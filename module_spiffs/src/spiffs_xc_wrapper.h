/*
 * spiffs_xc_wrapper.h
 *
 *  Created on: Nov 15, 2016
 *      Author: simon
 */


#ifndef SPIFFS_XC_WRAPPER_H_
#define SPIFFS_XC_WRAPPER_H_

#include <xccompat.h>

void if_read_flash(CLIENT_INTERFACE(FlashDataInterface, i_data), unsigned int addr, unsigned int size, unsigned char *buf);
void if_write_flash(CLIENT_INTERFACE(FlashDataInterface, i_data), unsigned int addr, unsigned int size, unsigned char *buf);
void if_erase_flash(CLIENT_INTERFACE(FlashDataInterface, i_data), unsigned int addr, unsigned int size);

#ifdef __XC__
extern "C" {
#endif

void spiffs_init(CLIENT_INTERFACE(FlashDataInterface, i_data));

short iSPIFFS_open(char path[], unsigned short flags);
int iSPIFFS_close(unsigned short fd);
int iSPIFFS_read(unsigned short fd, unsigned char data[], unsigned int len);
int iSPIFFS_write(unsigned short fd, unsigned char data[], unsigned int len);
int iSPIFFS_remove(unsigned short fd);
int iSPIFFS_vis(void);
int iSPIFFS_ls(void);
int iSPIFFS_check(void);
int iSPIFFS_status(unsigned short fd, unsigned stat[]);
int iSPIFFS_get_size(unsigned short fd);
int iSPIFFS_rename(char old[], char newPath[]);
int iSPIFFS_format(void);
int iSPIFFS_seek(unsigned short fd, int offs, int whence);
int iSPIFFS_tell(unsigned short fd);
void iSPIFFS_unmount(void);
int iSPIFFS_flush(unsigned short fd);
int iSPIFFS_errno(void);
int iSPIFFS_info(unsigned int total[], unsigned int used[]);
int iSPIFFS_gc(unsigned int size);
int iSPIFFS_gc_quick(unsigned short max_free_pages);

#ifdef __XC__
}
#endif

#endif /* SPIFFS_XC_WRAPPER_H_ */
