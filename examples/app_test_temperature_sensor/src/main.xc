/* PLEASE REPLACE "CORE_BOARD_REQUIRED" WITH AN APPROPRIATE BOARD SUPPORT FILE FROM module_board-support */
//#include <CORE_BOARD_REQUIRED>
#include <CORE_C21-DX_G2.bsp>

/**
 * @file main.xc
 * @brief Demo application illustrates usage of module_temperature_sensor
 * @author Synapticon GmbH <support@synapticon.com>
 */

#include <temperature_sensor.h>

#define MONITOR_OS_PIN  0
on tile[0]: I2C_ports i2c_p = SOMANET_I2C_PORTS;
on tile[0]: port os = XS1_PORT_4D;


void temp_sensor_comm(client interface i_temperature_sensor_communication i_temperature)
{

    float temp_value = 0.0;
    unsigned int value;

#if MONITOR_OS_PIN == 1
        i_temperature.set_threshold_value(33);
        temp_value = i_temperature.get_threshold_value();
        printf("The threshold value = %f\n", temp_value);

        i_temperature.set_hysteresis_value(32);
        temp_value = i_temperature.get_hysteresis_value();
        printf("The hysteresis value = %f\n", temp_value);

#endif


    while(1)
    {
#if MONITOR_OS_PIN == 0
        value = i_temperature.get_temperature_update_time();
        printf("The time value = %d\n", value);

        temp_value = i_temperature.get_temperature();
        printf("The temperature value = %f\n", temp_value);

        i_temperature.set_temperature_update_time(200);
        value = i_temperature.get_temperature_update_time();
        printf("The time value = %d\n", value);

        temp_value = i_temperature.get_threshold_value();
        printf("The threshold value = %f\n", temp_value);

        temp_value = i_temperature.get_hysteresis_value();
        printf("The hysteresis value = %f\n", temp_value);

        value = i_temperature.get_configuration();
        printf("The configuration value = %d\n", value);

        i_temperature.enable_shutdown_mode();
        value = i_temperature.get_configuration();
        printf("The configuration value = %d\n", value);

        i_temperature.enable_normal_mode();
        value = i_temperature.get_configuration();
        printf("The configuration value = %d\n", value);

        i_temperature.enable_OS_comparator_mode();
        value = i_temperature.get_configuration();
        printf("The configuration value = %d\n", value);

        i_temperature.enable_OS_interrupt_mode();
        value = i_temperature.get_configuration();
        printf("The configuration value = %d\n\n", value);
#endif
#if MONITOR_OS_PIN == 1
        temp_value = i_temperature.get_temperature();
        printf("The temperature value = %f\n", temp_value);
#endif
        delay_seconds(1);

    }

}
#if MONITOR_OS_PIN == 1
void OS_pin_check()
{
    uint8_t value;
    while(1)
    {
        os :> value;
        value = value & 0x04;
        if(value)
            value = 1;
        else
            value = 0;
        printf(" ################# The OS pin value = %d ################ \n", value);
        delay_seconds(1);
    }

}
#endif

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
#if MONITOR_OS_PIN == 1
                   OS_pin_check();
#endif

                }
            }
       }
    return 0;
}
