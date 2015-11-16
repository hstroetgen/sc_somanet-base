/***************************
 * IFM Drive DC-100
 * Rev. A
 ***************************/

#pragma once

#include <xs1.h>
#include <platform.h>

#define ADC_RESOLUTION 740

/* FET DRIVER A4935 control ports */
#define FETDRV_PORT_COASTN IFM_PORT_1BIT_4
#define FETDRV_PORT_ESF_RSTN_PWML_PWMH IFM_PORT_4BIT_68_70_72_74
#define FETDRV_PORT_FF1 IFM_PORT_1BIT_16
#define FETDRV_PORT_FF2 IFM_PORT_1BIT_10

#define FET_DRIVER_PORTS {			\
	FETDRV_PORT_COASTN, 			\
	FETDRV_PORT_ESF_RSTN_PWML_PWMH,	\
	FETDRV_PORT_FF1,				\
	FETDRV_PORT_FF2					\
}

/* ADC */
#define ADC_PORT_MISO_A IFM_PORT_1BIT_42
#define ADC_PORT_MISO_B IFM_PORT_1BIT_40
#define ADC_PORT_SCLK_CONV_MOSI_B_MOSI_A IFM_PORT_4BIT_20_58_10_8
#define ADC_PORT_DUMMY XS1_PORT_16A	
#define ADC_CLOCK IFM_TILE_CLOCK_1

#define ADC_PORTS {						\
	ADC_PORT_MISO_A,					\
	ADC_PORT_MISO_B,					\
	ADC_PORT_SCLK_CONV_MOSI_B_MOSI_A,	\
	ADC_PORT_DUMMY,						\
										\
	ADC_CLOCK							\
}

/* HALL SENSOR PORT*/
#define HALL_PORT IFM_PORT_1BIT_2

/* PWM PORTS*/
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

/* ENCODER PORT */
#define ENCODER_PORT IFM_PORT_4BIT_XXX; /* Encoder */

/* LEDs, Watchdog */
on tile[IFM_TILE]: out port p_ifm_shared_leds_wden = XS1_PORT_4B; /* BlueGreenRed_WDEN */
on tile[IFM_TILE]: out port p_ifm_wd_tick = XS1_PORT_1F; /* WatchdogTick */

/* GPIO_PORTS */
#define GPIO_D0 IFM_PORT_1B_28
#define GPIO_D1 IFM_PORT_1B_2
#define GPIO_D2 IFM_PORT_1B_22
#define GPIO_D3 IFM_PORT_1B_32

