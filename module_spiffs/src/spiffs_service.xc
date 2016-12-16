/*
 * spiffs_service.xc
 *
 *  Created on: Nov 15, 2016
 *      Author: Simon Fischinger <sfischinger@synapticon.com>
 */

#include <platform.h>
#include <xccompat.h>
#include <flash_service.h>
#include <spiffs_service.h>
#include <spiffs_xc_wrapper.h>


#include <print.h>


/**
 * @brief SPIFFS Service, handling all file system operations
 */


void if_read_flash(CLIENT_INTERFACE(FlashDataInterface, i_data), unsigned int addr, unsigned int size, unsigned char *buf)
{
    i_data.read(addr, size, buf);
}

void if_write_flash(CLIENT_INTERFACE(FlashDataInterface, i_data), unsigned int addr, unsigned int size, unsigned char *buf)
{
    i_data.write(addr, size, buf);
}


void if_erase_flash(CLIENT_INTERFACE(FlashDataInterface, i_data), unsigned int addr, unsigned int size)
{
    i_data.erase(addr, size);
}



void spiffs_service(CLIENT_INTERFACE(FlashDataInterface, i_data))
{
    /* Init SPIFFS */

    spiffs_init(i_data);

    printstrln("spiffs_service()");
    test_wrapper_function();


   /* while (1)
    {
        printstrln("spiffs_service()");
        test_wrapper_function();
        delay_milliseconds(5000);

    }*/
}
