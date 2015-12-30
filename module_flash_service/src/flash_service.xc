/**
 * @file flash_service.xc
 * @author Synapticon GmbH <support@synapticon.com>
 */

#include <flash_service.h>
#include <flash_boot.h>
#include <flash_data.h>

// TODO Nullable interfaces!
void flash_service(fl_SPIPorts &SPI,
                   interface FlashBootInterface server ?i_boot,
                   interface FlashDataInterface server i_data[n],
                   unsigned n) {
    int command;
    int data_length; /* data length exceeds page length error */
    int page;        /* page exceeds error, no data partition found error */
    int status;      /* erase all pages atleast once if status is always 0 even if data partition is found */

    fl_BootImageInfo bii;

    flash_init(SPI);

    // XXX code in the cases is just scrap and random or symbolic
    while (1) {
        select {
            /* Data Field update */
            case i_data[int i].read(char data[], unsigned nbytes, unsigned address): {
                // TODO Do flash management
                status = __read_data_flash(page, data);
            }
            break;
            case i_data[int i].write(char data[], unsigned nbytes) -> int address: {
                status = __write_data_flash(data, data_length, page);
            }
            break;
            // XXX we don't need addresses here, because the position in the boot partition will be calculated automatically.
            case i_boot.read(char data[], unsigned nbytes, unsigned char image_num) -> unsigned error: {
                // Calculating addresses of the factory image.
                if (fl_getFactoryImage(bii)) {
                    error = NO_FACTORY_IMAGE;
                    break;
                }

                // In dependence of the factory image, we calculate the address of the next upgrade images (if available)
                for (int i = 0; i < image_num; i++) {
                    if (fl_getNextBootImage(bii)) {
                        error = NO_UPGRADE_IMAGE;
                        break;
                    }
                }

                fl_imageReadState.currentAddress = bootImageInfo->startAddress;
                unsigned limitAddress = fl_imageReadState.currentAddress + bootImageInfo->size;
                unsigned pageSize = fl_getPageSize();
                limitAddress = ((limitAddress + pageSize - 1) / pageSize) * pageSize;
                fl_imageReadState.limitAddress = limitAddress;

                // If image_num is zero, we will read the factory image. For image number greater then zero,
                // we will read the n-1th upgrade image.

                // When we are using fl_readImagePage(), we have to call first fl_startImageRead(), which calculateds the start and end addres of the image.
                // fl_startImageRead(b)
                read_boot_flash();
            }
            break;
            case i_boot.write(char data[], unsigned nbytes): {
                write_boot_flash();
            }
            break;
            default:
                break;
        }
    }
}
