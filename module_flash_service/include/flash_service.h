/**
 * @file flash_service.h
 * @author Synapticon GmbH <support@synapticon.com>
 */

#pragma once

interface flash_data_interface {
    void read(char data[], unsigned nbytes, unsigned address);
    unsigned write(char data[], unsigned nbytes);
};

interface flash_boot_interface {
    unsigned read(char data[], unsigned nbytes,  unsigned char image_num);
    unsigned write(char data[], unsigned nbytes);
};

typedef enum flash_error {
    NO_FACTORY_IMAGE=1, NO_UPGRADE_IMAGE
};

void flash_service(fl_SPIPorts &SPI,
                   interface flash_boot_interface server ?i_boot,
                   interface flash_data_interface server i_data[n],
                   unsigned n);
