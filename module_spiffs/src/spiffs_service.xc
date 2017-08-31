/*
 * spiffs_service.xc
 *
 *  Created on: Nov 15, 2016
 *      Author: Simon Fischinger <sfischinger@synapticon.com>
 */

#include <string.h>
#include <xccompat.h>
#include <print.h>
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


void spiffs_service(CLIENT_INTERFACE(FlashDataInterface, i_data), interface SPIFFSInterface server i_spiffs[n_spiffs], unsigned n_spiffs)
{

    select {
        case i_data.service_ready():
    break;
    }

    if (i_data.getDataPartitionSize() < FLASH_PAGE_SIZE)
    {
        printstr("SPIFFS Error: data partition size missing.\n");
        return;
    }

    if (isnull(i_spiffs))
    {
        printstr("SPIFFS Error: No flash interfaces provided.\n");
        return;
    }

    /* Init SPIFFS */

    printstrln(">>   SPIFFS SERVICE STARTING...\n");

    spiffs_init(i_data);

    //Send data ready notification to all clients
    for (int i = 0; i < n_spiffs; i++)
        i_spiffs[i].service_ready();

    while (1) {
        select {
                   case !isnull(i_spiffs) => i_spiffs[int i].open_file(char path[], unsigned path_length, unsigned short flags) -> short fd:
                       char buffer[SPIFFS_MAX_FILENAME_SIZE];
                       memcpy(buffer,path,path_length+1);

                       fd = iSPIFFS_open(buffer, flags);
                   break;
                   case !isnull(i_spiffs) => i_spiffs[int i].close_file(unsigned short fd) -> int res:

                       res = iSPIFFS_close(fd);
                   break;

                   case !isnull(i_spiffs) => i_spiffs[int i].read(unsigned short fd, unsigned char data[], unsigned int len) -> int res:
                       unsigned char buffer[SPIFFS_MAX_DATA_BUFFER_SIZE];
                       unsigned int read_len, read_offset = 0;

                       for (int il = len; il > 0; il = il - SPIFFS_MAX_DATA_BUFFER_SIZE)
                       {
                           read_len = (il > SPIFFS_MAX_DATA_BUFFER_SIZE ? SPIFFS_MAX_DATA_BUFFER_SIZE : il);

                           res = iSPIFFS_read(fd, buffer, read_len);
                           if (res < 0) break; else res = len;
                           memcpy(data + read_offset, buffer, read_len);
                           read_offset += read_len;
                       }
                   break;

                   case !isnull(i_spiffs) => i_spiffs[int i].write(unsigned short fd, unsigned char data[], unsigned int len) -> int res:
                       unsigned char buffer[SPIFFS_MAX_DATA_BUFFER_SIZE];
                       unsigned int write_len, write_offset = 0;

                       for (int il = len; il > 0; il = il - SPIFFS_MAX_DATA_BUFFER_SIZE)
                       {
                           write_len = (il > SPIFFS_MAX_DATA_BUFFER_SIZE ? SPIFFS_MAX_DATA_BUFFER_SIZE : il);
                           memcpy(buffer, data + write_offset, write_len);

                           res = iSPIFFS_write(fd, buffer, write_len);
                           if (res < 0) break; else res = len;
                           write_offset += write_len;
                        }
                   break;

                   case !isnull(i_spiffs) => i_spiffs[int i].remove_file(unsigned short fd) -> int res:

                        res = iSPIFFS_remove(fd);
                   break;

                   case !isnull(i_spiffs) => i_spiffs[int i].get_file_size(unsigned short fd) -> int res:

                        res = iSPIFFS_get_size(fd);
                   break;

                   case !isnull(i_spiffs) => i_spiffs[int i].vis() -> int res:

                       res = iSPIFFS_vis();
                   break;

                   case !isnull(i_spiffs) => i_spiffs[int i].ls() -> int res:

                       res = iSPIFFS_ls();
                   break;

                   case !isnull(i_spiffs) => i_spiffs[int i].ls_struct(spiffs_stat s[]) -> int res:
                       unsigned flist_buffer[SPIFFS_MAX_FILELIST_ITEMS * sizeof(spiffs_stat)];

                       memset(flist_buffer, 0, sizeof(flist_buffer));
                       res = iSPIFFS_ls_struct(flist_buffer);
                       memcpy(s, flist_buffer, SPIFFS_MAX_FILELIST_ITEMS * sizeof(spiffs_stat));

                   break;

                   case !isnull(i_spiffs) => i_spiffs[int i].check() -> int res:

                       res = iSPIFFS_check();
                   break;

                   case !isnull(i_spiffs) => i_spiffs[int i].status(unsigned short fd, unsigned short &obj_id, unsigned int &size, unsigned char &type, unsigned short &pix, char name[]) -> int res:
                           unsigned stat_buffer[sizeof(spiffs_stat)];
                           spiffs_stat s;

                           res = iSPIFFS_status(fd, stat_buffer);
                           memcpy(&s, stat_buffer, sizeof(spiffs_stat));
                           obj_id = s.obj_id;
                           size = s.size;
                           type = s.type;
                           pix = s.pix;
                           memcpy(name, s.name, SPIFFS_MAX_FILENAME_SIZE);
                   break;

                   case !isnull(i_spiffs) => i_spiffs[int i].unmount():

                       iSPIFFS_unmount();
                   break;

                   case !isnull(i_spiffs) => i_spiffs[int i].format() -> int res:

                        res = iSPIFFS_format();
                   break;

                   case !isnull(i_spiffs) => i_spiffs[int i].tell(unsigned short fd) -> int res:

                       res = iSPIFFS_tell(fd);
                   break;

                   case !isnull(i_spiffs) => i_spiffs[int i].seek(unsigned short fd, int offs, int whence) -> int res:

                       res = iSPIFFS_seek(fd, offs, whence);
                   break;

                   case !isnull(i_spiffs) => i_spiffs[int i].rename_file(char old_path[], unsigned old_path_length, char new_path[], unsigned new_path_length) -> int res:
                       char old_buffer[SPIFFS_MAX_FILENAME_SIZE];
                       char new_buffer[SPIFFS_MAX_FILENAME_SIZE];
                       memcpy(old_buffer,old_path,old_path_length+1);
                       memcpy(new_buffer,new_path,new_path_length+1);

                       res = iSPIFFS_rename(old_buffer, new_buffer);
                   break;

                   case !isnull(i_spiffs) => i_spiffs[int i].flush(unsigned short fd) -> int res:

                       res = iSPIFFS_flush(fd);
                   break;

                   case !isnull(i_spiffs) => i_spiffs[int i].errno() -> int res:

                       res = iSPIFFS_errno();
                   break;

                   case !isnull(i_spiffs) => i_spiffs[int i].fs_info(unsigned int &total, unsigned int &used) -> int res:
                          unsigned int buffer_total[1];
                          unsigned int buffer_used[1];

                          res = iSPIFFS_info(buffer_total, buffer_used);
                          total = buffer_total[0];
                          used = buffer_used[0];
                   break;

                   case !isnull(i_spiffs) => i_spiffs[int i].gc(unsigned int size) -> int res:

                       res = iSPIFFS_gc(size);
                   break;

                   case !isnull(i_spiffs) => i_spiffs[int i].gc_quick(unsigned short max_free_pages) -> int res:

                       res = iSPIFFS_gc_quick(max_free_pages);
                   break;

               }
    }
}
