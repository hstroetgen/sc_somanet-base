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


/**
 * @brief Types of Register in Temperature Sensor.
 */
typedef enum
{
    CONF_REGISTER = 0x01,       /**< Pointer Value of Configuration Register */
    TEMP_REGISTER = 0x00,       /**< Pointer Value of Temperature Register */
    TOS_REGISTER = 0x03,        /**< Pointer Value of Overtemperature shutdown threshold Register */
    THYST_REGISTER = 0x02,      /**< Pointer Value of hysteresis Register */
    TIDLE_REGISTER = 0x04       /**< Pointer Value of Tidle Register */

}Temp_Registers;

/**
 * @brief Interface type to communicate with Temperature sensor Service.
 */

interface i_temperature_sensor_communication {

    /**
     * @brief Set the Temperature update time after which temperature sensor update temperature register.
     * @param time_in_ms time in milliseconds
     */

    void    set_temperature_update_time(unsigned int time_in_ms);

    /**
     * @brief Set the threshold Temperature value for OS output pin.
     * @param temperature in degree celsius.
     */

    void    set_threshold_value(uint16_t temp);

    /**
     * @brief Set the hysteresis Temperature value for OS output pin.
     * @param temperature in degree celsius.
     */

    void    set_hysteresis_value(uint16_t temp);

    /**
      * @brief Set the configuration for Temperature Sensor.
      * @param configuration for temperature sensor.
      */

     void    set_configuration(uint8_t conf);


    /**
     * @brief Read the Temperature value.
     *
     * @return Temperature Value in degree celsius
     */

    float    get_temperature();

    /**
     * @brief Read the Temperature update time after which temperature sensor update temperature register.
     * @return time in milliseconds
     */

    unsigned int    get_temperature_update_time();

    /**
     * @brief Read the threshold Temperature value for OS output pin.
     * @return temperature in degree celsius
     */

    float    get_threshold_value();

    /**
     * @brief Read the hysteresis Temperature value for OS output pin.
     * @return temperature in degree celsius
     */

    float    get_hysteresis_value();

    /**
     * @brief Read the  Configuration register for temperature sensor.
     * @return Configuration Register Value.
     */

    uint8_t    get_configuration();

    /**
      * @brief Enable shutdown mode for temperature sensor.
      */

     void    enable_shutdown_mode();

    /**
      * @brief Enable normal mode for temperature sensor.
      */

     void    enable_normal_mode();

    /**
      * @brief Enable  OS comparator mode for temperature sensor.
      */

     void    enable_OS_comparator_mode();

    /**
      * @brief Enable  OS interrupt mode for temperature sensor.
      */

     void    enable_OS_interrupt_mode();
};


void temperature_sensor_service(server interface i_temperature_sensor_communication i_temperture_sensor, client interface i2c_master_if i2c);
#endif
