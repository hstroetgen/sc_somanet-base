/*
 * spiffs_service.h
 *
 *  Created on: Nov 15, 2016
 *      Author: simon
 */


#ifndef SPIFFS_SERVICE_H_
#define SPIFFS_SERVICE_H_

/**
 * @brief SPIFFS Service, handling all file system operations
 */

void if_read_flash(CLIENT_INTERFACE(FlashDataInterface, i_data), unsigned int addr, unsigned int size, unsigned char *buf);
void if_write_flash(CLIENT_INTERFACE(FlashDataInterface, i_data), unsigned int addr, unsigned int size, unsigned char *buf);
void if_erase_flash(CLIENT_INTERFACE(FlashDataInterface, i_data), unsigned int addr, unsigned int size);

void spiffs_service(CLIENT_INTERFACE(FlashDataInterface, i_data));

#endif /* SPIFFS_SERVICE_H_ */
