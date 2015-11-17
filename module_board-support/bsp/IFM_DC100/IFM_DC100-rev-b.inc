/***************************
 * IFM Drive DC-100
 * Rev. B
 ***************************/

#pragma once

#include <xs1.h>
#include <platform.h>

#define IFM_RESOLUTION 740

/* A4935 control ports */
//on tile[IFM_TILE]: port p_ifm_coastn = XS1_PORT_1G;
//on tile[IFM_TILE]: out port p_ifm_esf_rstn_pwml_pwmh = XS1_PORT_4F;
//on tile[IFM_TILE]: port p_ifm_ff1 = XS1_PORT_1H;
//on tile[IFM_TILE]: port p_ifm_ff2 = XS1_PORT_1I;

/* ADC */
on tile[IFM_TILE]: in buffered  port:32 p_ifm_adc_misoa = XS1_PORT_1D;
on tile[IFM_TILE]: in buffered  port:32 p_ifm_adc_misob = XS1_PORT_1C;
on tile[IFM_TILE]: buffered out port:32 p_ifm_adc_sclk_conv_mosib_mosia = XS1_PORT_4C;

/* BLDC Motor */
/* PWM PORTS*/
#define PWM_PORT_A_HIGH_SIDE IFM_PORT_1BIT_62 
#define PWM_PORT_B_HIGH_SIDE IFM_PORT_1BIT_26
#define PWM_PORT_C_HIGH_SIDE IFM_PORT_1BIT_54
#define PWM_PORT_A_LOW_SIDE IFM_PORT_1BIT_56
#define PWM_PORT_B_LOW_SIDE IFM_PORT_1BIT_52
#define PWM_PORT_C_LOW_SIDE IFM_PORT_1BIT_24

#define PWM_CLOCK_SRC IFM_TILE_CLOCK_0
#define PWM_DUMMY_PORT_TRIGGER IFM_UNUSED_PORT_0

#define PWM_PORTS { 														\
    {PWM_PORT_A_HIGH_SIDE, PWM_PORT_B_HIGH_SIDE, PWM_PORT_C_HIGH_SIDE},		\
    {PWM_PORT_A_LOW_SIDE, PWM_PORT_B_LOW_SIDE, PWM_PORT_C_LOW_SIDE},		\
    null,																	\
    null,																	\
	PWM_CLOCK_SRC,       													\
	PWM_DUMMY_PORT_TRIGGER													\
}

on tile[IFM_TILE]: in  port p_ifm_hall = XS1_PORT_4E;
on tile[IFM_TILE]: in port p_ifm_encoder = XS1_PORT_4A; /* Encoder */

/* LEDs, Watchdog */

/************ WATCHDOG PORT DEFINITIONS *********************/
#define WATCHDOG_TICK_PORT IFM_PORT_1BIT_6
#define WATCHDOG_EN_PORT IFM_PORT_4BIT_36_46_48_50 

#define WATCHDOG_PORTS {  		\
    WATCHDOG_EN_PORT,         	\
    WATCHDOG_TICK_PORT          \
}

/************** FET DRIVER PORT DEFINITIONS ***********************/
#define FET_DRIVER_COAST_PORT IFM_PORT_1BIT_4 
#define FET_DRIVER_ESF_RST_PWML_PWMH_PORT IFM_PORT_4BIT_68_70_72_74 
#define FET_DRIVER_FF1 IFM_PORT_1BIT_16
#define FET_DRIVER_FF2 IFM_PORT_1BIT_78

#define FET_DRIVER_PORTS {    			\
	FET_DRIVER_COAST_PORT,        		\
    FET_DRIVER_ESF_RST_PWML_PWMH_PORT, 	\
    FET_DRIVER_FF1,					  	\
    FET_DRIVER_FF2   					\
}

/* Expansion Ports */
on tile[IFM_TILE]: port p_ifm_ext_d[4] ={ XS1_PORT_1A,
									  XS1_PORT_1E,
									  XS1_PORT_1J,
									  XS1_PORT_1B };
