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
 //   uint8_t pointer_reg = 0x00;
 //   uint8_t temp_data[2] = {0,0}, buff[1] = {TEMP_REGISTER};
 //   uint16_t tmp = 0;
 //   size_t no_bytes_sent;
    float temp_value = 0.0;
    unsigned int value;
//    i2c_regop_res_t ret;
//    i2c_res_t res;
//    i2c.write(SLAVE_ADDRESS, buff, 1, no_bytes_sent, 0);
//    i2c.write_reg(SLAVE_ADDRESS, buff[0], 0x01);
    while(1)
    {
        value = i_temperature.get_temperature_update_time();
        printf("The time value = %d\n", value);

        temp_value = i_temperature.get_temperature();
        printf("The temp value = %f\n", temp_value);

        i_temperature.set_temperature_update_time(100);
        value = i_temperature.get_temperature_update_time();
        printf("The time value = %d\n\n", value);

#if 0
   //     i2c.write(SLAVE_ADDRESS, buff, 1, no_bytes_sent, 0); //printf("No of bytes written = %d\n", no_bytes_sent);
        res = i2c.read(SLAVE_ADDRESS, temp_data, 2, 1);
        //printf("The return value after read is = %d\n", res);
        printf("The temp digital data recieved = %x and %x\n", temp_data[0], temp_data[1]);
        if((temp_data[0] & 0x80) == 0)
        {
            tmp = temp_data[0];
            tmp = (tmp << 8) | temp_data[1];
            printf("tmp = 0x%x\n", tmp);
            tmp = (tmp >> 5);
            temp_value = tmp * 0.125;
            printf("The temp value = %f\n\n", temp_value);
        }

        else
        {
            tmp = temp_data[0];
            tmp = (tmp << 8) | temp_data[1];
            printf("tmp = 0x%x\n", tmp);
            tmp = (tmp >> 5);
            tmp = ~tmp + 1;
            temp_value = tmp * 0.125;
            printf("The temp value = %f\n\n", temp_value);
        }
#endif
        delay_seconds(1);


    }

//    if((temp_data[1] & 0x80) == 0)
 //   if(1)
 //   {
 //       tmp = temp_data[1];
 //     tmp = (tmp << 8) | temp_data[0];
 //     tmp = tmp >> 5;
 //       temp_value = tmp * 0.125;

 //   }
 //   else
//    {
 //       tmp = temp_data[1];
//        tmp = ((tmp << 8) | temp_data[0]);
//        tmp = ~tmp;
//        temp_value = -(tmp * 0.125);
//        printf("The temperature is = %lf", temp_value);
//    }
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
