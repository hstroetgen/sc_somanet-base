/*
 * flash_boot.h
 *
 *  Created on: 17.12.2015
 *      Author: hstroetgen
 */

/**
 * @brief Provides functions for boot partition access.
 */

#ifndef FLASH_BOOT_H_
#define FLASH_BOOT_H_


int flash_write_boot(char data[], unsigned size);
int flash_read_boot(char data[], unsigned size);

#endif /* FLASH_BOOT_H_ */
