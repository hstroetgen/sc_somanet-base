/***************************
 * IFM Drive DC-100
 * Rev. A
 ***************************/

#pragma once

#include <xs1.h>
#include <platform.h>

/*******************************************************/
/*                        NODE 1                       */
/*******************************************************/

/* Buttons */
on tile[IFM_TILE]: in port p_ifm_btn1_0 = XS1_PORT_1J; /* Button 1 */
/* Button 2 shares port with encoder (see below) */

/* A4935 control ports */
on tile[IFM_TILE]: port p_ifm_coastn_0 = XS1_PORT_1G;
on tile[IFM_TILE]: out port p_ifm_esf_rstn_pwml_pwmh_0 = XS1_PORT_4F;
on tile[IFM_TILE]: port p_ifm_ff1_0 = XS1_PORT_1H;
on tile[IFM_TILE]: port p_ifm_ff2_0 = XS1_PORT_1I;

/* ADC */
on tile[IFM_TILE]:          out port p_ifm_adc_clk_0 = XS1_PORT_1B;
on tile[IFM_TILE]: buffered out port:32 p_ifm_adc_conv_0 = XS1_PORT_1C;
on tile[IFM_TILE]: in buffered  port:32 p_ifm_adc_miso_0 = XS1_PORT_1D;
on tile[IFM_TILE]: in           port p_ifm_dummy_port_0 = XS1_PORT_16A; /* any unused port */

/* BLDC Motor */
on tile[IFM_TILE]:          in  port p_ifm_hall_0 = XS1_PORT_4E;
on tile[IFM_TILE]: buffered out port:32 p_ifm_motor_hi_0[3] = { XS1_PORT_1K,   /* Hi A */
							XS1_PORT_1O,   /* Hi B */
							XS1_PORT_1M }; /* Hi C */
on tile[IFM_TILE]: buffered out port:32 p_ifm_motor_lo_0[3] = { XS1_PORT_1L,   /* Lo A */
							  XS1_PORT_1P,   /* Lo B */
							  XS1_PORT_1N }; /* Lo C */
on tile[IFM_TILE]: in port p_ifm_encoder_0 = XS1_PORT_4A; /* Encoder */

/* LEDs, Watchdog */
on tile[IFM_TILE]: out port p_ifm_shared_leds_wden_0 = XS1_PORT_4B; /* BlueGreenRed_WDEN */
on tile[IFM_TILE]: out port p_ifm_wd_tick_0 = XS1_PORT_1F; /* WatchdogTick */

/* Expansion Port */
on tile[IFM_TILE]: out port p_ifm_scl_0 = XS1_PORT_1E; /* I2C SCL */
on tile[IFM_TILE]:     port p_ifm_sda_0 = XS1_PORT_1A; /* I2C SDA */

/*******************************************************/
/*                        NODE 2                       */
/*******************************************************/

/* Buttons */
on tile[IFM_TILE]: in port p_ifm_btn1_1 = XS1_PORT_1J; /* Button 1 */
/* Button 2 shares port with encoder (see below) */

/* A4935 control ports */
on tile[IFM_TILE]: port p_ifm_coastn_1 = XS1_PORT_1G;
on tile[IFM_TILE]: out port p_ifm_esf_rstn_pwml_pwmh_1 = XS1_PORT_4F;
on tile[IFM_TILE]: port p_ifm_ff1_1 = XS1_PORT_1H;
on tile[IFM_TILE]: port p_ifm_ff2_1 = XS1_PORT_1I;

/* ADC */
on tile[IFM_TILE]:          out port p_ifm_adc_clk_1 = XS1_PORT_1B;
on tile[IFM_TILE]: buffered out port:32 p_ifm_adc_conv_1 = XS1_PORT_1C;
on tile[IFM_TILE]: in buffered  port:32 p_ifm_adc_miso_1 = XS1_PORT_1D;
on tile[IFM_TILE]: in           port p_ifm_dummy_port_1 = XS1_PORT_16A; /* any unused port */

