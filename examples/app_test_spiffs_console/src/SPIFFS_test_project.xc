/*
 * SPIFFS_test_project.xc
 *
 *  Created on: 27 но€б. 2016 г.
 *      Author: w
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

//---------SPI flash definitions---------

// Ports for QuadSPI access on explorerKIT.
fl_QSPIPorts ports = {
PORT_SQI_CS,
PORT_SQI_SCLK,
PORT_SQI_SIO,
on tile[0]: XS1_CLKBLK_1
};


int main(void)
{
  FlashDataInterface i_data[2];
  FlashBootInterface i_boot;
  SPIFFSInterface i_spiffs;

  par
  {
    on tile[0]:
    {
        flash_service(ports, i_boot, i_data, 1);
    }

    on tile[1]:
    {
        spiffs_service(i_data[0], i_spiffs);
    }
    on tile[1]:
    {
        delay_milliseconds(3000);
        test_script(i_spiffs);
    }
  }

  return 0;
}
