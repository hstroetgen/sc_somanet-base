/***************************
 * IFM Drive DC-100
 * Rev. B
 ***************************/

#pragma once

#include <xs1.h>
#include <platform.h>

/* RGB LED and green LED */
on tile[IFM_TILE]: out port p_ifm_leds = XS1_PORT_4B; /* BlueGreenRed_Green */

/* Buttons */
on tile[IFM_TILE]: in port p_ifm_btn1 = XS1_PORT_1J; /* Button 1 */
/* Button 2 shares port with encoder (see below) */

/* A4935 control ports */
on tile[IFM_TILE]: port p_ifm_coastn = XS1_PORT_1G;
on tile[IFM_TILE]: out port p_ifm_esf_rstn_pwml_pwmh = XS1_PORT_4F;
on tile[IFM_TILE]: port p_ifm_ff1 = XS1_PORT_1H;
on tile[IFM_TILE]: port p_ifm_ff2 = XS1_PORT_1I;

/* ADC */
on tile[IFM_TILE]: out port p_ifm_adc_clk = XS1_PORT_1B;
on tile[IFM_TILE]: buffered out port:32 p_ifm_adc_conv = XS1_PORT_1C;
on tile[IFM_TILE]: in buffered  port:32 p_ifm_adc_miso = XS1_PORT_1D;
on tile[IFM_TILE]: in           port p_ifm_dummy_port = XS1_PORT_16A; /* any unused port */

/* BLDC Motor */
on tile[IFM_TILE]: in  port p_ifm_hall = XS1_PORT_4E;
on tile[IFM_TILE]: buffered out port:32 p_ifm_motor_hi[3] = { XS1_PORT_1K,   /* Hi A */
							XS1_PORT_1O,   /* Hi B */
							XS1_PORT_1M }; /* Hi C */

on tile[IFM_TILE]: buffered out port:32 p_ifm_motor_lo[3] = { XS1_PORT_1L,   /* Lo A */
							  XS1_PORT_1P,   /* Lo B */
							  XS1_PORT_1N }; /* Lo C */

on tile[IFM_TILE]: in port p_ifm_encoder_btn2 = XS1_PORT_4A; /* Encoder and Button 2 */

/* Expansion Port */
on tile[IFM_TILE]: out port p_ifm_scl = XS1_PORT_1E; /* I2C SCL */
on tile[IFM_TILE]: port p_ifm_sda = XS1_PORT_1A; /* I2C SDA */