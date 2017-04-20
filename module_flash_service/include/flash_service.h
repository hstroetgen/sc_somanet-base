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


/*  @brief Defines the maximum size of a packet coming over the interface to be written into flash
 * (in bytes)
 */
#define MAX_PACKET_SIZE 4096

/*  @brief Defines the maximum size of a packet coming over the interface to be written into flash
 * (in bytes)
 */
#define INTERMEDIATE_BUFFER_SIZE 1024


#ifdef __XC__

/**
 * @brief Interface to communicate with the Position Feedback Service.
 */
interface FlashDataInterface {

    /**
         * @brief               Read data (whole page) from SPI flash
         * @param addr          Start address of data block
         * @param size          Data size for reading
         * @param data          Pointer to data buffer
         *
         * @returns             Size of readed data or 0 in case of error
         */
    [[guarded]] int read(unsigned addr, unsigned size, unsigned char data[]);

    /**
         * @brief               Write data to SPI flash
         * @param addr          Start address for writing
         * @param size          Data size for writing
         * @param data          Pointer to data buffer
         *
         * @returns             Size of writed data or 0 in case of error
         */
    [[guarded]] int write(unsigned addr, unsigned size, unsigned char data[]);


    /**
         * @brief               Erase data block in SPI flash
         * @param addr          Start address for writing
         * @param size          Data size for writing
         * @param data          Pointer to data buffer
         *
         * @returns             Size of writed data or 0 in case of error
         */
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

/**
 * @brief Module Flash Service provides a server, which managed the flash content and is responsible for the flash access (writing/reading).
 *
 * @param SPI      SPI ports and clock blocks
 * @param i_boot   Server interface for boot service
 * @param i_data   Server interface for data services
 * @param n_data   Pattern variable for data services
 *
 */
void flash_service(fl_QSPIPorts &SPI,
                   interface FlashBootInterface server ?i_boot,
                   interface FlashDataInterface server (&?i_data)[n_data], unsigned n_data);
#else
/**
 * @brief Module Flash Service provides a server, which managed the flash content and is responsible for the flash access (writing/reading).

 *
 * @param SPI      SPI ports and clock blocks
 * @param i_boot   Server interface for boot service
 * @param i_data   Server interfaces for data service
 * @param n_data   Pattern variable for data services
 *
 */
void flash_service(fl_SPIPorts &SPI,
                   interface FlashBootInterface server ?i_boot,
                   interface FlashDataInterface server (&?i_data)[n_data], unsigned n_data);
#endif

#endif
