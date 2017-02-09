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


void spiffs_service(CLIENT_INTERFACE(FlashDataInterface, i_data), interface SPIFFSInterface server ?i_spiffs)
{
    /* Init SPIFFS */

    printstrln(">>   SPIFFS SERVICE STARTING...\n");

    spiffs_init(i_data);

    while (1) {
        select {
                   case !isnull(i_spiffs) => i_spiffs.open_file(char path[], unsigned path_length, unsigned short flags) -> unsigned short fd:
                       char buffer[MAX_FILENAME_SIZE];
                       memcpy(buffer,path,path_length+1);
                       fd = iSPIFFS_open(buffer, flags);
                   break;
                   case !isnull(i_spiffs) => i_spiffs.close_file(unsigned short fd) -> int res:
                       res = iSPIFFS_close(fd);
                   break;

                   case !isnull(i_spiffs) => i_spiffs.read(unsigned short fd, unsigned char data[], unsigned int len) -> int res:
                       unsigned char buffer[MAX_DATA_BUFFER_SIZE];
                       res = iSPIFFS_read(fd, buffer, len);
                       memcpy(data, buffer, len);
                   break;

                   case !isnull(i_spiffs) => i_spiffs.write(unsigned short fd, unsigned char data[], unsigned int len) -> int res:
                       unsigned char buffer[MAX_DATA_BUFFER_SIZE];
                       memcpy(buffer, data, len);
                       res = iSPIFFS_write(fd, buffer, len);
                   break;

                   case !isnull(i_spiffs) => i_spiffs.remove_file(unsigned short fd) -> int res:
                        res = iSPIFFS_remove(fd);
                   break;

                   case !isnull(i_spiffs) => i_spiffs.vis() -> int res:
                       res = iSPIFFS_vis();
                   break;

                   case !isnull(i_spiffs) => i_spiffs.check() -> int res:
                       res = iSPIFFS_check();
                   break;

                   case !isnull(i_spiffs) => i_spiffs.status(unsigned short fd, unsigned short &obj_id, unsigned int &size, unsigned char type, unsigned short pix, unsigned char name[]) -> int res:
                           unsigned char buffer[MAX_FILENAME_SIZE];
                           res = iSPIFFS_status(fd, obj_id, size, type, pix, buffer);
                           memcpy(name, buffer, MAX_FILENAME_SIZE);
                   break;

                   case !isnull(i_spiffs) => i_spiffs.format() -> int res:
                        res = iSPIFFS_format();
                   break;

                   case !isnull(i_spiffs) => i_spiffs.tell(unsigned short fd) -> int res:
                       res = iSPIFFS_tell(fd);
                   break;

                   case !isnull(i_spiffs) => i_spiffs.seek(unsigned short fd, int offs, int whence) -> int res:
                       res = iSPIFFS_seek(fd, offs, whence);
                   break;

                   case !isnull(i_spiffs) => i_spiffs.rename_file(char old_path[], unsigned old_path_length, char new_path[], unsigned new_path_length) -> int res:
                       char old_buffer[MAX_FILENAME_SIZE];
                       char new_buffer[MAX_FILENAME_SIZE];
                       memcpy(old_buffer,old_path,old_path_length+1);
                       memcpy(new_buffer,new_path,new_path_length+1);
                       res = iSPIFFS_rename(old_buffer, new_buffer);
                   break;
               }
    }
}
