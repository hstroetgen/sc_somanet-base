/**
 * @file flash_service.h
 * @author Synapticon GmbH <support@synapticon.com>
 */

#pragma once

#include "flash_common.h"
#include <flash.h>

interface FlashDataInterface {
    int get_configurations(int type, unsigned char buffer[], unsigned &n_bytes);
    int set_configurations(int type, unsigned char data[n_bytes], unsigned n_bytes);
};
typedef interface FlashDataInterface FlashDataInterface;

interface FlashBootInterface {
    int read(char data[], unsigned nbytes,  unsigned char image_num);
    int write(char data[], unsigned nbytes);
    int prepare_boot_partition();
    int erase_upgrade_image(void);
    int validate_flashing(void);
    int upgrade_image_installed(void);
};

typedef interface FlashBootInterface FlashBootInterface;

enum configuration_type {
    MOTCTRL_CONFIG
};

void flash_service(fl_SPIPorts &SPI,
                   interface FlashBootInterface server ?i_boot,
                   interface FlashDataInterface server (&?i_data)[n_data], unsigned n_data, const static int flash_page_size);
