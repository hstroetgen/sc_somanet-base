/**
 * @file flash_write.c
 * @brief Flash device access
 * @author Synapticon GmbH <support@synapticon.com>
 */

#include <stdlib.h>
#include <stdint.h>
#include <flashlib.h>
#include <platform.h>
#include <flash.h>
#include <flash_somanet.h>
#include <string.h>
#include <print.h>

//#define DEBUG // No space for prints!

fl_SPIPorts SPI_port;



void flash_init(fl_SPIPorts *SPI)
{
    SPI_port = SPI;
}

void connect_to_flash(void)
{
    if (fl_connect(SPI_port) != 0) {
        #ifdef DEBUG
        printstrln("could not connect flash");
        #endif
        exit(1);
    }
}

// Address must be a multiple of page_size
void flash_buffer(unsigned char content[BUFFER_SIZE], int image_size, unsigned address)
{
    unsigned current_page = 0;

    for (int i=0; i<(image_size/PAGE_SIZE); i++) {
        fl_writePage(address, &content[current_page]);
        current_page += PAGE_SIZE;
        address += PAGE_SIZE;
    }
}


int __write_data_flash(unsigned char data[PAGE_SIZE], int data_length, int page)
{
    /* Array to store the data to be written to the flash */
    unsigned char data_page[PAGE_SIZE];

    int status = 1;             /* SUCCESS == 1 */

    /* Initialise the my_page array */
    for (int i=0; i<PAGE_SIZE; i++ ) {
        if (i < data_length) {
            data_page[i] = data[i];
        } else {
            data_page[i] = 0x0;
        }
    }

    connect_to_flash();

    #ifdef DEBUG
    // Get the FLASH data partition size
    int temp = fl_getDataPartitionSize();
    printstr("FLASH data partition size: ");
    printint(temp);
    printstrln(" bytes.");
    #endif
    // TODO Perhaps not the smartest decision to delete everything, isn't it?
    if (page == 0) {
        if (fl_eraseAllDataSectors() != 0) {
            #ifdef DEBUG
            printstrln("Could not erase the data partition");
            #endif
            status = 0;
        }
    }

    // Write to the data partition
    if (fl_writeDataPage(page, data_page) != 0) {
        #ifdef DEBUG
        printstrln("Could not write the data partition");
        #endif
        status = 0;
    }

    // Read from the data partition and Verify
    if (fl_readDataPage(page, data_page) != 0) {
        #ifdef DEBUG
        printstrln("Could not read the data partition");
        #endif
        status = 0;
    }

    // Verify
    for (int i=0; i<PAGE_SIZE; i++) {
        if (i < data_length) {
            if (data_page[i] != data[i]) {
                status = 0;
                break;
            }
        }
    }
    return status;
}

//int __read_data_flash(fl_SPIPorts *SPI, int page, unsigned char data[256])
int __read_data_flash(int page, unsigned char data[PAGE_SIZE])
{
    /* Variables for buffering, counting iterations, etc */
    unsigned int temp;
    int status = 1;

    /* Initialise the data_page array */
    memset(data, 0, PAGE_SIZE);

    connect_to_flash();

    // Get the FLASH data partition size
    #ifdef DEBUG
    temp = fl_getDataPartitionSize();
    printstr("FLASH data partition size: ");
    printint(temp);
    printstrln(" bytes.");
    #endif

    // Read from the data partition and Verify
    if (fl_readDataPage(page, data) != 0) {
        #ifdef DEBUG
        printstrln("Could not read the data partition");
        #endif
        status = 0;
    }

    return status;
}

