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

// TODO Nullable interfaces!
void flash_service(fl_SPIPorts &SPI,
                   interface FlashBootInterface server ?i_boot,
                   interface FlashDataInterface server i_data[2]) {
    fl_BootImageInfo bootImageInfo;

    flash_init(SPI);

    while (1) {
        select {
            case i_data[int i].get_configurations(int type, unsigned char buffer[], unsigned &n_bytes) -> int result: {
                unsigned char intermediate_buffer[1024];
                unsigned intermediate_n_bytes;
                result = get_configurations(type, intermediate_buffer, intermediate_n_bytes);
                memcpy(buffer, intermediate_buffer, intermediate_n_bytes);
                n_bytes = intermediate_n_bytes;
                break;
            }
            case i_data[int i].set_configurations(int type, unsigned char data[n_bytes], unsigned n_bytes) -> int result: {
                unsigned char intermediate_buffer[1024];
                memcpy(intermediate_buffer, data, n_bytes);
                result = set_configurations(type, intermediate_buffer, n_bytes);
                break;
            }
            // XXX code in below cases is just scrap and random or symbolic
            // XXX we don't need addresses here, because the position in the boot partition will be
            // calculated automatically.
            case i_boot.read(char data[], unsigned nbytes, unsigned char image_num) -> int result: {
                // Calculating addresses of the factory image.
                if (fl_getFactoryImage(bootImageInfo)) {
                    result = NO_FACTORY_IMAGE;
                    break;
                }

                // In dependence of the factory image, we calculate the address of the next upgrade images (if available)
                for (int i = 0; i < image_num; i++) {
                    if (fl_getNextBootImage(bootImageInfo)) {
                        result = NO_UPGRADE_IMAGE;
                        break;
                    }
                }

                unsigned limitAddress = bootImageInfo.startAddress + bootImageInfo.size;
                unsigned pageSize = fl_getPageSize();
                limitAddress = ((limitAddress + pageSize - 1) / pageSize) * pageSize;
//                fl_imageReadState.currentAddress = bootImageInfo.startAddress;
//                fl_imageReadState.limitAddress = limitAddress;

                // If image_num is zero, we will read the factory image. For image number greater then zero,
                // we will read the n-1th upgrade image.

                // When we are using fl_readImagePage(), we have to call first fl_startImageRead(),
                // which calculateds the start and end addres of the image.
                // fl_startImageRead(b)
//                result = flash_read_boot(data, nbytes);
            }
            break;
            case i_boot.write(char data[], unsigned nbytes) -> int result: {
//                result = flash_write_boot(data, nbytes);
            }
            break;
            default:
                break;
        }
    }
}
