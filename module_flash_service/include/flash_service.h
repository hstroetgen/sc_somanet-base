/*
 * flash_service.h
 *
 *  Created on: 17.12.2015
 *      Author: hstroetgen
 */

#ifndef FLASH_SERVICE_H_
#define FLASH_SERVICE_H_

interface if_flash_data
{
    void read(char data[], unsigned nbytes, unsigned address);
    unsigned write(char data[], unsigned nbytes);
};

interface if_flash_boot
{
    unsigned read(char data[], unsigned nbytes,  unsigned char image_num);
    unsigned write(char data[], unsigned nbytes);
};

typedef enum flash_error {NO_FACTORY_IMAGE=1, NO_UPGRADE_IMAGE};

void flash_service(fl_SPIPorts &SPI, interface if_flash_boot server ?if_boot, interface if_flash_data server if_data);

#endif /* FLASH_SERVICE_H_ */
