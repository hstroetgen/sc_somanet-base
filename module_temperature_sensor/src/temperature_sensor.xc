/**
 * @file main.xc
 * @brief Module illustrates usage of temperature sensor PCT2075GVJ
 * @author Synapticon GmbH <support@synapticon.com>
 */

#include <temperature_sensor.h>

unsigned int read_i2c(uint8_t no_of_bytes, uint8_t stop_bit, client interface i2c_master_if i2c, uint8_t data[])
{
    i2c_res_t res;
    res = i2c.read(SLAVE_ADDRESS, data, no_of_bytes, stop_bit);
    if(res == 1)
        return 1;
    else
        return -1;
}

void write_i2c()
{

}

void temperature_sensor_service(server interface i_temperature_sensor_communication i_temperature_sensor, client interface i2c_master_if i2c)
{
    unsigned int ret;
    while (1) {
           select {
               case i_temperature_sensor.get_temperature() -> float temp:
                       uint8_t temp_data[2];
                       uint16_t tmp = 0;
                       float temp_value = 0.0;
                       ret = read_i2c(2,1, i2c, temp_data);
                       if(ret == 1)
                       {
                           if((temp_data[0] & 0x80) == 0)
                           {
                               tmp = temp_data[0];
                               tmp = (tmp << 8) | temp_data[1];
                     //          printf("tmp = 0x%x\n", tmp);
                               tmp = (tmp >> 5);
                               temp_value = tmp * 0.125;
                     //        printf("The temp value = %f\n\n", temp_value);
                           }

                           else
                           {
                               tmp = temp_data[0];
                               tmp = (tmp << 8) | temp_data[1];
                    //          printf("tmp = 0x%x\n", tmp);
                               tmp = (tmp >> 5);
                               tmp = ~tmp + 1;
                               temp_value = -(tmp * 0.125);
                    //          printf("The temp value = %f\n\n", temp_value);
                           }
                           temp = temp_value;
                       }
                       else
                       {
                           printf("WARNING : NACK recieved from the device while reading temperature value");
                           temp = 0.0;
                       }
                       break;
           }

    }

}
