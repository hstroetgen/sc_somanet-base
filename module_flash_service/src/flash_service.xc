/**
 * @file flash_service.xc
 * @author Synapticon GmbH <support@synapticon.com>
 */

#include <flash_service.h>
#include <flash_boot.h>
#include <flash_data.h>
#include <flash_common.h>

#include <flashlib.h>
#include <print.h>
#include <string.h>



void flash_service(fl_SPIPorts &SPI,
                   interface FlashBootInterface server ?i_boot,
                   interface FlashDataInterface server (&?i_data)[2]) {

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
                result = get_configurations(type, intermediate_buffer, intermediate_n_bytes);
                memcpy(buffer, intermediate_buffer, intermediate_n_bytes);
                n_bytes = intermediate_n_bytes;
                break;
            }
            case !isnull(i_data) => i_data[int i].set_configurations(int type, unsigned char data[n_bytes], unsigned n_bytes) -> int result: {
                unsigned char intermediate_buffer[1024];
                memcpy(intermediate_buffer, data, n_bytes);
                result = set_configurations(type, intermediate_buffer, n_bytes);
                break;
            }

            case i_boot.prepare_boot_partition(unsigned image_size) -> int error: {
                error = flash_prepare_boot_partition(image_size);
            }
            break;

            case i_boot.validate_flashing(void) -> int error: {
                // Try to find new image
                error = flash_find_images();
            }
            break;

            case i_boot.read(char data[], unsigned nbytes, unsigned char image_num) -> int error: {
                   // Todo
            }
            break;

            case i_boot.write(char page[], unsigned nbytes) -> int error: {
                char data[PAGE_SIZE];
                memcpy(data, page, PAGE_SIZE);
                error = flash_write_boot(data, nbytes);
            }
            break;
        }
    }
}
