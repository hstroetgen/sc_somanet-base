#pragma once

#include <xs1.h>
#include <platform.h>

/**********************
 * Ifm Drive BLDC 1K
 **********************/

#define SET_ALL_AS_HALL 0b0000
#define SET_ALL_AS_QEI 0b0011
#define SET_PORT1_AS_HALL_PORT2_AS_QEI 0b0010
#define SET_PORT1_AS_QEI_PORT2_AS_HALL 0b0001
#define DC1K
#define AD7265

#define ADC_DATA_A on tile[IFM_TILE]: XS1_PORT_1D
#define ADC_DATA_B on tile[IFM_TILE]: XS1_PORT_1C
#define ADC_SCLK on tile[IFM_TILE]: XS1_PORT_1H // 1-bit port connecting to external ADC serial clock
#define ADC_READY on tile[IFM_TILE]: XS1_PORT_1G // 1-bit port used to as ready signal for pb32_adc_data ports and ADC chip
#define ADC_MUX on tile[IFM_TILE]: XS1_PORT_4C // 4-bit port used to control multiplexor on ADC chip and ADC single-diff mode "P4C3 -> SGL_DIFF set"
#define ADC_INT_CLK on tile[IFM_TILE]: XS1_CLKBLK_3 // Intern al XMOS clock

/* BLDC Motor, default port mode */
on tile[IFM_TILE]: in  port p_ifm_hall = XS1_PORT_4E; /* [p3 p2 p1 p0] -> [QEI_HALL_OUT2.Q/AUX_I  QEI_HALL_OUT2.I/H1  QEI_HALL_OUT2.B/H2  QEI_HALL_OUT2.A/H3] */
on tile[IFM_TILE]: in  port p_ifm_encoder = XS1_PORT_4A; /* [p3 p2 p1 p0] -> [QEI_HALL_OUT1.Q  QEI_HALL_OUT1.I/H1  QEI_HALL_OUT1.B/H2  QEI_HALL_OUT1.A/H3] */
on tile[IFM_TILE]:     port p_ifm_encoder_hall_select_ext_d4to5 = XS1_PORT_4F; /* [p3 p2 p1 p0] -> [EXT_D.5  EXT_D.4  HALL_ENC_SELEC.2  HALL_ENC_SELEC.1] */
on tile[IFM_TILE]: in  port p_ifm_dummy_port = XS1_PORT_16A; /* any unused port */
on tile[IFM_TILE]: buffered out port:32 p_ifm_motor_hi[4] = { 
								XS1_PORT_1K,    /* Hi A */ 
								XS1_PORT_1O,    /* Hi B */
								XS1_PORT_1M,    /* Hi C */
								XS1_PORT_1A };  /* Hi D */
on tile[IFM_TILE]: buffered out port:32 p_ifm_motor_lo[4]  = { 
								XS1_PORT_1L,    /* Lo A */
								XS1_PORT_1P,    /* Lo B */
								XS1_PORT_1N,    /* Lo C */
								XS1_PORT_1B };  /* Lo D */

/* LEDs, Watchdog */
on tile[IFM_TILE]: out port  p_ifm_led_moton_wdtick_wden = XS1_PORT_4B;  /* [p3 p2 p1 p0] -> [LED Motor_ON WD_TICK WD_EN] */


/* Expansion Port */
#define GPIO_D0 on tile[IFM_TILE]: XS1_PORT_1I //EXT_D.0
#define GPIO_D1 on tile[IFM_TILE]: XS1_PORT_1J //EXT_D.1
#define GPIO_D2 on tile[IFM_TILE]: XS1_PORT_1F //EXT_D.2
#define GPIO_D3 on tile[IFM_TILE]: XS1_PORT_1E //EXT_D.3

// DX -> XS1_PORT_4D


