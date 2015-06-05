#pragma once

#include <xs1.h>
#include <platform.h>

/**********************
 * Ifm Drive BLDC 5K
 **********************/

#define MOTOR_TILE 1

/* ADC */
on tile[MOTOR_TILE]: buffered in port:32 pb32_adc_data[2] = { XS1_PORT_1D ,XS1_PORT_1C };
on tile[MOTOR_TILE]: out port p1_adc_sclk = XS1_PORT_1H; // 1-bit port connecting to external ADC serial clock
on tile[MOTOR_TILE]: port p1_ready = XS1_PORT_1G; // 1-bit port used to as ready signal for pb32_adc_data ports and ADC chip
on tile[MOTOR_TILE]: out port p4_adc_mux = XS1_PORT_4C; // 4-bit port used to control multiplexor on ADC chip and ADC single-diff mode "P4C3 -> AI SGL_DIFF set"
on tile[MOTOR_TILE]: clock adc_xclk = XS1_CLKBLK_3; // Intern al XMOS clock

/* BLDC Motor, default port mode */
on tile[MOTOR_TILE]:          in  port p_ifm_hall = XS1_PORT_4E; // [p3 p2 p1 p0] -> [AUX_IO  HALL.1  HALL.2  HALL.3]
on tile[MOTOR_TILE]:          in  port p_ifm_encoder = XS1_PORT_4A; // [p3 p2 p1 p0] -> [QEI.Q  QEI.I  QEI.B  QEI.A]
on tile[MOTOR_TILE]:          in  port p_ifm_dummy_port = XS1_PORT_16A; /* any unused port */
on tile[MOTOR_TILE]:  buffered out port:32 p_ifm_motor_hi[3] = { XS1_PORT_1K,   /* Hi A */
							         							 XS1_PORT_1O,   /* Hi B */
							         							 XS1_PORT_1M }; /* Hi C */
on tile[MOTOR_TILE]: buffered out port:32 p_ifm_motor_lo[3]  = { XS1_PORT_1L,   /* Lo A */
							        							 XS1_PORT_1P,   /* Lo B */
							        							 XS1_PORT_1N }; /* Lo C */

/* LEDs, Watchdog */
on tile[MOTOR_TILE]: out port p_ifm_led_moton_wdtick_wden = XS1_PORT_4B; // [p3 p2 p1 p0] -> [LED Motor_ON WD_TICK WD_EN]

/* Expansion Port */
on tile[MOTOR_TILE]: port p_ifm_ext_d0 = XS1_PORT_1A;
on tile[MOTOR_TILE]: port p_ifm_ext_d1 = XS1_PORT_1B;
on tile[MOTOR_TILE]: port p_ifm_ext_d2 = XS1_PORT_1F;
on tile[MOTOR_TILE]: port p_ifm_ext_d3 = XS1_PORT_1E;
on tile[MOTOR_TILE]: port p_ifm_ext_d4 = XS1_PORT_1I;
on tile[MOTOR_TILE]: port p_ifm_ext_d5 = XS1_PORT_1J;

on tile[MOTOR_TILE]: port p_ifm_ext_d6to8_AUX12vEN = XS1_PORT_4F; /* [p3 p2 p1 p0] -> [EXT_D.7  EXT_D.6  EXT_D.8  AUX12vEN] */

// DX -> XS1_PORT_4D


