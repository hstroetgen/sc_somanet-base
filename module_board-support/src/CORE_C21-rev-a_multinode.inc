/**************
 * Core-C21-DX
 * Rev. A
 **************/

#pragma once

#include <xs1.h>
#include <platform.h>
#include <flash.h>

/*******************************************************/
/*                        NODE 0                       */
/*******************************************************/

#define NODE_0_COM_TILE 0
#define NODE_0_IFM_TILE 1

/* SPI port definitions */ 
on tile[NODE_0_COM_TILE]: fl_SPIPorts p_spi_flash_0 = { PORT_SPI_MISO_0,
 								PORT_SPI_SS_0,
 								PORT_SPI_CLK_0,
 								PORT_SPI_MOSI_0,
 								XS1_CLKBLK_2 };
/* RGB LED */
on tile[NODE_0_COM_TILE]: out port p_core_leds_0[3] = { XS1_PORT_1M,   /* Red */
					   XS1_PORT_1L,   /* Green */
					   XS1_PORT_1K }; /* Blue */


/*******************************************************/
/*                        NODE 1                       */
/*******************************************************/

#define NODE_1_COM_TILE 2
#define NODE_1_IFM_TILE 3

/* SPI port definitions */ 
on tile[NODE_1_COM_TILE]: fl_SPIPorts p_spi_flash_1 = { PORT_SPI_MISO_1,
 								PORT_SPI_SS_1,
 								PORT_SPI_CLK_1,
 								PORT_SPI_MOSI_1,
 								XS1_CLKBLK_2 };
/* RGB LED */
on tile[NODE_1_COM_TILE]: out port p_core_leds_1[3] = { XS1_PORT_1M,   /* Red */
					   XS1_PORT_1L,   /* Green */
					   XS1_PORT_1K }; /* Blue */


/*******************************************************/
/*                        NODE 2                       */
/*******************************************************/

#define NODE_2_COM_TILE 4
#define NODE_2_IFM_TILE 5

/* SPI port definitions */ 
on tile[NODE_2_COM_TILE]: fl_SPIPorts p_spi_flash_2 = { PORT_SPI_MISO_2,
 								PORT_SPI_SS_2,
 								PORT_SPI_CLK_2,
 								PORT_SPI_MOSI_2,
 								XS1_CLKBLK_2 };
/* RGB LED */
on tile[NODE_2_COM_TILE]: out port p_core_leds_2[3] = { XS1_PORT_1M,   /* Red */
					   XS1_PORT_1L,   /* Green */
					   XS1_PORT_1K }; /* Blue */


// 
//              EXPAND HERE IF NEEDED
//                      __
//                     |  |
//                   __|  |__	
//                   \      /
//                    \    /
//                     \  /
//                      \/
// 





