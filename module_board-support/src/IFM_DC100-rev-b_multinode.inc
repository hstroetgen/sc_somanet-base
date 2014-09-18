/***************************
 * IFM Drive DC-100
 * Rev. B
 ***************************/

#pragma once

#include <xs1.h>
#include <platform.h>

/*******************************************************/
/*                        NODE 0                       */
/*******************************************************/

/* A4935 control ports */
on tile[NODE_0_IFM_TILE]: port p_ifm_coastn_0 = XS1_PORT_1G;
on tile[NODE_0_IFM_TILE]: out port p_ifm_esf_rstn_pwml_pwmh_0 = XS1_PORT_4F;
on tile[NODE_0_IFM_TILE]: port p_ifm_ff1_0 = XS1_PORT_1H;
on tile[NODE_0_IFM_TILE]: port p_ifm_ff2_0 = XS1_PORT_1I;

/* ADC */
on tile[NODE_0_IFM_TILE]: in buffered  port:32 p_ifm_adc_misoa_0 = XS1_PORT_1D;
on tile[NODE_0_IFM_TILE]: in buffered  port:32 p_ifm_adc_misob_0 = XS1_PORT_1C;
on tile[NODE_0_IFM_TILE]: buffered out port:32 p_ifm_adc_sclk_conv_mosib_mosia_0 = XS1_PORT_4C;
on tile[NODE_0_IFM_TILE]: in           port p_ifm_dummy_port_0 = XS1_PORT_16A; /* any unused port */

/* BLDC Motor */
on tile[NODE_0_IFM_TILE]:          in  port p_ifm_hall_0 = XS1_PORT_4E;
on tile[NODE_0_IFM_TILE]: buffered out port:32 p_ifm_motor_hi_0[3] = { XS1_PORT_1K,   /* Hi A */
							XS1_PORT_1O,   /* Hi B */
							XS1_PORT_1M }; /* Hi C */
on tile[NODE_0_IFM_TILE]: buffered out port:32 p_ifm_motor_lo_0[3] = { XS1_PORT_1L,   /* Lo A */
							  XS1_PORT_1P,   /* Lo B */
							  XS1_PORT_1N }; /* Lo C */
on tile[NODE_0_IFM_TILE]: in port p_ifm_encoder_0 = XS1_PORT_4A; /* Encoder */

/* LEDs, Watchdog */
on tile[NODE_0_IFM_TILE]: out port p_ifm_shared_leds_wden_0 = XS1_PORT_4B; /* BlueGreenRed_WDEN */
on tile[NODE_0_IFM_TILE]: out port p_ifm_wd_tick_0 = XS1_PORT_1F; /* WatchdogTick */

/* Expansion Ports */
on tile[NODE_0_IFM_TILE]: port p_ifm_ext_d_0[4] ={ XS1_PORT_1A,
									  XS1_PORT_1E,
									  XS1_PORT_1J,
									  XS1_PORT_1B };

/*******************************************************/
/*                        NODE 1                       */
/*******************************************************/

/* A4935 control ports */
on tile[NODE_1_IFM_TILE]: port p_ifm_coastn_1 = XS1_PORT_1G;
on tile[NODE_1_IFM_TILE]: out port p_ifm_esf_rstn_pwml_pwmh_1 = XS1_PORT_4F;
on tile[NODE_1_IFM_TILE]: port p_ifm_ff1_1 = XS1_PORT_1H;
on tile[NODE_1_IFM_TILE]: port p_ifm_ff2_1 = XS1_PORT_1I;

/* ADC */
on tile[NODE_1_IFM_TILE]: in buffered  port:32 p_ifm_adc_misoa_1 = XS1_PORT_1D;
on tile[NODE_1_IFM_TILE]: in buffered  port:32 p_ifm_adc_misob_1 = XS1_PORT_1C;
on tile[NODE_1_IFM_TILE]: buffered out port:32 p_ifm_adc_sclk_conv_mosib_mosia_1 = XS1_PORT_4C;
on tile[NODE_1_IFM_TILE]: in           port p_ifm_dummy_port_1 = XS1_PORT_16A; /* any unused port */

