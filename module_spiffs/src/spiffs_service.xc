/*
 * spiffs_service.xc
 *
 *  Created on: Nov 15, 2016
 *      Author: Simon Fischinger <sfischinger@synapticon.com>
 */

#include <string.h>
#include <xccompat.h>
#include <print.h>
#include <stdio.h>
#include <flash_service.h>
#include <spiffs_service.h>
#include <spiffs_xc_wrapper.h>



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



void spiffs_service(CLIENT_INTERFACE(FlashDataInterface, i_data), interface SPIFFSInterface server ?i_spiffs, char ready)
{
    /* Init SPIFFS */

    printstrln(">>   SPIFFS SERVICE STARTING...\n");

    spiffs_init(i_data);

    ready = 1;

    while (1) {
        select {
                   case !isnull(i_spiffs) => i_spiffs.open_file(char path[], unsigned path_length, unsigned short flags) -> unsigned short fd:
                       char buffer[32];
                       memcpy(buffer,path,path_length+1);
                       fd = iSPIFFS_open(buffer, flags);
                   break;

                   case !isnull(i_spiffs) => i_spiffs.close_file() -> int res:
                       iSPIFFS_close();
                   break;

                   case !isnull(i_spiffs) => i_spiffs.read(unsigned char data[], unsigned int len) -> int res:
                       unsigned char buffer[1024];
                       res = iSPIFFS_read(buffer, len);
                       memcpy(data, buffer, len);
                   break;

                   case !isnull(i_spiffs) => i_spiffs.write(unsigned char data[], unsigned int len) -> int res:
                       unsigned char buffer[1024];
                       memcpy(buffer, data, len);
                       res = iSPIFFS_write(buffer, len);
                   break;

                   case !isnull(i_spiffs) => i_spiffs.remove_file() -> int res:
                        res = iSPIFFS_remove();
                   break;

                   case !isnull(i_spiffs) => i_spiffs.vis() -> int res:
                       res = iSPIFFS_vis();
                   break;

                   case !isnull(i_spiffs) => i_spiffs.check() -> int res:
                       res = iSPIFFS_check();
                   break;

                   case !isnull(i_spiffs) => i_spiffs.status(unsigned short &obj_id, unsigned int &size, unsigned char type, unsigned short pix, unsigned char name[]) -> int res:
                           unsigned char buffer[32];
                           res = iSPIFFS_status(obj_id, size, type, pix, buffer);
                           memcpy(name, buffer, 32);
                   break;
               }
    }
}
