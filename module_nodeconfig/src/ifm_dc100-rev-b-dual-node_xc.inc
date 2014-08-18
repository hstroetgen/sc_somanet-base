/*******************************************
 * IFM Drive DC-100 Rev. B dual node setup
 *******************************************/

#pragma once

#include <xs1.h>
#include <platform.h>

/* ADC */
on tile[3]: in buffered  port:32 p_ifm_adc_misoa_node_0 = XS1_PORT_1D;
on tile[3]: in buffered  port:32 p_ifm_adc_misob_node_0 = XS1_PORT_1C;
on tile[3]: buffered out port:32 p_ifm_adc_sclk_conv_mosib_mosia_node_0 = XS1_PORT_4C;

on tile[7]: in buffered  port:32 p_ifm_adc_misoa_node_1 = XS1_PORT_1D;
on tile[7]: in buffered  port:32 p_ifm_adc_misob_node_1 = XS1_PORT_1C;
on tile[7]: buffered out port:32 p_ifm_adc_sclk_conv_mosib_mosia_node_1 = XS1_PORT_4C;


/* A4935 control ports */
on tile[3]: out port p_ifm_coastn_node_0 = XS1_PORT_1G;
on tile[3]: out port p_ifm_esf_rstn_pwml_pwmh_node_0 = XS1_PORT_4F;
on tile[3]: port p_ifm_ff1_node_0 = XS1_PORT_1H;
on tile[3]: port p_ifm_ff2_node_0 = XS1_PORT_1I;

on tile[7]: out port p_ifm_coastn_node_1 = XS1_PORT_1G;
on tile[7]: out port p_ifm_esf_rstn_pwml_pwmh_node_1 = XS1_PORT_4F;
on tile[7]: port p_ifm_ff1_node_1 = XS1_PORT_1H;
on tile[7]: port p_ifm_ff2_node_1 = XS1_PORT_1I;


/* BLDC Motor, default port mode */
on tile[3]:          in  port p_ifm_hall_node_0 = XS1_PORT_4E;
on tile[3]:          in  port p_ifm_encoder_node_0 = XS1_PORT_4A; /* Encoder and Button 2 */
on tile[3]:          in  port p_ifm_dummy_port_node_0 = XS1_PORT_16B; /* any unused port */
on tile[3]: buffered out port:32 p_ifm_motor_hi_node_0[3] = { XS1_PORT_1K,   /* Hi A */
							XS1_PORT_1O,   /* Hi B */
							XS1_PORT_1M }; /* Hi C */
on tile[3]: buffered out port:32 p_ifm_motor_lo_node_0[3] = { XS1_PORT_1L,   /* Lo A */
							  XS1_PORT_1P,   /* Lo B */
							  XS1_PORT_1N }; /* Lo C */
							  
on tile[7]:          in  port p_ifm_hall_node_1 = XS1_PORT_4E;
on tile[7]:          in  port p_ifm_encoder_node_1 = XS1_PORT_4A; /* Encoder and Button 2 */
on tile[7]:          in  port p_ifm_dummy_port_node_1 = XS1_PORT_16B; /* any unused port */
on tile[7]: buffered out port:32 p_ifm_motor_hi_node_1[3] = { XS1_PORT_1K,   /* Hi A */
							XS1_PORT_1O,   /* Hi B */
							XS1_PORT_1M }; /* Hi C */
on tile[7]: buffered out port:32 p_ifm_motor_lo_node_1[3] = { XS1_PORT_1L,   /* Lo A */
							  XS1_PORT_1P,   /* Lo B */
							  XS1_PORT_1N }; /* Lo C */							  


/* LEDs, Watchdog */
on tile[3]: out port p_ifm_shared_leds_wden_node_0 = XS1_PORT_4B; /* BlueGreenRed_WDEN */
on tile[7]: out port p_ifm_shared_leds_wden_node_1 = XS1_PORT_4B; /* BlueGreenRed_WDEN */
on tile[3]: out port p_ifm_wd_tick_node_0 = XS1_PORT_1F; /* WatchdogTick */
on tile[7]: out port p_ifm_wd_tick_node_1 = XS1_PORT_1F; /* WatchdogTick */


/* Expansion Port */
on tile[3]: port p_ifm_ext_d0_node_0 = XS1_PORT_1A;
on tile[3]: port p_ifm_ext_d1_node_0 = XS1_PORT_1E;
on tile[3]: port p_ifm_ext_d2_node_0 = XS1_PORT_1J;
on tile[3]: port p_ifm_ext_d3_node_0 = XS1_PORT_1B;

on tile[7]: port p_ifm_ext_d0_node_1 = XS1_PORT_1A;
on tile[7]: port p_ifm_ext_d1_node_1 = XS1_PORT_1E;
on tile[7]: port p_ifm_ext_d2_node_1 = XS1_PORT_1J;
on tile[7]: port p_ifm_ext_d3_node_1 = XS1_PORT_1B;
