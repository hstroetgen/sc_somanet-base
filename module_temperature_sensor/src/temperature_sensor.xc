/**
 * @file main.xc
 * @brief Module illustrates usage of temperature sensor PCT2075GVJ
 * @author Synapticon GmbH <support@synapticon.com>
 */

#include <temperature_sensor.h>

unsigned int read_i2c(client interface i2c_master_if i2c, uint8_t no_of_bytes, uint8_t stop_bit, uint8_t data[])
{
    i2c_res_t res;
    res = i2c.read(SLAVE_ADDRESS, data, no_of_bytes, stop_bit);
    if(res == 1)
        return 1;
    else
        return -1;
}

void write_i2c_reg(client interface i2c_master_if i2c, uint8_t data[])
{
    i2c.write_reg(SLAVE_ADDRESS, data[0], data[1]);
}

void write_i2c(client interface i2c_master_if i2c, uint8_t no_of_bytes, uint8_t stop_bit, uint8_t data[])
{
    size_t no_bytes_sent;

    i2c.write(SLAVE_ADDRESS, data, no_of_bytes, no_bytes_sent, stop_bit);

}

void temperature_sensor_service(server interface i_temperature_sensor_communication i_temperature_sensor, client interface i2c_master_if i2c)
{
    unsigned int ret;
    while (1) {
           select {
               case i_temperature_sensor.get_temperature() -> float temp:
                       uint8_t temp_data[2] = {0,0};
                       uint8_t reg_data[1] = {TEMP_REGISTER};
                       uint16_t tmp = 0;
                       float temp_value = 0.0;
                       write_i2c(i2c, 1, 0, reg_data);
                       ret = read_i2c(i2c, 2, 1, temp_data);
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

               case i_temperature_sensor.get_temperature_update_time() -> unsigned int time:
                   uint8_t temp_data[1] = {0};
                   uint8_t reg_data[1] = {TIDLE_REGISTER};
                   write_i2c(i2c, 1, 0, reg_data);
                   ret = read_i2c(i2c, 1, 1, temp_data);
                   time = (temp_data[0] * 100);
                   break;

               case i_temperature_sensor.get_threshold_value() -> float temperature:
                   uint8_t temp_data[2] = {0,0};
                   uint8_t reg_data[1] = {TOS_REGISTER};
                   uint16_t temp_value;
                   write_i2c(i2c, 1, 0, reg_data);
                   ret = read_i2c(i2c, 2, 1, temp_data);
                   temp_value = temp_data[0];
                   temp_value = (temp_value << 8) | temp_data[1];
                   temp_value = temp_value >> 7;
                   temperature = (float)(temp_value/2);
                   break;

               case i_temperature_sensor.get_hysteresis_value() -> float temperature:
                    uint8_t temp_data[2] = {0,0};
                    uint8_t reg_data[1] = {THYST_REGISTER};
                    uint16_t temp_value;
                    write_i2c(i2c, 1, 0, reg_data);
                    ret = read_i2c(i2c, 2, 1, temp_data);
                    temp_value = temp_data[0];
                    temp_value = (temp_value << 8) | temp_data[1];
                    temp_value = temp_value >> 7;
                    temperature = (float)(temp_value/2);
                    break;

               case i_temperature_sensor.get_configuration() -> uint8_t value :
                   uint8_t reg_data[1] = {CONF_REGISTER};
                   uint8_t temp_data[1] = {0};
                   write_i2c(i2c, 1, 0, reg_data);
                   ret = read_i2c(i2c, 1, 1, temp_data);
                   value = temp_data[0];
                   break;


               case i_temperature_sensor.set_temperature_update_time(unsigned int time_in_ms):
                    uint8_t temp_data[2] = {TIDLE_REGISTER,0};
                    unsigned int value = time_in_ms/100;
                    temp_data[1] = value;
                    write_i2c_reg(i2c, temp_data);
                    break;


               case i_temperature_sensor.set_threshold_value(uint16_t temp):
                   uint8_t temp_data[3] = {TOS_REGISTER,0,0};
                   temp = temp * 2;
                   temp = temp << 7;
                   temp_data[1] = (temp & 0xFF00) >> 8;
                   temp_data[2] = temp & 0x00FF;
                   write_i2c(i2c, 3, 1, temp_data);
                   break;

               case i_temperature_sensor.set_hysteresis_value(uint16_t temp):
                    uint8_t temp_data[3] = {THYST_REGISTER,0,0};
                    temp = temp * 2;
                    temp = temp << 7;
                    temp_data[1] = (temp & 0xFF00) >> 8;
                    temp_data[2] = temp & 0x00FF;
                    write_i2c(i2c, 3, 1, temp_data);
                    break;

               case i_temperature_sensor.set_configuration(uint8_t conf):
                   uint8_t temp_data[2] = {CONF_REGISTER,0};
                   temp_data[1] = conf;
                   write_i2c(i2c, 2, 1, temp_data);
                   break;

               case i_temperature_sensor.enable_shutdown_mode():
                   uint8_t reg_data[2] = {CONF_REGISTER,0};
                   uint8_t temp_data[1] = {0};
                   write_i2c(i2c, 1, 0, reg_data);
                   ret = read_i2c(i2c, 1, 1, temp_data);
                   temp_data[0] = temp_data[0] | 0x01;
                   reg_data[1] = temp_data[0];
                   write_i2c(i2c, 2, 1, reg_data);
                   break;

               case i_temperature_sensor.enable_normal_mode():
                   uint8_t reg_data[2] = {CONF_REGISTER,0};
                   uint8_t temp_data[1] = {0};
                   write_i2c(i2c, 1, 0, reg_data);
                   ret = read_i2c(i2c, 1, 1, temp_data);
                   temp_data[0] = temp_data[0] & 0xFE;
                   reg_data[1] = temp_data[0];
                   write_i2c(i2c, 2, 1, reg_data);
                   break;

           }

    }

}
