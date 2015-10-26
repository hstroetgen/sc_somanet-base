#pragma once

#include <xs1.h>
#include <platform.h>

/**********************
 * Ifm Drive BLDC 5K
 **********************/

#define MOTOR_TILE 1

/* ADC in DC5K */
#define ADC_DATA_A  on tile[MOTOR_TILE]: XS1_PORT_1F
#define ADC_DATA_B  on tile[MOTOR_TILE]: XS1_PORT_1E
#define ADC_SCLK    on tile[MOTOR_TILE]: XS1_PORT_1H // 1-bit port connecting to external ADC serial clock
#define ADC_READY   on tile[MOTOR_TILE]: XS1_PORT_1G // 1-bit port used to as ready signal for pb32_adc_data ports and ADC chip
#define ADC_MUX     on tile[MOTOR_TILE]: XS1_PORT_4C // 4-bit port used to control multiplexor on ADC chip and ADC single-diff mode "P4C3 -> SGL_DIFF set"
#define ADC_INT_CLK on tile[MOTOR_TILE]: XS1_CLKBLK_3 // Intern al XMOS clock



/* BLDC Motor, default port mode */
on tile[MOTOR_TILE]: in  port p_ifm_hall    = XS1_PORT_4E;           /* [p3 p2 p1 p0] -> [AUX_IO  HALL.1  HALL.2  HALL.3] */
on tile[MOTOR_TILE]: in  port p_ifm_encoder = XS1_PORT_4A;        /* [p3 p2 p1 p0] -> [QEI.Q  QEI.I  QEI.B  QEI.A] */


/* LEDs, Watchdog */
on tile[MOTOR_TILE]: out port p_ifm_led_moton_wdtick_wden = XS1_PORT_4B; /* [p3 p2 p1 p0] -> [LED Motor_ON WD_TICK WD_EN] */


/* Expansion Port in DC5K */
on tile[MOTOR_TILE]: port p_ifm_ext_d1 = XS1_PORT_1B;
on tile[MOTOR_TILE]: port p_ifm_ext_d2 = XS1_PORT_1I;
on tile[MOTOR_TILE]: port p_ifm_ext_d3 = XS1_PORT_1C;
on tile[MOTOR_TILE]: port p_ifm_ext_d4 = XS1_PORT_1D;
on tile[MOTOR_TILE]: port p_ifm_ext_d5 = XS1_PORT_1J;


on tile[MOTOR_TILE]: port p_ifm_ext_d6to8_AUX12vEN = XS1_PORT_4F; /* [p3 p2 p1 p0] -> [EXT_D.7  EXT_D.6  EXT_D.8  AUX12vEN] */


