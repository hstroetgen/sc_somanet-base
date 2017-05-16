/**
 * @file flash_common.c
 * @brief Flash device access
 * @author Synapticon GmbH <support@synapticon.com>
 */

#include <flash_common.h>


#ifdef XCORE200
#include <quadflash.h>
#else
#include <flash.h>
#endif

#include <print.h>

#ifdef XCORE200
fl_QSPIPorts *SPI_port;
#else
fl_SPIPorts *SPI_port;
#endif

/**
 * @brief Saves the spi port in a global variable.
 * @param SPI   Struct with the port definitions.
 */
#ifdef XCORE200
void flash_init(fl_QSPIPorts *SPI)
{
    SPI_port = SPI;
    fl_connect(SPI_port);
}
#else
void flash_init(fl_SPIPorts *SPI)

{
    SPI_port = SPI;
    connect_to_flash();
}
#endif

/**
 * @brief Connect to the flash. Should be called before any accessing the flash memory.
 * @return  0 if connecting was successful.
 */
int connect_to_flash(void) {

    int result = fl_connect(SPI_port);
    if (result != 0) {
        printstrln("Could not connect to flash memory \n");
    }

    return result;
}


