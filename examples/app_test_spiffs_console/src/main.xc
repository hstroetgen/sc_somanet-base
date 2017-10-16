/* PLEASE REPLACE "CORE_BOARD_REQUIRED" WITH AN APPROPRIATE BOARD SUPPORT FILE FROM module_board-support */
#include <CORE_BOARD_REQUIRED>

/**
 * @file main.xc
 * @brief Demo application illustrates usage of module_rtc
 * @author Synapticon GmbH <support@synapticon.com>
 */

#include <xs1.h>
#include <platform.h>
#include <flash_service.h>
#include <spiffs_service.h>
#include <command_processor.h>

#ifdef XCORE200
#include <quadflash.h>
#else
#include <flash.h>
#endif

#define MAX_SPIFFS_INTERFACES 2
#define MAX_FLASH_DATA_INTERFACES 2


int main(void)
{
  FlashDataInterface i_data[MAX_FLASH_DATA_INTERFACES];
  FlashBootInterface i_boot;
  SPIFFSInterface i_spiffs[MAX_SPIFFS_INTERFACES];

  par
  {
    on tile[COM_TILE]:
    {
#ifdef XCORE200
        flash_service(p_qspi_flash, i_boot, i_data, 1);
#else
        flash_service(p_spi_flash, i_boot, i_data, 1);
#endif
    }

    on tile[APP_TILE]:
    {
        spiffs_console(i_spiffs[0]);
    }

    on tile[IF2_TILE]:
    {
        spiffs_service(i_data[0], i_spiffs, 1);
    }
  }

  return 0;
}
