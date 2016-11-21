/*
 * spiffs_service.xc
 *
 *  Created on: Nov 15, 2016
 *      Author: Simon Fischinger <sfischinger@synapticon.com>
 */

#include <platform.h>

#include <spiffs_service.h>
#include <spiffs_xc_wrapper.h>

#include <print.h>

/**
 * @brief SPIFFS Service, handling all file system operations
 */
void spiffs_service()
{

    /* Init SPIFFS */
    spiffs_init();

    while (1)
    {
        printstrln("spiffs_service()");
        test_wrapper_function();
        delay_milliseconds(1000);
    }
}
