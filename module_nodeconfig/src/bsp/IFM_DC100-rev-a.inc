/***************************
 * IFM Drive DC-100
 * Rev. A
 ***************************/

#pragma once

#include <xs1.h>
#include <platform.h>

/* ADC */
extern          out port p_ifm_adc_clk;
extern buffered out port:32 p_ifm_adc_conv;
extern in buffered  port:32 p_ifm_adc_miso;
extern in           port p_ifm_dummy_port;

/* A4935 control ports */
extern out port p_ifm_coastn;
extern out port p_ifm_esf_rstn_pwml_pwmh;
extern     port p_ifm_ff1;
extern     port p_ifm_ff2;

/* RGB LED and green LED */
extern out port p_ifm_leds; /* BlueGreenRed_Green */

/* Buttons */
extern in port p_ifm_btn1; /* Button 1 */
/* Button 2 shares port with encoder (see below) */

/* BLDC Motor */
extern           in  port p_ifm_hall;
extern  buffered out port:32 p_ifm_motor_hi[3]; /* = { Hi A, Hi B, Hi C } */
//extern  out port p_motor_pwm_hi[3]; /* = { Hi A, Hi B, Hi C } */
extern  buffered out port:32 p_ifm_motor_lo[3]; /* = { Hi A, Hi B, Hi C } */
//extern           out port p_ifm_motor_lo[3]; /* = { Lo A, Lo B, Lo C } */

extern           in port p_ifm_encoder_btn2; /* Encoder and Button 2 */

/* Expansion Port */
extern out port p_ifm_scl; /* I2C SCL */
extern     port p_ifm_sda; /* I2C SDA */

/*********************************************************************************************/

/* RGB LED and green LED */
on tile[3]: out port p_ifm_leds = XS1_PORT_4B; /* BlueGreenRed_Green */

/* Buttons */
on tile[3]: in port p_ifm_btn1 = XS1_PORT_1J; /* Button 1 */
/* Button 2 shares port with encoder (see below) */

/* A4935 control ports */
on tile[3]: out port p_ifm_coastn = XS1_PORT_1G;
on tile[3]: out port p_ifm_esf_rstn_pwml_pwmh = XS1_PORT_4F;
on tile[3]: port p_ifm_ff1 = XS1_PORT_1H;
on tile[3]: port p_ifm_ff2 = XS1_PORT_1I;

/* ADC */
on tile[3]:          out port p_ifm_adc_clk = XS1_PORT_1B;
on tile[3]: buffered out port:32 p_ifm_adc_conv = XS1_PORT_1C;
on tile[3]: in buffered  port:32 p_ifm_adc_miso = XS1_PORT_1D;
on tile[3]: in           port p_ifm_dummy_port = XS1_PORT_16A; /* any unused port */

/* BLDC Motor */
on tile[3]:          in  port p_ifm_hall = XS1_PORT_4E;
on tile[3]: buffered out port:32 p_ifm_motor_hi[3] = { XS1_PORT_1K,   /* Hi A */
							XS1_PORT_1O,   /* Hi B */
							XS1_PORT_1M }; /* Hi C */
//on tile[3]: out port p_ifm_motor_hi[3] = { XS1_PORT_1K,   /* Hi A */
//					      XS1_PORT_1O,   /* Hi B */
//					      XS1_PORT_1M }; /* Hi C */
on tile[3]: buffered out port:32 p_ifm_motor_lo[3] = { XS1_PORT_1L,   /* Lo A */
							  XS1_PORT_1P,   /* Lo B */
							  XS1_PORT_1N }; /* Lo C */
//on tile[3]: out port p_ifm_motor_lo[3] = { XS1_PORT_1L,   /* Lo A */
//					      XS1_PORT_1P,   /* Lo B */
//					      XS1_PORT_1N }; /* Lo C */
on tile[3]: in port p_ifm_encoder_btn2 = XS1_PORT_4A; /* Encoder and Button 2 */

/* Expansion Port */
on tile[3]: out port p_ifm_scl = XS1_PORT_1E; /* I2C SCL */
on tile[3]:     port p_ifm_sda = XS1_PORT_1A; /* I2C SDA */
