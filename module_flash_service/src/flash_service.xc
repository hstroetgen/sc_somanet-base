/**
 * @file flash_service.xc
 * @author Synapticon GmbH <support@synapticon.com>
 */

#include <platform.h>

#include <flash_service.h>
#include <flash_boot.h>
#include <flash_data.h>
#include <flash_common.h>

#include <print.h>
#include <string.h>


#ifdef XCORE200

unsigned int get_app_tile_usec(void)
{
    // read tile frequency
    unsigned int app_tile_usec = USEC_STD;
    unsigned ctrlReadData;
    read_sswitch_reg(get_local_tile_id(), 8, ctrlReadData);
    if(ctrlReadData == 1) {
        app_tile_usec = USEC_FAST;
    }

    return app_tile_usec;
}

void flash_service(fl_QSPIPorts &SPI,
                   interface FlashBootInterface server ?i_boot,
                   interface FlashDataInterface server (&?i_data)[n_data], unsigned n_data)
#else
void flash_service(fl_SPIPorts &SPI,
                   interface FlashBootInterface server ?i_boot,
                   interface FlashDataInterface server (&?i_data)[n_data], unsigned n_data)
#endif
{

    /* Init local variables */
    unsigned int erase_flash = 0;
    int erase_error = 0;

    if (isnull(i_boot) && isnull(i_data))
    {
        printstr("Error: No flash interfaces provided.\n");
        return;
    }

    printstr(">>   SOMANET FLASH SERVICE STARTING...\n");

    #ifdef XCORE200
        flash_init(SPI, get_app_tile_usec());
    #else
        flash_init(SPI);
    #endif

    //Send data ready notification to all clients
     for (int i = 0; i < n_data; i++)
         i_data[i].service_ready();

    while (1) {
        select {
            case !isnull(i_data) => i_data[int i].get_configurations(int type, unsigned char buffer[], unsigned &n_bytes) -> int result: {
                #ifdef XCORE200
                    change_FlashDeviceSpec(get_app_tile_usec());
                #endif
                unsigned char intermediate_buffer[1024];
                unsigned intermediate_n_bytes;
                result = get_configurations(type, intermediate_buffer, intermediate_n_bytes, FLASH_PAGE_SIZE);
                if (result == NO_ERROR) {
                    memcpy(buffer, intermediate_buffer, intermediate_n_bytes);
                    n_bytes = intermediate_n_bytes;
                }
                break;
            }
            case !isnull(i_data) => i_data[int i].set_configurations(int type, unsigned char data[n_bytes], unsigned n_bytes) -> int result: {
                #ifdef XCORE200
                    change_FlashDeviceSpec(get_app_tile_usec());
                #endif
                unsigned char intermediate_buffer[1024];
                memcpy(intermediate_buffer, data, n_bytes);
                result = set_configurations(type, intermediate_buffer, n_bytes, FLASH_PAGE_SIZE);
                break;
            }

            case !isnull(i_data) => i_data[int i].read(unsigned addr, unsigned size, unsigned char buffer[]) -> int error: {
                #ifdef XCORE200
                    change_FlashDeviceSpec(get_app_tile_usec());
                #endif
                unsigned char intermediate_buffer[MAX_PACKET_SIZE];
                error = flash_read_data(addr,size,intermediate_buffer);
                memcpy(buffer, intermediate_buffer, size);
            }
            break;

            case !isnull(i_data) => i_data[int i].write(unsigned addr, unsigned size, unsigned char buffer[]) -> int error: {
                #ifdef XCORE200
                    change_FlashDeviceSpec(get_app_tile_usec());
                #endif
                unsigned char intermediate_buffer[MAX_PACKET_SIZE];
                memcpy(intermediate_buffer, buffer, size);
                error = flash_write_data(addr,size,intermediate_buffer);
            }
            break;

            case !isnull(i_data) => i_data[int i].erase(unsigned addr, unsigned size) -> int error: {
                #ifdef XCORE200
                    change_FlashDeviceSpec(get_app_tile_usec());
                #endif

                 error = flash_erase_data(addr,size);
            }
            break;

            case !isnull(i_boot) => i_boot.prepare_boot_partition() -> int error: {
                #ifdef XCORE200
                    change_FlashDeviceSpec(get_app_tile_usec());
                #endif
                error = flash_prepare_boot_partition();
            }
            break;

            case !isnull(i_boot) => i_boot.validate_flashing(void) -> int error: {
                #ifdef XCORE200
                    change_FlashDeviceSpec(get_app_tile_usec());
                #endif
                // Try to find new image
                error = flash_find_images();
            }
            break;

            case !isnull(i_boot) => i_boot.read(char data[], unsigned nbytes, unsigned char image_num) -> int error: {
                   // Todo
            }
            break;

            case !isnull(i_boot) => i_boot.write(char page[], unsigned nbytes) -> int error: {
                #ifdef XCORE200
                    change_FlashDeviceSpec(get_app_tile_usec());
                #endif
                char data[MAX_PACKET_SIZE];
                memcpy(data, page, nbytes);
                error = flash_write_boot_page(data, nbytes);
                break;
            }

            case !isnull(i_boot) => i_boot.erase_boot_partition(void): {
                erase_flash = 1;
                break;
            }

            case !isnull(i_boot) => i_boot.upgrade_image_installed(void) -> int error:
            {
                #ifdef XCORE200
                    change_FlashDeviceSpec(get_app_tile_usec());
                #endif
                error = upgrade_image_installed();
                break;
            }

            case !isnull(i_boot) => i_boot.get_notification() -> int error:
                    error = erase_error;
                break;

            /* Do time consuming operations and notify client when done - to make sure we don't block */
            default:
                #ifdef XCORE200
                    change_FlashDeviceSpec(get_app_tile_usec());
                #endif
                if (!isnull(i_boot) && erase_flash)
                {
                    erase_error = flash_erase_boot_partition();
                    erase_flash = 0;

                    i_boot.notification();
                }
                break;

        }
    }
}
