/***************************
 * IFM Drive DC-100
 * Rev. B
 ***************************/

#pragma once

#include <xs1.h>
#include <platform.h>

#define IFM_RESOLUTION 740

/* A4935 control ports */
on tile[IFM_TILE]: port p_ifm_coastn = XS1_PORT_1G;
on tile[IFM_TILE]: out port p_ifm_esf_rstn_pwml_pwmh = XS1_PORT_4F;
on tile[IFM_TILE]: port p_ifm_ff1 = XS1_PORT_1H;
on tile[IFM_TILE]: port p_ifm_ff2 = XS1_PORT_1I;

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
on tile[IFM_TILE]: out port p_ifm_shared_leds_wden = XS1_PORT_4B; /* BlueGreenRed_WDEN */
on tile[IFM_TILE]: out port p_ifm_wd_tick = XS1_PORT_1F; /* WatchdogTick */

/* Expansion Ports */
on tile[IFM_TILE]: port p_ifm_ext_d[4] ={ XS1_PORT_1A,
									  XS1_PORT_1E,
									  XS1_PORT_1J,
									  XS1_PORT_1B };
