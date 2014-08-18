/************
 * Core-C22
 ************/

#pragma once

#include <flash.h>

extern fl_SPIPorts p_spi_flash;

/* RGB LED */
extern out port p_core_leds[3]; /* = { Red, Green, Blue } */
