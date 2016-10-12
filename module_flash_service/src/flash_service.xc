/**
 * @file flash_service.xc
 * @author Synapticon GmbH <support@synapticon.com>
 */

#include <flash_service.h>
#include <flash_boot.h>
#include <flash_data.h>
#include <flash_common.h>

#ifdef XCORE200
#include <quadflashlib.h>
#else
#include <flashlib.h>
#endif

#include <print.h>
#include <string.h>

/* Defines the maximum size of a packet coming over the interface to be written into flash
 * (in bytes)
 */
#define MAX_PACKET_SIZE 1024

#ifdef XCORE200
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

    flash_init(SPI);

    while (1) {
        select {
            case !isnull(i_data) => i_data[int i].get_configurations(int type, unsigned char buffer[], unsigned &n_bytes) -> int result: {
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
                unsigned char intermediate_buffer[1024];
                memcpy(intermediate_buffer, data, n_bytes);
                result = set_configurations(type, intermediate_buffer, n_bytes, FLASH_PAGE_SIZE);
                break;
            }

            case !isnull(i_boot) => i_boot.prepare_boot_partition(): {
                erase_flash = 1;
            }
            break;

            case !isnull(i_boot) => i_boot.validate_flashing(void) -> int error: {
                // Try to find new image
                error = flash_find_images();
            }
            break;

            case !isnull(i_boot) => i_boot.read(char data[], unsigned nbytes, unsigned char image_num) -> int error: {
                   // Todo
            }
            break;

            case !isnull(i_boot) => i_boot.write(char page[], unsigned nbytes) -> int error: {
                char data[MAX_PACKET_SIZE];
                memcpy(data, page, nbytes);
                error = flash_write_boot_page(data, nbytes);
                break;
            }

            case !isnull(i_boot) => i_boot.erase_upgrade_image(void): {
                erase_flash = 1;
                break;
            }

            case !isnull(i_boot) => i_boot.upgrade_image_installed(void) -> int error:
            {
                error = upgrade_image_installed();
                break;
            }

            case !isnull(i_boot) => i_boot.get_notification() -> int error:
                    error = erase_error;
                break;

            /* Do time consuming operations and notify client when done - to make sure we don't block */
            default:
                if (!isnull(i_boot) && erase_flash)
                {
                    erase_error = flash_prepare_boot_partition();
                    erase_flash = 0;

                    i_boot.notification();
                }
                break;

        }
    }
}
