/**
 * @file rtc_service.xc
 * @brief Module provides a Service of M41T62LC6F Real Time Clock
 * @author Synapticon GmbH <support@synapticon.com>
 */

#include <xs1.h>
#include "rtc_config.h"
#include <stdio.h>

uint8_t RTC_read(client interface i2c_master_if i2c, uint8_t device_addr, uint8_t reg, i2c_regop_res_t &result)
{
      uint8_t data = 0;

      data = i2c.read_reg(device_addr, reg, result);
      if (result != I2C_REGOP_SUCCESS) {
          printf("rtc read reg failed\n");
          return -1;
                                        }
      else {
            return data;
            }
}
void RTC_write(client interface i2c_master_if i2c, uint8_t device_addr, uint8_t reg, uint8_t data)
{
    i2c_regop_res_t result;
    result = i2c.write_reg(device_addr, reg, data);
      if (result != I2C_REGOP_SUCCESS) {
          printf("I2C write reg failed\n");
      }
}
void rtc_service(server interface rtc_communication rtc, client interface i2c_master_if i2c)
{
    unsigned units, tens, century, data_month, data = 0;

    while (1) {
           select {
           case rtc.init(i2c_regop_res_t result):
               unsigned ST = 1;
               uint8_t data = 0;
               printf("rtc starting ..\n");
               // Start power up
               while (ST != 0){
               // Write ST = 1
               RTC_write(i2c, Addr_Slave, Seconds, 0x80);

               // Read ST
               data = RTC_read(i2c, Addr_Slave, Seconds, result);
               ST = (data >> 7) & 0x1;

               // Write ST = 0
               RTC_write(i2c, Addr_Slave, Seconds, 0x0);

               // Read ST
               data = RTC_read(i2c, Addr_Slave, Seconds, result);
               ST = (data >> 7) & 0x1;

               }
               if (ST == 0)
               {
                   printf("RTC device ready\n");
               }
               break;
           case rtc.set_Hours(uint8_t data):
                   tens = data / 10;
                   units = data % 10;
                   data = (tens << 4) | units;
                   RTC_write(i2c, Addr_Slave, Hours, data);
               break;
           case rtc.set_Minutes(uint8_t data):
                   tens = data / 10;
                   units = data % 10;
                   data = (tens << 4) | units;
                   RTC_write(i2c, Addr_Slave, Minutes, data);
               break;
           case rtc.set_Seconds(uint8_t data):
                   tens = data / 10;
                   units = data % 10;
                   data = (tens << 4) | units;
                   RTC_write(i2c, Addr_Slave, Seconds, data);
               break;
           case rtc.set_Milli_Seconds(uint8_t data):
                   tens = data / 10;
                   units = data % 10;
                   data = (tens << 4) | units;
                   RTC_write(i2c, Addr_Slave, tens_hundreds_seconds, data);
               break;
           case rtc.set_Year(uint8_t data):
                   tens = data / 10;
                   units = data % 10;
                   data = (tens << 4) | units;
                   RTC_write(i2c, Addr_Slave, Year, data);
               break;
           case rtc.set_Month(uint8_t data):
                    tens = data / 10;
                    units = data % 10;
                    data_month = (tens << 4) | units;
                break;
           case rtc.set_Century(uint8_t data):
                    data = ((data - 20) << 6) | data_month;
                    RTC_write(i2c, Addr_Slave, Century_Month, data);
                break;
           case rtc.set_Day_of_week(uint8_t data):
                     RTC_write(i2c, Addr_Slave, Day, data);
                 break;
           case rtc.set_Date(uint8_t data):
                     tens = data / 10;
                     units = data % 10;
                     data = (tens << 4) | units;
                     RTC_write(i2c, Addr_Slave, Date, data);
                 break;
           case rtc.get_Hours(i2c_regop_res_t result) -> unsigned data_actual:
                   // read Hours
                   data = RTC_read(i2c, Addr_Slave, Hours, result);
                   units = (data & 0xF);
                   tens = (data >> 4 ) & 0x3;
                   data_actual = (tens * 10) + units;
                 break;
           case rtc.get_Minutes(i2c_regop_res_t result) -> unsigned data_actual:
                   //read Minutes
                   data = RTC_read(i2c, Addr_Slave, Minutes, result);
                   units = (data & 0xF);
                   tens = (data >> 4 ) & 0x7;
                   data_actual = (tens * 10) + units;
                 break;
           case rtc.get_Seconds(i2c_regop_res_t result) -> unsigned data_actual:
                   // read Seconds
                   data = RTC_read(i2c, Addr_Slave, Seconds, result);
                   units = (data & 0xF);
                   tens = (data >> 4 ) & 0x7;
                   data_actual = (tens * 10) + units;
                 break;
           case rtc.get_Milli_Seconds(i2c_regop_res_t result) -> unsigned data_actual:
                   // read milliseconds
                   data = RTC_read(i2c, Addr_Slave, tens_hundreds_seconds, result);
                   units = (data & 0xF);
                   tens = (data >> 4 ) & 0x7;
                   data_actual = (tens * 10) + units;
                 break;
           case rtc.get_Day_of_week(i2c_regop_res_t result) -> unsigned data_actual:
                   // read Day
                   data = RTC_read(i2c, Addr_Slave, Day, result);
                   data_actual = (data & 0x7);
                 break;
           case rtc.get_Date(i2c_regop_res_t result) -> unsigned data_actual:
                   // read Date
                   data = RTC_read(i2c, Addr_Slave, Date, result);
                   units = (data & 0xF);
                   tens = (data >> 4 ) & 0x3;
                   data_actual = (tens * 10) + units;
                 break;
           case rtc.get_Month(i2c_regop_res_t result) -> unsigned data_actual:
                   // read Month
                   data = RTC_read(i2c, Addr_Slave, Century_Month, result);
                   units = (data & 0xF);
                   tens = (data >> 4 ) & 0x1;
                   century = (data >> 6) & 0x3;
                   data_actual = (tens * 10) + units;
                 break;
           case rtc.get_Century(i2c_regop_res_t result) -> unsigned data_actual:
                   // read Century
                   data = RTC_read(i2c, Addr_Slave, Century_Month, result);
                   data_actual = (data >> 6) & 0x3;
                 break;
           case rtc.get_Year(i2c_regop_res_t result) -> unsigned data_actual:
                   data = RTC_read(i2c, Addr_Slave, Year, result);
                   units = (data & 0xF);
                   tens = (data >> 4 ) & 0xF;
                   data_actual = (tens * 10) + units;
                 break;
           default : break;
                    }
               }
}
