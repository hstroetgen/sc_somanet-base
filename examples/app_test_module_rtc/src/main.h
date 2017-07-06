/*
 * main.h
 *
 *  Created on: Jul 6, 2017
 *      Author: root
 */

#ifndef MAIN_H_
#define MAIN_H_
#include <xs1.h>
#include "i2c.h"
#include "rtc_config.h"
#include <stdio.h>

/**
 * @brief Configuration structure of the I2C ports.
 */

typedef struct {
    port p_scl;     /**< I2C clock line */
    port p_sda;     /**< I2C data line */
}I2C_ports;


#endif /* MAIN_H_ */
