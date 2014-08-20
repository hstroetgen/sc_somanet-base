/***************************
 * IFM Drive DC-300
 * Rev. A
 ***************************/

#pragma once

#include <xs1.h>
#include <platform.h>

/* ADC */
extern in buffered  port:32 p_ifm_adc_misoa;
extern in buffered  port:32 p_ifm_adc_misob;
extern buffered out port:32 p_ifm_adc_sclk_conv_mosib_mosia;

/* A4935 control ports */
extern port p_ifm_coastn;
extern out port p_ifm_esf_rstn_pwml_pwmh;
extern     port p_ifm_ff1;
extern     port p_ifm_ff2;

/* BLDC Motor, default port mode */
extern           in  port p_ifm_hall;
extern           in  port p_ifm_encoder;
extern           in  port p_ifm_dummy_port; /* needed for PWM ADC-trigger timing */
extern  buffered out port:32 p_ifm_motor_hi[3]; /* = { Hi A, Hi B, Hi C } */
extern  buffered out port:32 p_ifm_motor_lo[3]; /* = { Hi A, Hi B, Hi C } */

/* BLDC Motor, alternative declaration for low-side PWM */
//extern    out port p_motor_pwm_hi[3]; /* = { Hi A, Hi B, Hi C } */
//extern    out port p_ifm_motor_lo[3]; /* = { Lo A, Lo B, Lo C } */

/* LEDs, Watchdog */
extern out port p_ifm_shared_leds_wden; /* BlueGreenRed_WDEN */
extern out port p_ifm_wd_tick;

/* Expansion Port */
extern port p_ifm_ext_d[4];

/*********************************************************************************************/

/* ADC */
on tile[3]: in buffered  port:32 p_ifm_adc_misoa = XS1_PORT_1D;
on tile[3]: in buffered  port:32 p_ifm_adc_misob = XS1_PORT_1C;
on tile[3]: buffered out port:32 p_ifm_adc_sclk_conv_mosib_mosia = XS1_PORT_4C;

/* A4935 control ports */
on tile[3]: port p_ifm_coastn = XS1_PORT_1G;
on tile[3]: out port p_ifm_esf_rstn_pwml_pwmh = XS1_PORT_4F;
on tile[3]: port p_ifm_ff1 = XS1_PORT_1H;
on tile[3]: port p_ifm_ff2 = XS1_PORT_1I;

/* BLDC Motor, default port mode */
on tile[3]:          in  port p_ifm_hall = XS1_PORT_4E;
on tile[3]:          in  port p_ifm_encoder = XS1_PORT_4A; /* Encoder and Button 2 */
on tile[3]:          in  port p_ifm_dummy_port = XS1_PORT_16B; /* any unused port */
on tile[3]: buffered out port:32 p_ifm_motor_hi[3] = { XS1_PORT_1K,   /* Hi A */
							XS1_PORT_1O,   /* Hi B */
							XS1_PORT_1M }; /* Hi C */
on tile[3]: buffered out port:32 p_ifm_motor_lo[3] = { XS1_PORT_1L,   /* Lo A */
							  XS1_PORT_1P,   /* Lo B */
							  XS1_PORT_1N }; /* Lo C */
/* BLDC Motor, alternative declaration for low-side PWM */
//on tile[3]: out port p_ifm_motor_hi[3] = { XS1_PORT_1K,   /* Hi A */
//					      XS1_PORT_1O,   /* Hi B */
//					      XS1_PORT_1M }; /* Hi C */
//on tile[3]: out port p_ifm_motor_lo[3] = { XS1_PORT_1L,   /* Lo A */
//					      XS1_PORT_1P,   /* Lo B */
//					      XS1_PORT_1N }; /* Lo C */

/* LEDs, Watchdog */
on tile[3]: out port p_ifm_shared_leds_wden = XS1_PORT_4B; /* BlueGreenRed_WDEN */
on tile[3]: out port p_ifm_wd_tick = XS1_PORT_1F; /* WatchdogTick */

/* Expansion Port */
on tile[3]: port p_ifm_ext_d[4] ={ XS1_PORT_1A,
									  XS1_PORT_1E,
									  XS1_PORT_1J,
									  XS1_PORT_1B };


