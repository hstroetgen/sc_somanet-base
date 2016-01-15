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

/**
 * @brief Encode (custom) the total size of stored configurations in the flash memory
 *
 * Used for (customly) encoding the number stored inside the flash memory
 * that contains the information about the total number of bytes that a
 * certain type of configurations take up in the flash memory.
 *
 * @param n_bytes the number to be encoded
 */
unsigned int encode_data_size(unsigned int n_bytes) {
    if (n_bytes >= 65536) {
        printstrln("Invalid data size - must be less than 65536 bytes");
        return 0;
    }
    return (n_bytes << 16) | (~n_bytes & 0x0000FFFF);
}

/**
 * @brief Decode the total size of stored configurations in the flash memory
 *
 * Used for decoding (and confirming the validity) of the number stored
 * inside the flash memory that contains the information about the total
 * number of bytes that a certain type of configurations take up in the
 * flash memory. The encoding must be done by the encode_data_size()
 * function.
 *
 * @param encoded_n_bytes customly built 32bit integer containing data size
 */
unsigned int decode_data_size(unsigned int encoded_n_bytes) {
    int n_bytes = encoded_n_bytes >> 16;
    int n_bytes_check = ~(encoded_n_bytes & 0x0000FFFF) & 0x0000FFFF;

    if (n_bytes == n_bytes_check) {
        return n_bytes;
    } else {
        return 0;
    }
}

// TODO Nullable interfaces!
void flash_service(fl_SPIPorts &SPI,
                   interface FlashBootInterface server ?i_boot,
                   interface FlashDataInterface server i_data[n],
                   unsigned n) {
    fl_BootImageInfo bootImageInfo;

    flash_init(SPI);

    // XXX code in the cases is just scrap and random or symbolic
    while (1) {
        select {
            case i_data[int i].get_configurations(int type, unsigned char buffer[], unsigned &n_bytes) -> int result: {
                int current_type_first_page = DATA_PAGES_PER_TYPE * type;
                result = 0;

                // Conect to flash
                result = connect_to_flash();
                if (result != 0) {
                    break;
                }

                // Read the first data page
                char data_page[256];
                memset(data_page, 0, sizeof(data_page));    // Fill the data page with zeros

                // Read from the data partition
                result = fl_readDataPage(current_type_first_page, data_page);
                if (result != 0) {
                    printstrln( "Could not read the data partition" );
                    break;
                }

                // Get the number of bytes configurations take up
                int encoded_data_size;
                memcpy(&encoded_data_size, data_page, sizeof(int));

                n_bytes = decode_data_size(encoded_data_size);

                if (n_bytes > 252) {    // 252 = 256 - 4 (space left in the first page)
                    memcpy(buffer, data_page + sizeof(int), 252);
                    int read_bytes = 252;
                    n_bytes -= read_bytes;
                    for (int i = 1; n_bytes > 0; i++) {
                        result = fl_readDataPage(current_type_first_page + i, data_page);
                        if (result != 0) {
                            printstrln( "Could not read the data partition" );
                            break;
                        }
                        if (n_bytes <= 256) {
                            memcpy(buffer + read_bytes, data_page, n_bytes);
                            n_bytes = 0;
                        } else {
                            memcpy(buffer + read_bytes, data_page, 256);
                            read_bytes += 256;
                            n_bytes -= read_bytes;
                        }
                    }
                } else {
                    memcpy(buffer, data_page + sizeof(int), n_bytes);
                }

                // Disconnect from the flash
                result = fl_disconnect();
                if (result != 0){
                    printstrln( "Could not disconnect from FLASH" );
                }

                break;
            }
            case i_data[int i].set_configurations(int type, unsigned char data[n_bytes], unsigned n_bytes) -> int result: {
                int current_type_first_page = DATA_PAGES_PER_TYPE * type;
                result = 0;

                result = connect_to_flash();
                if (result != 0) {
                    break;
                }

                // Check the data partition size
                if (fl_getDataPartitionSize() == 0) {
                    result = 1;
                    printstrln( "No data partition available." );
                    break;
                }

                // Clear the current configuration data sector
                result = fl_eraseAllDataSectors();
                if (result != 0) {
                    printstrln( "Could not clear the configuration data sector" );
                    break;
                }

                char data_page[256];
                memset(data_page, 0, sizeof(data_page));    // Fill the data page with zeros

                // Copy the number of bytes that will be occupied in total
                int data_to_store = encode_data_size(n_bytes);
                memcpy(data_page, &data_to_store, sizeof(int));

                if (n_bytes > 252) {    // 252 = 256 - 4 (space left in the first page)
                    memcpy(data_page + sizeof(int), data, 252);
                    result = fl_writeDataPage(current_type_first_page, data_page);
                    if (result != 0){
                        printstrln( "Could not write a data page" );
                        break;
                    }
                    int written_bytes = 252;
                    for (int i = 1; written_bytes < n_bytes; i++) {
                        if (n_bytes - written_bytes <= 256) {
                            memset(data_page, 0, sizeof(data_page));    // Fill the data page with zeros
                            memcpy(data_page, data + written_bytes, n_bytes - written_bytes);
                            result = fl_writeDataPage(current_type_first_page + i, data_page);
                            if (result != 0){
                                printstrln( "Could not write a data page" );
                                break;
                            }
                            written_bytes = n_bytes;
                        } else {
                            memcpy(data_page, data + written_bytes, 256);
                            result = fl_writeDataPage(current_type_first_page + i, data_page);
                            if (result != 0){
                                printstrln( "Could not write a data page" );
                                break;
                            }
                            written_bytes += 256;
                        }
                    }
                } else {
                    memcpy(data_page + sizeof(int), data, n_bytes);
                    result = fl_writeDataPage(current_type_first_page, data_page);
                    if (result != 0){
                        printstrln( "Could not write a data page" );
                        break;
                    }
                }

                // Disconnect from the flash
                result = fl_disconnect();
                if (result != 0){
                    printstrln( "Could not disconnect from FLASH" );
                }

                break;
            }
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
