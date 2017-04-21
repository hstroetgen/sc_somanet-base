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

    [[guarded]] int get_configurations(int type, unsigned char buffer[], unsigned &n_bytes);
    [[guarded]] int set_configurations(int type, unsigned char data[n_bytes], unsigned n_bytes);
};
typedef interface FlashDataInterface FlashDataInterface;


/**
 * @brief Interface to access boot partition of SOMANET SoCs
 */
interface FlashBootInterface 
{
    /**
     * @brief NOT YET IMPLEMENTED
     */
    [[guarded]] int read(char data[], unsigned nbytes,  unsigned char image_num);
    
    /**
     * @brief Writes chunk of data to boot partition of flash
     * @param data[] Char array holding data to be written to flash
     * @param nbytes Number of bytes to be written
     * @return 0 - success 
     */
    [[guarded]] int write(char data[], unsigned nbytes);

    /**
     * @brief Prepares the boot partition for a new boot image to be written
     * @return 0 - success
     */
    [[guarded]] int prepare_boot_partition();

    /**
     * @brief Deletes the boot partition of the SoC. 
     * Note: This will remove the running program from flash, after this function is called, the device 
     * will not boot after a power cycle. 
     * 
     * @return 0 - success
     */
    [[guarded]] void erase_boot_partition(void);

    /**
     * @brief Checks if flash contains a valid factory and upgrade image
     * @return 0 - if valid images exist
     */
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


/**
 * @brief Service to access the data partition of the internal flash of Synapticon SoCs
 *
 * @param SPI  SPI port definition struct 
 * @param i_boot Interface for boot partition manipulation    
 * @param i_data Interface for data partition manipulation
 * @param n_data Number of end-points in i_data array
 */
#ifdef XCORE200
void flash_service(fl_QSPIPorts &SPI,
                   interface FlashBootInterface server ?i_boot,
                   interface FlashDataInterface server (&?i_data)[n_data], unsigned n_data);
#else
void flash_service(fl_SPIPorts &SPI,
                   interface FlashBootInterface server ?i_boot,
                   interface FlashDataInterface server (&?i_data)[n_data], unsigned n_data);
#endif
