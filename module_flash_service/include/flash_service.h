/**
 * @file flash_service.h
 * @author Synapticon GmbH <support@synapticon.com>
 */

#pragma once

#include <flash.h>

interface FlashDataInterface {
    int read(char data[], unsigned nbytes, unsigned address);
    int write(char data[], unsigned nbytes);
};

interface FlashBootInterface {
    int read(char data[], unsigned nbytes,  unsigned char image_num);
    int write(char data[], unsigned nbytes);
};

enum flash_error {
    NO_FACTORY_IMAGE=1, NO_UPGRADE_IMAGE
};

void flash_service(fl_SPIPorts &SPI,
                   interface FlashBootInterface server ?i_boot,
                   interface FlashDataInterface server i_data[n],
                   unsigned n);
