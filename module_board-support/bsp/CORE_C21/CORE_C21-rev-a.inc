/**************
 * Core-C21-DX
 * Rev. A
 **************/

#pragma once

#include <xs1.h>
#include <platform.h>
#include <flash.h>

/* For single-node setups */
#define APP_TILE 0
#define IFM_TILE 1

/* LED PORTS */
#define CORE_LED_PORT_RED on tile[APP_TILE]: XS1_PORT_1M
#define CORE_LED_PORT_GREEN on tile[APP_TILE]: XS1_PORT_1L
#define CORE_LED_PORT_BLUE on tile[APP_TILE]: XS1_PORT_1K

 /* IFM PORTS */
#define IFM_PORT_1BIT_2 on tile[IFM_TILE]: XS1_PORT_1E
#define IFM_PORT_1BIT_4 on tile[IFM_TILE]: XS1_PORT_1G
#define IFM_PORT_1BIT_6 on tile[IFM_TILE]: XS1_PORT_1F
#define IFM_PORT_1BIT_16 on tile[IFM_TILE]: XS1_PORT_1H
#define IFM_PORT_1BIT_22 on tile[IFM_TILE]: XS1_PORT_1J
#define IFM_PORT_1BIT_24 on tile[IFM_TILE]: XS1_PORT_1N
#define IFM_PORT_1BIT_26 on tile[IFM_TILE]: XS1_PORT_1O
#define IFM_PORT_1BIT_28 on tile[IFM_TILE]: XS1_PORT_1A
#define IFM_PORT_1BIT_32 on tile[IFM_TILE]: XS1_PORT_1B
#define IFM_PORT_1BIT_40 on tile[IFM_TILE]: XS1_PORT_1C
#define IFM_PORT_1BIT_42 on tile[IFM_TILE]: XS1_PORT_1D
#define IFM_PORT_1BIT_52 on tile[IFM_TILE]: XS1_PORT_1P
#define IFM_PORT_1BIT_54 on tile[IFM_TILE]: XS1_PORT_1M
#define IFM_PORT_1BIT_56 on tile[IFM_TILE]: XS1_PORT_1L
#define IFM_PORT_1BIT_62 on tile[IFM_TILE]: XS1_PORT_1K
#define IFM_PORT_1BIT_78 on tile[IFM_TILE]: XS1_PORT_1I

#define IFM_PORT_4BIT_38_44_30_34 on tile[IFM_TILE]: XS1_PORT_4A
#define IFM_PORT_4BIT_36_46_48_50 on tile[IFM_TILE]: XS1_PORT_4B
#define IFM_PORT_4BIT_20_58_10_8 on tile[IFM_TILE]: XS1_PORT_4C
#define IFM_PORT_4BIT_66_76_80 on tile[IFM_TILE]: XS1_PORT_4E
#define IFM_PORT_4BIT_68_70_72_74 on tile[IFM_TILE]: XS1_PORT_4F

#if defined(COM_PORT_1B_18) || defined(COM_PORT_1B_10) || defined(COM_PORT_1B_34) || defined(COM_PORT_1B_50) || defined(COM_PORT_1B_40) || defined(COM_PORT_1B_70) || defined(COM_PORT_16B_48_52_46_42_38_36_28_60_20_56_24_54_30) || defined(COM_PORT_16B_76_78_4_2_6_74_8_72_70_12_68_66_16_64_62_44)
	#error "CORE C21 does not support a COM modules"
#endif