/**********************
 * Ifm Drive BLDC 1K
 **********************/

#pragma once

#include <xs1.h>
#include <platform.h>

#define IFM_DC1K

#define SET_ALL_AS_HALL 0b0000
#define SET_ALL_AS_QEI 0b0011
#define SET_PORT1_AS_HALL_PORT2_AS_QEI 0b0010
#define SET_PORT1_AS_QEI_PORT2_AS_HALL 0b0001
#define DC1K
#define AD7265

#define PWM_CLOCK_SRC CLOCK_MOTOR_TILE_0

#define PWM_PORT_A_HIGH_SIDE IFM_PORT_1BIT_62 
#define PWM_PORT_B_HIGH_SIDE IFM_PORT_1BIT_26
#define PWM_PORT_C_HIGH_SIDE IFM_PORT_1BIT_54
#define PWM_PORT_D_HIGH_SIDE IFM_PORT_1BIT_28
								
#define PWM_PORT_A_LOW_SIDE IFM_PORT_1BIT_56
#define PWM_PORT_B_LOW_SIDE IFM_PORT_1BIT_52
#define PWM_PORT_C_LOW_SIDE IFM_PORT_1BIT_24
#define PWM_PORT_D_LOW_SIDE IFM_PORT_1BIT_32

#define PWM_PORTS {																					\
	PWM_CLOCK_SRC,																					\
																									\
	{PWM_PORT_A_HIGH_SIDE, PWM_PORT_B_HIGH_SIDE, PWM_PORT_C_HIGH_SIDE},								\
	{PWM_PORT_A_LOW_SIDE, PWM_PORT_B_LOW_SIDE, PWM_PORT_C_LOW_SIDE},								\
	PWM_PORT_D_HIGH_SIDE,																			\
	PWM_PORT_D_LOW_SIDE																				\
}

// ADC PORT DEFINITIONS
#define ADC_DATA_A IFM_PORT_1BIT_42 
#define ADC_DATA_B IFM_PORT_1BIT_40 
#define ADC_SCLK IFM_PORT_1BIT_16 
#define ADC_READY IFM_PORT_1BIT_4 
#define ADC_MUX IFM_PORT_4BIT_20_58_10_8 // 4-bit port used to control multiplexor on ADC. ADC single-diff mode p20
#define ADC_INT_CLK CLOCK_MOTOR_TILE_2

#define AD7265_PORTS {	\
	ADC_INT_CLK,		\
						\
	ADC_DATA_A,			\
	ADC_DATA_B,			\
	ADC_SCLK,			\
	ADC_READY,			\
	ADC_MUX				\
}

#define SELECTION_HALL_ENCODER_PORT IFM_PORT_4BIT_68_70_72_74

/* HALL SENSOR PORTS */
#define HALL_PORT IFM_PORT_4BIT_38_44_30_34

#define HALL_PORTS {\
	HALL_PORT		\
}

/* ENCODER PORT */
#define ENCODER_PORT IFM_PORT_4BIT_XXX

#define ENCODER_PORTS {	\
	ENCODER_PORT		\
}

/************** QEI PORT DEFINITIONS ***********************/
#define QEI_PORT IFM_PORT_4BIT_36_46_48_50

/************ WATCHDOG PORT DEFINITIONS *********************/
#define WATCHDOG_TICK_PORT null
#define WATCHDOG_EN_PORT IFM_PORT_4BIT_36_46_48_50 

#define WATCHDOG_PORTS {		\
	WATCHDOG_TICK_PORT,			\
 	WATCHDOG_EN_PORT			\
}

/************** GPIO PORT DEFINITIONS ***********************/
#define GPIO_D0 IFM_PORT_1BIT_6
#define GPIO_D1 IFM_PORT_1BIT_78
#define GPIO_D2 IFM_PORT_1BIT_2
#define GPIO_D3 IFM_PORT_1BIT_22

#define FET_DRIVER_PORTS {	\
	null,					\
	null,					\
	null,					\
	null					\
}