/* BLDC Motor */
on tile[IFM_TILE]:          in  port p_ifm_hall_1 = XS1_PORT_4E;
on tile[IFM_TILE]: buffered out port:32 p_ifm_motor_hi_1[3] = { XS1_PORT_1K,   /* Hi A */
							XS1_PORT_1O,   /* Hi B */
							XS1_PORT_1M }; /* Hi C */
on tile[IFM_TILE]: buffered out port:32 p_ifm_motor_lo_1[3] = { XS1_PORT_1L,   /* Lo A */
							  XS1_PORT_1P,   /* Lo B */
							  XS1_PORT_1N }; /* Lo C */
on tile[IFM_TILE]: in port p_ifm_encoder_1 = XS1_PORT_4A; /* Encoder */

/* LEDs, Watchdog */
on tile[IFM_TILE]: out port p_ifm_shared_leds_1_wden = XS1_PORT_4B; /* BlueGreenRed_WDEN */
on tile[IFM_TILE]: out port p_ifm_wd_tick_1 = XS1_PORT_1F; /* WatchdogTick */

/* Expansion Port */
on tile[IFM_TILE]: out port p_ifm_scl_1 = XS1_PORT_1E; /* I2C SCL */
on tile[IFM_TILE]:     port p_ifm_sda_1 = XS1_PORT_1A; /* I2C SDA */

/*******************************************************/
/*                        NODE 3                       */
/*******************************************************/

/* Buttons */
on tile[IFM_TILE]: in port p_ifm_btn1_2 = XS1_PORT_1J; /* Button 1 */
/* Button 2 shares port with encoder (see below) */

/* A4935 control ports */
on tile[IFM_TILE]: port p_ifm_coastn_2 = XS1_PORT_1G;
on tile[IFM_TILE]: out port p_ifm_esf_rstn_pwml_pwmh_2 = XS1_PORT_4F;
on tile[IFM_TILE]: port p_ifm_ff1_2 = XS1_PORT_1H;
on tile[IFM_TILE]: port p_ifm_ff2_2 = XS1_PORT_1I;

/* ADC */
on tile[IFM_TILE]:          out port p_ifm_adc_clk_2 = XS1_PORT_1B;
on tile[IFM_TILE]: buffered out port:32 p_ifm_adc_conv_2 = XS1_PORT_1C;
on tile[IFM_TILE]: in buffered  port:32 p_ifm_adc_miso_2 = XS1_PORT_1D;
on tile[IFM_TILE]: in           port p_ifm_dummy_port_2 = XS1_PORT_16A; /* any unused port */

/* BLDC Motor */
on tile[IFM_TILE]:          in  port p_ifm_hall_2 = XS1_PORT_4E;
on tile[IFM_TILE]: buffered out port:32 p_ifm_motor_hi_2[3] = { XS1_PORT_1K,   /* Hi A */
							XS1_PORT_1O,   /* Hi B */
							XS1_PORT_1M }; /* Hi C */
on tile[IFM_TILE]: buffered out port:32 p_ifm_motor_lo_2[3] = { XS1_PORT_1L,   /* Lo A */
							  XS1_PORT_1P,   /* Lo B */
							  XS1_PORT_1N }; /* Lo C */
on tile[IFM_TILE]: in port p_ifm_encoder_2 = XS1_PORT_4A; /* Encoder */

/* LEDs, Watchdog */
on tile[IFM_TILE]: out port p_ifm_shared_leds_wden_2 = XS1_PORT_4B; /* BlueGreenRed_WDEN */
on tile[IFM_TILE]: out port p_ifm_wd_tick_2 = XS1_PORT_1F; /* WatchdogTick */

/* Expansion Port */
on tile[IFM_TILE]: out port p_ifm_scl_2 = XS1_PORT_1E; /* I2C SCL */
on tile[IFM_TILE]:     port p_ifm_sda_2 = XS1_PORT_1A; /* I2C SDA */