/* BLDC Motor */
on tile[NODE_1_IFM_TILE]:          in  port p_ifm_hall_1 = XS1_PORT_4E;
on tile[NODE_1_IFM_TILE]: buffered out port:32 p_ifm_motor_hi_1[3] = { XS1_PORT_1K,   /* Hi A */
							XS1_PORT_1O,   /* Hi B */
							XS1_PORT_1M }; /* Hi C */
on tile[NODE_1_IFM_TILE]: buffered out port:32 p_ifm_motor_lo_1[3] = { XS1_PORT_1L,   /* Lo A */
							  XS1_PORT_1P,   /* Lo B */
							  XS1_PORT_1N }; /* Lo C */
on tile[NODE_1_IFM_TILE]: in port p_ifm_encoder_1 = XS1_PORT_4A; /* Encoder */

on tile[NODE_1_IFM_TILE]: out port p_ifm_shared_leds_wden_1 = XS1_PORT_4B; /* BlueGreenRed_WDEN */
on tile[NODE_1_IFM_TILE]: out port p_ifm_wd_tick_1 = XS1_PORT_1F; /* WatchdogTick */

/* Expansion Ports */
on tile[NODE_1_IFM_TILE]: port p_ifm_ext_d_1[4] ={ XS1_PORT_1A,
									  XS1_PORT_1E,
									  XS1_PORT_1J,
									  XS1_PORT_1B };

/*******************************************************/
/*                        NODE 2                       */
/*******************************************************/

/* A4935 control ports */
on tile[NODE_2_IFM_TILE]: port p_ifm_coastn_2 = XS1_PORT_1G;
on tile[NODE_2_IFM_TILE]: out port p_ifm_esf_rstn_pwml_pwmh_2 = XS1_PORT_4F;
on tile[NODE_2_IFM_TILE]: port p_ifm_ff1_2 = XS1_PORT_1H;
on tile[NODE_2_IFM_TILE]: port p_ifm_ff2_2 = XS1_PORT_1I;

/* ADC */
on tile[NODE_2_IFM_TILE]: in buffered  port:32 p_ifm_adc_misoa_2 = XS1_PORT_1D;
on tile[NODE_2_IFM_TILE]: in buffered  port:32 p_ifm_adc_misob_2 = XS1_PORT_1C;
on tile[NODE_2_IFM_TILE]: buffered out port:32 p_ifm_adc_sclk_conv_mosib_mosia_2 = XS1_PORT_4C;
on tile[NODE_2_IFM_TILE]: in           port p_ifm_dummy_port_2 = XS1_PORT_16A; /* any unused port */

/* BLDC Motor */
on tile[NODE_2_IFM_TILE]:          in  port p_ifm_hall_2 = XS1_PORT_4E;
on tile[NODE_2_IFM_TILE]: buffered out port:32 p_ifm_motor_hi_2[3] = { XS1_PORT_1K,   /* Hi A */
							XS1_PORT_1O,   /* Hi B */
							XS1_PORT_1M }; /* Hi C */
on tile[NODE_2_IFM_TILE]: buffered out port:32 p_ifm_motor_lo_2[3] = { XS1_PORT_1L,   /* Lo A */
							  XS1_PORT_1P,   /* Lo B */
							  XS1_PORT_1N }; /* Lo C */
on tile[NODE_2_IFM_TILE]: in port p_ifm_encoder_2 = XS1_PORT_4A; /* Encoder */

on tile[NODE_2_IFM_TILE]: out port p_ifm_shared_leds_wden_2 = XS1_PORT_4B; /* BlueGreenRed_WDEN */
on tile[NODE_2_IFM_TILE]: out port p_ifm_wd_tick_2 = XS1_PORT_1F; /* WatchdogTick */

/* Expansion Ports */
on tile[NODE_2_IFM_TILE]: port p_ifm_ext_d_2[4] ={ XS1_PORT_1A,
									  XS1_PORT_1E,
									  XS1_PORT_1J,
									  XS1_PORT_1B };
