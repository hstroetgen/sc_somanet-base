/**
 * @file flash_service.h
 * @author Synapticon GmbH <support@synapticon.com>
 */

#pragma once

#include <flash.h>

#define DATA_PAGES_PER_TYPE 4

interface FlashDataInterface {
    int get_configurations(int type, unsigned char buffer[], unsigned &n_bytes);
    int set_configurations(int type, unsigned char data[n_bytes], unsigned n_bytes);
};

interface FlashBootInterface {
    int read(char data[], unsigned nbytes,  unsigned char image_num);
    int write(char data[], unsigned nbytes);
};

enum flash_error {
    NO_FACTORY_IMAGE=1, NO_UPGRADE_IMAGE
};

enum configuration_type {
    MOTCTRL_CONFIG
};

void flash_service(fl_SPIPorts &SPI,
                   interface FlashBootInterface server ?i_boot,
                   interface FlashDataInterface server i_data[2]);
