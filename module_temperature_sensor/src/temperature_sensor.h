//#pragma once
#ifndef EEPROM_H_
#define EEPROM_H_


#include <xs1.h>
#include <platform.h>
#include <stdio.h>
#include <i2c.h>

#define SLAVE_ADDRESS   0x4A        // 01001000 or 01001010

/**
 * @brief Configuration structure of the I2C ports.
 */
typedef struct {
    port p_scl;     /**< I2C clock line */
    port p_sda;     /**< I2C data line */
}I2C_ports;

typedef enum
{
    CONF_REGISTER = 0x01,
    TEMP_REGISTER = 0x00,
    TOS_REGISTER = 0x03,
    THYST_REGISTER = 0x02,
    TIDLE_REGISTER = 0x04

}Temp_Registers;

/**
 * @brief Interface type to communicate with Temperature sensor Service.
 */

interface i_temperature_sensor_communication {

    /**
     * @brief Read the Temperature value.
     *
     * @return Temperature Value
     */

    float    get_temperature();
};


void temperature_sensor_service(server interface i_temperature_sensor_communication i_temperture_sensor, client interface i2c_master_if i2c);
#endif
