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
    void read(char data[], unsigned nbytes, fl_BootImageInfo &bii);
    void write(char data[], unsigned nbytes);
};

void flash_service_loop(fl_SPIPorts &SPI, interface if_flash_data, interface if_flash_boot);

#endif /* FLASH_SERVICE_H_ */
