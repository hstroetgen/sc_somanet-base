/* PLEASE REPLACE "CORE_BOARD_REQUIRED" WITH AN APPROPRIATE BOARD SUPPORT FILE FROM module_board-support */
//#include <CORE_BOARD_REQUIRED>
#include <CORE_C21-DX_G2.bsp>

/**
 * @file main.xc
 * @brief Demo application illustrates usage of module_temperature_sensor
 * @author Synapticon GmbH <support@synapticon.com>
 */

#include <temperature_sensor.h>

on tile[0]: I2C_ports i2c_p = SOMANET_I2C_PORTS;



void temp_sensor_comm(client interface i_temperature_sensor_communication i_temperature)
{

    float temp_value = 0.0;
    unsigned int value;

    while(1)
    {
        value = i_temperature.get_temperature_update_time();
        printf("The time value = %d\n", value);

        temp_value = i_temperature.get_temperature();
        printf("The temperature value = %f\n", temp_value);

        i_temperature.set_temperature_update_time(200);
        value = i_temperature.get_temperature_update_time();
        printf("The time value = %d\n", value);

        temp_value = i_temperature.get_threshold_value();
        printf("The threshold value = %f\n", temp_value);

        i_temperature.set_threshold_value(76);
        temp_value = i_temperature.get_threshold_value();
        printf("The threshold value = %f\n", temp_value);

        temp_value = i_temperature.get_hysteresis_value();
        printf("The hysteresis value = %f\n", temp_value);

        i_temperature.set_hysteresis_value(74);
        temp_value = i_temperature.get_hysteresis_value();
        printf("The hysteresis value = %f\n", temp_value);

        value = i_temperature.get_configuration();
        printf("The configuration value = %d\n\n", value);

        i_temperature.set_configuration(0x01);

        i_temperature.enable_shutdown_mode();
        value = i_temperature.get_configuration();
        printf("The configuration value = %d\n\n", value);

        i_temperature.enable_normal_mode();
        value = i_temperature.get_configuration();
        printf("The configuration value = %d\n\n", value);

        i_temperature.enable_OS_comparator_mode();
        value = i_temperature.get_configuration();
        printf("The configuration value = %d\n\n", value);

        i_temperature.enable_OS_interrupt_mode();
        value = i_temperature.get_configuration();
        printf("The configuration value = %d\n\n", value);

        delay_seconds(1);

    }

}

int main(void)
{
    interface i2c_master_if i2c[1];
    interface i_temperature_sensor_communication i_temperature;
    par {
        on tile[COM_TILE] : {
           par {

                   i2c_master(i2c, 1, i2c_p.p_scl, i2c_p.p_sda, 100);
                   temperature_sensor_service(i_temperature, i2c[0]);
                   temp_sensor_comm(i_temperature);

                }
            }
       }
    return 0;
}
