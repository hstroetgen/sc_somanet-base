/*
 * spiffs_xc_wrapper.h
 *
 *  Created on: Nov 15, 2016
 *      Author: simon
 */


#ifndef SPIFFS_XC_WRAPPER_H_
#define SPIFFS_XC_WRAPPER_H_


void if_read_flash(CLIENT_INTERFACE(FlashDataInterface, i_data), unsigned int addr, unsigned int size, unsigned char *buf);
void if_write_flash(CLIENT_INTERFACE(FlashDataInterface, i_data), unsigned int addr, unsigned int size, unsigned char *buf);
void if_erase_flash(CLIENT_INTERFACE(FlashDataInterface, i_data), unsigned int addr, unsigned int size);

void spiffs_init(CLIENT_INTERFACE(FlashDataInterface, i_data));

unsigned short iSPIFFS_open(char path[], unsigned short flags);
int iSPIFFS_close(void);
int iSPIFFS_read(unsigned char data[], unsigned int len);
int iSPIFFS_write(unsigned char data[], unsigned int len);
int iSPIFFS_remove(void);
int iSPIFFS_vis(void);
int iSPIFFS_check(void);
int iSPIFFS_status(unsigned short obj_id, unsigned int size, unsigned char type, unsigned short pix, unsigned char name[]);

#endif /* SPIFFS_XC_WRAPPER_H_ */
