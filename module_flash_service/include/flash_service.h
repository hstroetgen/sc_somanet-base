/**
 * @file flash_service.h
 * @author Synapticon GmbH <support@synapticon.com>
 */

#pragma once

#include "flash_common.h"

#ifdef XCORE200
#include <quadflash.h>
#else
#include <flash.h>
#endif

interface FlashDataInterface {
    [[guarded]] int read(unsigned addr, unsigned size, unsigned char data[]);
    [[guarded]] int write(unsigned addr, unsigned size, unsigned char data[]);
    [[guarded]] int erase(unsigned addr, unsigned size);
    [[guarded]] int get_configurations(int type, unsigned char buffer[], unsigned &n_bytes);
    [[guarded]] int set_configurations(int type, unsigned char data[n_bytes], unsigned n_bytes);
};
typedef interface FlashDataInterface FlashDataInterface;

interface FlashBootInterface {
    [[guarded]] int read(char data[], unsigned nbytes,  unsigned char image_num);
    [[guarded]] int write(char data[], unsigned nbytes);
    [[guarded]] int prepare_boot_partition();
    [[guarded]] void erase_boot_partition(void);
    [[guarded]] int validate_flashing(void);
    [[guarded]] int upgrade_image_installed(void);

    [[notification]]
    slave void notification();

    [[clears_notification]]
    int get_notification();
};

typedef interface FlashBootInterface FlashBootInterface;

enum configuration_type {
    MOTCTRL_CONFIG
};

#ifdef XCORE200
void flash_service(fl_QSPIPorts &SPI,
                   interface FlashBootInterface server ?i_boot,
                   interface FlashDataInterface server (&?i_data)[n_data], unsigned n_data);
#else
void flash_service(fl_SPIPorts &SPI,
                   interface FlashBootInterface server ?i_boot,
                   interface FlashDataInterface server (&?i_data)[n_data], unsigned n_data);
#endif
