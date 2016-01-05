/****************
 * COM Ethernet
 * Rev. A
 ****************/

#pragma once

#include <xs1.h>
#include <platform.h>
 
/****************************************************************************/

#define ETHERNET_DEFAULT_TILE_P1 tile[0]

#define PORT_ETH_RST_N0 COM_PORT_1BIT_66
#define PORT_ETH_RXCLK0 COM_PORT_1BIT_14
#define PORT_ETH_RXD0 COM_PORT_4BIT_76_78_8_72
#define PORT_ETH_TXD0 COM_PORT_4BIT_4_2_6_74
#define PORT_ETH_RXDV0 COM_PORT_1BIT_68
#define PORT_ETH_TXEN0 COM_PORT_1BIT_12
#define PORT_ETH_TXCLK0 COM_PORT_1BIT_10
#define PORT_ETH_MDIOC0 COM_PORT_4BIT_60_20_56_24
#define PORT_ETH_MDIOFAKE0 INTERNAL_PORT_8BIT_NOT_CONNECTED_1 //GET RID OF THIS!?
#define PORT_ETH_ERR0 COM_PORT_1BIT_70

#define ETHERNET_DEFAULT_TILE_P2 tile[0]

#define PORT_ETH_RST_N1 COM_PORT_1BIT_18
#define PORT_ETH_RXCLK1 COM_PORT_1BIT_34
#define PORT_ETH_RXD1 COM_PORT_4BIT_46_42_38_36
#define PORT_ETH_TXD1 COM_PORT_4BIT_48_52_28_32
#define PORT_ETH_RXDV1 COM_PORT_1BIT_40
#define PORT_ETH_TXEN1 COM_PORT_1BIT_50
#define PORT_ETH_TXCLK1 COM_PORT_1BIT_58
#define PORT_ETH_MDIOC1 COM_PORT_4BIT_22_26_54_30
#define PORT_ETH_MDIOFAKE1 INTERNAL_PORT_8BIT_NOT_CONNECTED_2 //GET RID OF THIS!?
#define PORT_ETH_ERR1 INTERNAL_PORT_1BIT_NOT_CONNECTED

/****************************************************************************/

#define ETHERNET_DEFAULT_PHY_ADDRESS 0
#define PORT_ETH_RST_N 1
#define SMI_COMBINE_MDC_MDIO 1
#define SMI_MDC_BIT 0
#define SMI_MDIO_BIT 1

#ifndef ETHERNET_DEFAULT_CLKBLK_0
#define ETHERNET_DEFAULT_CLKBLK_0 on ETHERNET_DEFAULT_TILE_P1: XS1_CLKBLK_1
#endif

#ifndef ETHERNET_DEFAULT_CLKBLK_1
#define ETHERNET_DEFAULT_CLKBLK_1 on ETHERNET_DEFAULT_TILE_P1: XS1_CLKBLK_3
#endif

#ifndef ETHERNET_DEFAULT_CLKBLK_2
#define ETHERNET_DEFAULT_CLKBLK_2 on ETHERNET_DEFAULT_TILE_P2: XS1_CLKBLK_4
#endif

#ifndef ETHERNET_DEFAULT_CLKBLK_3
#define ETHERNET_DEFAULT_CLKBLK_3 on ETHERNET_DEFAULT_TILE_P2: XS1_CLKBLK_5
#endif

#ifndef PORT_ETH_FAKE0
#define PORT_ETH_FAKE0 on ETHERNET_DEFAULT_TILE_P1: XS1_PORT_8C
#endif

#ifndef PORT_ETH_FAKE1
#define PORT_ETH_FAKE1 on ETHERNET_DEFAULT_TILE_P2: XS1_PORT_8D
#endif

#define ETHERNET_DEFAULT_MII_INIT_P1_lite { \
  ETHERNET_DEFAULT_CLKBLK_0, \
  ETHERNET_DEFAULT_CLKBLK_1, \
\
    PORT_ETH_RXCLK0,                             \
    PORT_ETH_ERR0,                               \
    PORT_ETH_RXD0,                               \
    PORT_ETH_RXDV0,                              \
    PORT_ETH_TXCLK0,                             \
    PORT_ETH_TXEN0,                              \
    PORT_ETH_TXD0,                               \
    PORT_ETH_FAKE0 \
}

#define ETHERNET_DEFAULT_MII_INIT_P2_lite { \
  ETHERNET_DEFAULT_CLKBLK_2, \
  ETHERNET_DEFAULT_CLKBLK_3, \
\
    PORT_ETH_RXCLK1,                             \
    PORT_ETH_ERR1,                               \
    PORT_ETH_RXD1,                               \
    PORT_ETH_RXDV1,                              \
    PORT_ETH_TXCLK1,                             \
    PORT_ETH_TXEN1,                              \
    PORT_ETH_TXD1,                               \
    PORT_ETH_FAKE1 \
}

#define ETHERNET_DEFAULT_MII_INIT_P1 ETHERNET_DEFAULT_MII_INIT_P1_lite
#define ETHERNET_DEFAULT_MII_INIT_P2 ETHERNET_DEFAULT_MII_INIT_P2_lite

#define ETHERNET_DEFAULT_SMI_INIT_P1 {ETHERNET_DEFAULT_PHY_ADDRESS, \
                                   PORT_ETH_MDIOC0}

#define ETHERNET_DEFAULT_SMI_INIT_P2 {ETHERNET_DEFAULT_PHY_ADDRESS, \
                                   PORT_ETH_MDIOC1}
