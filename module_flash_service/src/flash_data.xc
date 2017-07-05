/**
 * @file flash_data.xc
 * @author Synapticon GmbH <support@synapticon.com>
 */

#include <flash_service.h>
#include <flash_common.h>

#ifdef XCORE200
#include <quadflashlib.h>
#else
#include <flashlib.h>
#endif

#include <print.h>
#include <string.h>


int flash_data_init(unsigned partition_size) {

    return 0;
}

int flash_write_data(unsigned addr, unsigned size, unsigned char data[]) {

    int result = 0;
    int page_offset, page_len, page_num;
    int data_offset = 0;
    unsigned char page_buffer[FLASH_PAGE_SIZE];

    do {
         //calculate position and lenght for current page
         page_offset = (addr % FLASH_PAGE_SIZE);
         page_len = (size <= (FLASH_PAGE_SIZE - page_offset)) ? size : (FLASH_PAGE_SIZE - page_offset);
         page_num = addr / FLASH_PAGE_SIZE;

         //save previous data from page
         if (result !=0 )
         {
                       printstrln( "Could not connect to FLASH" );
                       return result;
          }

         result = fl_readDataPage(page_num, page_buffer);
         if (result !=0 )
         {
              printstrln( "Could not read from FLASH" );
              return result;
         }

         //copy new data to page buffer
         memcpy(page_buffer + page_offset, data + data_offset, page_len);
         result = fl_writeDataPage(page_num, page_buffer);

         if (result !=0 )
         {
             printstrln( "Could not write to FLASH" );
             return result;
         }

         data_offset += page_len;
         addr += page_len;
         size -= page_len;

    }  while (size > 0);

    return result;
}

int flash_read_data(unsigned addr, unsigned size, unsigned char data[]) {

    int result = 0;

    // Read from the data partition
    result = fl_readData(addr, size, data);
    if (result !=0 )
    {
        printstrln( "Could not read from FLASH" );
        return result;
    }

    return result;
}


int flash_erase_data(unsigned addr, unsigned size)
{

    int result = 0;
    unsigned sec_num, sec_size;

    //convert address to sector number
    sec_num = addr / 0xFFF;
    sec_size = size / 0xFFF;

    //erase sectors
    for (unsigned i = sec_num; i < sec_num + sec_size; i++)
    {
        result = fl_eraseDataSector(i);
        if (result !=0 )
        {
           printstrln( "Could not erase FLASH sector" );
           return result;
        }
    }

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

int get_configurations(int type, unsigned char buffer[], unsigned &n_bytes, const static int flash_page_size_bytes)
{
    int current_type_first_page = DATA_PAGES_PER_TYPE * type;
    const int special_page_size = flash_page_size_bytes - 4;

    // Conect to flash
    int result = connect_to_flash();
    if (result != 0) {
        return result;
    }

    // Check the data partition size
    if (fl_getDataPartitionSize() == 0) {
        result = ERR_NO_DATA_PARTITION;
        printstrln( "No data partition available." );
        return result;
    }

    // Read the first data page
    char data_page[flash_page_size_bytes];
    memset(data_page, 0, flash_page_size_bytes);    // Fill the data page with zeros

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
    // The first 4 bytes contain an encoded size of total data written in the data partition
    if (n_bytes > special_page_size) {    // 252 = 256 - 4 (space left in the first page)
        memcpy(buffer, data_page + sizeof(int), special_page_size);
        int read_bytes = special_page_size;
        n_bytes -= read_bytes;
        for (int i = 1; n_bytes > 0; i++) {
            result = fl_readDataPage(current_type_first_page + i, data_page);
            if (result != 0) {
                printstrln( "Could not read the data partition" );
                return result;
            }
            if (n_bytes <= flash_page_size_bytes) {
                memcpy(buffer + read_bytes, data_page, n_bytes);
                n_bytes = 0;
            } else {
                memcpy(buffer + read_bytes, data_page, flash_page_size_bytes);
                read_bytes += flash_page_size_bytes;
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

int set_configurations(int type, unsigned char data[n_bytes], unsigned int n_bytes, const static int flash_page_size_bytes) {
    int current_type_first_page = DATA_PAGES_PER_TYPE * type;
    const int special_page_size = flash_page_size_bytes - 4;

    // Conect to flash
    int result = connect_to_flash();
    if (result != 0) {
        return result;
    }

    // Check the data partition size
    if (fl_getDataPartitionSize() == 0) {
        result = ERR_NO_DATA_PARTITION;
        printstrln( "No data partition available." );
        return result;
    }

    // Clear the current configuration data sector
    result = fl_eraseAllDataSectors();
    if (result != 0) {
        printstrln( "Could not clear the configuration data sector" );
        return result;
    }

    char data_page[flash_page_size_bytes];
    memset(data_page, 0, flash_page_size_bytes);    // Fill the data page with zeros

    // Copy the number of bytes that will be occupied in total
    int data_to_store = encode_data_size(n_bytes);
    memcpy(data_page, &data_to_store, sizeof(int));
    // FIXME Why this 4 bytes?
    if (n_bytes > special_page_size) {    // 252 = 256 - 4 (space left in the first page)
        memcpy(data_page + sizeof(int), data, special_page_size);
        result = fl_writeDataPage(current_type_first_page, data_page);
        if (result != 0){
            printstrln( "Could not write a data page" );
            return result;
        }
        int written_bytes = special_page_size;
        for (int i = 1; written_bytes < n_bytes; i++) {
            if (n_bytes - written_bytes <= flash_page_size_bytes) {
                memset(data_page, 0, flash_page_size_bytes);    // Fill the data page with zeros
                memcpy(data_page, data + written_bytes, n_bytes - written_bytes);
                result = fl_writeDataPage(current_type_first_page + i, data_page);
                if (result != 0){
                    printstrln( "Could not write a data page" );
                    return result;
                }
                written_bytes = n_bytes;
            } else {
                memcpy(data_page, data + written_bytes, flash_page_size_bytes);
                result = fl_writeDataPage(current_type_first_page + i, data_page);
                if (result != 0){
                    printstrln( "Could not write a data page" );
                    return result;
                }
                written_bytes += flash_page_size_bytes;
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
