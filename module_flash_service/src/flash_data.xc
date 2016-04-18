/**
 * @file flash_data.xc
 * @author Synapticon GmbH <support@synapticon.com>
 */

#include <flash_service.h>
#include <flash_common.h>

#include <flashlib.h>
#include <print.h>
#include <string.h>

#define SPECIAL_PAGE_SIZE PAGE_SIZE-4


int flash_data_init(unsigned partition_size) {
    // TODO
    return 0;
}

int flash_write_data(char data[], unsigned size) {
    // TODO
    return 0;
}

int flash_read_data(char data[], unsigned page) {
    // Read from the data partition
    result = fl_readDataPage(page, data);
    return result;
}

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

int get_configurations(int type, unsigned char buffer[], unsigned &n_bytes) {
    int current_type_first_page = DATA_PAGES_PER_TYPE * type;

    // Conect to flash
    int result = connect_to_flash();
    if (result != 0) {
        return result;
    }

    // Read the first data page
    char data_page[PAGE_SIZE];
    memset(data_page, 0, sizeof(data_page));    // Fill the data page with zeros

    // Read from the data partition
    result = fl_readDataPage(current_type_first_page, data_page);
    if (result != 0) {
        printstrln( "Could not read the data partition" );
        return result;
    }

    // Get the number of bytes configurations take up
    int encoded_data_size;
    memcpy(&encoded_data_size, data_page, sizeof(int));

    n_bytes = decode_data_size(encoded_data_size);
    // FIXME Why this 4 bytes?
    if (n_bytes > SPECIAL_PAGE_SIZE) {    // 252 = 256 - 4 (space left in the first page)
        memcpy(buffer, data_page + sizeof(int), SPECIAL_PAGE_SIZE);
        int read_bytes = SPECIAL_PAGE_SIZE;
        n_bytes -= read_bytes;
        for (int i = 1; n_bytes > 0; i++) {
            result = fl_readDataPage(current_type_first_page + i, data_page);
            if (result != 0) {
                printstrln( "Could not read the data partition" );
                return result;
            }
            if (n_bytes <= PAGE_SIZE) {
                memcpy(buffer + read_bytes, data_page, n_bytes);
                n_bytes = 0;
            } else {
                memcpy(buffer + read_bytes, data_page, PAGE_SIZE);
                read_bytes += PAGE_SIZE;
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

    return result;
}

int set_configurations(int type, unsigned char data[n_bytes], unsigned int n_bytes) {
    int current_type_first_page = DATA_PAGES_PER_TYPE * type;

    // Conect to flash
    int result = connect_to_flash();
    if (result != 0) {
        return result;
    }

    // Check the data partition size
    if (fl_getDataPartitionSize() == 0) {
        result = 1;
        printstrln( "No data partition available." );
        return result;
    }

    // Clear the current configuration data sector
    result = fl_eraseAllDataSectors();
    if (result != 0) {
        printstrln( "Could not clear the configuration data sector" );
        return result;
    }

    char data_page[PAGE_SIZE];
    memset(data_page, 0, sizeof(data_page));    // Fill the data page with zeros

    // Copy the number of bytes that will be occupied in total
    int data_to_store = encode_data_size(n_bytes);
    memcpy(data_page, &data_to_store, sizeof(int));
    // FIXME Why this 4 bytes?
    if (n_bytes > SPECIAL_PAGE_SIZE) {    // 252 = 256 - 4 (space left in the first page)
        memcpy(data_page + sizeof(int), data, SPECIAL_PAGE_SIZE);
        result = fl_writeDataPage(current_type_first_page, data_page);
        if (result != 0){
            printstrln( "Could not write a data page" );
            return result;
        }
        int written_bytes = SPECIAL_PAGE_SIZE;
        for (int i = 1; written_bytes < n_bytes; i++) {
            if (n_bytes - written_bytes <= PAGE_SIZE) {
                memset(data_page, 0, sizeof(data_page));    // Fill the data page with zeros
                memcpy(data_page, data + written_bytes, n_bytes - written_bytes);
                result = fl_writeDataPage(current_type_first_page + i, data_page);
                if (result != 0){
                    printstrln( "Could not write a data page" );
                    return result;
                }
                written_bytes = n_bytes;
            } else {
                memcpy(data_page, data + written_bytes, PAGE_SIZE);
                result = fl_writeDataPage(current_type_first_page + i, data_page);
                if (result != 0){
                    printstrln( "Could not write a data page" );
                    return result;
                }
                written_bytes += PAGE_SIZE;
            }
        }
    } else {
        memcpy(data_page + sizeof(int), data, n_bytes);
        result = fl_writeDataPage(current_type_first_page, data_page);
        if (result != 0){
            printstrln( "Could not write a data page" );
            return result;
        }
    }

    // Disconnect from the flash
    result = fl_disconnect();
    if (result != 0){
        printstrln( "Could not disconnect from FLASH" );
    }

    return result;
}
