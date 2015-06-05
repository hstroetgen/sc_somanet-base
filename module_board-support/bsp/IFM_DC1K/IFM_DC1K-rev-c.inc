#pragma once

#include <xs1.h>
#include <platform.h>

/**********************
 * Ifm Drive BLDC 1K
 **********************/

#define MOTOR_TILE 1

/* ADC */
on tile[MOTOR_TILE]: buffered in port:32 pb32_adc_data[2] = { XS1_PORT_1D ,XS1_PORT_1C };
on tile[MOTOR_TILE]: out port p1_adc_sclk = XS1_PORT_1H; // 1-bit port connecting to external ADC serial clock
on tile[MOTOR_TILE]: port p1_ready = XS1_PORT_1G; // 1-bit port used to as ready signal for pb32_adc_data ports and ADC chip
on tile[MOTOR_TILE]: out port p4_adc_mux = XS1_PORT_4C; // 4-bit port used to control multiplexor on ADC chip and ADC single-diff mode "P4C3 -> SGL_DIFF set"
on tile[MOTOR_TILE]: clock adc_xclk = XS1_CLKBLK_3; // Intern al XMOS clock

/* BLDC Motor, default port mode */
on tile[MOTOR_TILE]:          in  port p_ifm_encoder_hall_2 = XS1_PORT_4E; /* [p3 p2 p1 p0] -> [QEI_HALL_OUT2.Q/AUX_I  QEI_HALL_OUT2.I/H1  QEI_HALL_OUT2.B/H2  QEI_HALL_OUT2.A/H3] */
on tile[MOTOR_TILE]:          in  port p_ifm_encoder_hall_1 = XS1_PORT_4A; /* [p3 p2 p1 p0] -> [QEI_HALL_OUT1.Q  QEI_HALL_OUT1.I/H1  QEI_HALL_OUT1.B/H2  QEI_HALL_OUT1.A/H3] */
on tile[MOTOR_TILE]:              port p_ifm_encoder_hall_select_ext_d4to5 = XS1_PORT_4F; /* [p3 p2 p1 p0] -> [EXT_D.5  EXT_D.4  HALL_ENC_SELEC.2  HALL_ENC_SELEC.1] */
on tile[MOTOR_TILE]:          in  port p_ifm_dummy_port = XS1_PORT_16A; /* any unused port */
on tile[MOTOR_TILE]:  buffered out port:32 p_ifm_motor_hi[4] = { 
								XS1_PORT_1K,    /* Hi A */ 
								XS1_PORT_1O,    /* Hi B */
								XS1_PORT_1M,    /* Hi C */
								XS1_PORT_1A };  /* Hi D */
on tile[MOTOR_TILE]: buffered out port:32 p_ifm_motor_lo[4]  = { 
								XS1_PORT_1L,    /* Lo A */
								XS1_PORT_1P,    /* Lo B */
								XS1_PORT_1N,    /* Lo C */
								XS1_PORT_1B };  /* Lo D */

/* LEDs, Watchdog */
on tile[MOTOR_TILE]: out port p_ifm_led_moton_wdtick_wden = XS1_PORT_4B;  /* [p3 p2 p1 p0] -> [LED Motor_ON WD_TICK WD_EN] */

/* Expansion Port */
on tile[MOTOR_TILE]: port p_ifm_ext_d0 = XS1_PORT_1I; //EXT_D.0
on tile[MOTOR_TILE]: port p_ifm_ext_d1 = XS1_PORT_1J; //EXT_D.1
on tile[MOTOR_TILE]: port p_ifm_ext_d2 = XS1_PORT_1F; //EXT_D.2
on tile[MOTOR_TILE]: port p_ifm_ext_d3 = XS1_PORT_1E; //EXT_D.3

// DX -> XS1_PORT_4D



