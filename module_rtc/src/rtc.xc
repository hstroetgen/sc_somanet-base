/**
 * @file rtc_service.xc
 * @brief Module provides a Service of M41T62LC6F Real Time Clock
 * @author Synapticon GmbH <support@synapticon.com>
 */

#include <xs1.h>
#include "rtc.h"
#include <stdio.h>

uint8_t data_month = 1;

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

void rtc_init(client interface i2c_master_if i2c, i2c_regop_res_t result)
{
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
}

void rtc_set_Hours(client interface i2c_master_if i2c, uint8_t data)
{
    uint8_t units, tens = 0;
    tens = data / 10;
    units = data % 10;
    data = (tens << 4) | units;
    RTC_write(i2c, Addr_Slave, Hours, data);
}

void rtc_set_Minutes(client interface i2c_master_if i2c, uint8_t data)
{
    uint8_t units, tens = 0;
    tens = data / 10;
    units = data % 10;
    data = (tens << 4) | units;
    RTC_write(i2c, Addr_Slave, Minutes, data);
}

void rtc_set_Seconds(client interface i2c_master_if i2c, uint8_t data)
{
    uint8_t units, tens = 0;
    tens = data / 10;
    units = data % 10;
    data = (tens << 4) | units;
    RTC_write(i2c, Addr_Slave, Seconds, data);
}

void rtc_set_Milli_Seconds(client interface i2c_master_if i2c, uint8_t data)
{
    uint8_t units, tens = 0;
    tens = data / 10;
    units = data % 10;
    data = (tens << 4) | units;
    RTC_write(i2c, Addr_Slave, tens_hundreds_seconds, data);
}

void rtc_set_Year(client interface i2c_master_if i2c, uint8_t data)
{
    uint8_t units, tens = 0;
    tens = data / 10;
    units = data % 10;
    data = (tens << 4) | units;
    RTC_write(i2c, Addr_Slave, Year, data);
}

void rtc_set_Month(uint8_t data)
{
    uint8_t units, tens = 0;
    tens = data / 10;
    units = data % 10;
    data_month = (tens << 4) | units;
}

void rtc_set_Century(client interface i2c_master_if i2c, uint8_t data)
{
    data = ((data - 20) << 6) | data_month;
    RTC_write(i2c, Addr_Slave, Century_Month, data);
}

void rtc_set_Day_of_week(client interface i2c_master_if i2c, uint8_t data)
{
    i2c_regop_res_t result;
    uint8_t day;
    day = RTC_read(i2c, Addr_Slave, Day, result);
    day = day & 0xf8;
    day = day | (data & 0x07);
    RTC_write(i2c, Addr_Slave, Day, day);
}

void rtc_set_Date(client interface i2c_master_if i2c, uint8_t data)
{
    uint8_t units, tens = 0;
    tens = data / 10;
    units = data % 10;
    data = (tens << 4) | units;
    RTC_write(i2c, Addr_Slave, Date, data);
}

void rtc_set_SQWE(client interface i2c_master_if i2c, uint8_t data)
{
    i2c_regop_res_t result;
    uint8_t sqwe;
    /* Write enable bit to reg A */
    sqwe = RTC_read(i2c, Addr_Slave, Al_month, result);
    sqwe = sqwe & 0xbf;
    sqwe = sqwe | (data<<6);
    RTC_write(i2c, Addr_Slave, Al_month, sqwe);
}

void rtc_set_SQW_Freq(client interface i2c_master_if i2c, RTC_SQW_FREQ data)
{
    i2c_regop_res_t result;
    uint8_t tmp;

    if(data != RTC_SQW_FREQ_NONE)
    {
        tmp = RTC_read(i2c, Addr_Slave, Day, result);
        tmp = tmp & 0x0F;
        tmp = tmp | data;
        RTC_write(i2c, Addr_Slave, Day, tmp);
    }
    else
    {
        tmp = RTC_read(i2c, Addr_Slave, Day, result);
        tmp = tmp & 0x0F;
        RTC_write(i2c, Addr_Slave, Day, tmp);
        tmp = RTC_read(i2c, Addr_Slave, Al_month, result);
        tmp = tmp & 0xbf;
        RTC_write(i2c, Addr_Slave, Al_month, tmp);
    }
}

unsigned rtc_get_Hours(client interface i2c_master_if i2c, i2c_regop_res_t result)
{
    uint8_t units, tens, data = 0;
    // read Hours
    data = RTC_read(i2c, Addr_Slave, Hours, result);
    units = (data & 0xF);
    tens = (data >> 4 ) & 0x3;
    return ((tens * 10) + units);
}

unsigned rtc_get_Minutes(client interface i2c_master_if i2c, i2c_regop_res_t result)
{
    uint8_t units, tens, data = 0;
    //read Minutes
    data = RTC_read(i2c, Addr_Slave, Minutes, result);
    units = (data & 0xF);
    tens = (data >> 4 ) & 0x7;
    return ((tens * 10) + units);
}

unsigned rtc_get_Seconds(client interface i2c_master_if i2c, i2c_regop_res_t result)
{
    uint8_t units, tens, data = 0;
    // read Seconds
    data = RTC_read(i2c, Addr_Slave, Seconds, result);
    units = (data & 0xF);
    tens = (data >> 4 ) & 0x7;
    return ((tens * 10) + units);
}

unsigned rtc_get_Milli_Seconds(client interface i2c_master_if i2c, i2c_regop_res_t result)
{
    uint8_t units, tens, data = 0;
    // read milliseconds
    data = RTC_read(i2c, Addr_Slave, tens_hundreds_seconds, result);
    units = (data & 0xF);
    tens = (data >> 4 ) & 0x7;
    return ((tens * 10) + units);
}

unsigned rtc_get_Day_of_week(client interface i2c_master_if i2c, i2c_regop_res_t result)
{
    uint8_t data = 0;
    // read Day
    data = RTC_read(i2c, Addr_Slave, Day, result);
    return (data & 0x7);
}

unsigned rtc_get_Date(client interface i2c_master_if i2c, i2c_regop_res_t result)
{
    uint8_t units, tens, data = 0;
    // read Date
    data = RTC_read(i2c, Addr_Slave, Date, result);
    units = (data & 0xF);
    tens = (data >> 4 ) & 0x3;
    return ((tens * 10) + units);
}

unsigned rtc_get_Month(client interface i2c_master_if i2c, i2c_regop_res_t result)
{
    uint8_t units, tens, century, data = 0;
    // read Month
    data = RTC_read(i2c, Addr_Slave, Century_Month, result);
    units = (data & 0xF);
    tens = (data >> 4 ) & 0x1;
    century = (data >> 6) & 0x3;
    return ((tens * 10) + units);
}

unsigned rtc_get_Century(client interface i2c_master_if i2c, i2c_regop_res_t result)
{
    uint8_t data = 0;
    // read Century
    data = RTC_read(i2c, Addr_Slave, Century_Month, result);
    return ((data >> 6) & 0x3);
}

unsigned rtc_get_Year(client interface i2c_master_if i2c, i2c_regop_res_t result)
{
    uint8_t units, tens, data = 0;
    data = RTC_read(i2c, Addr_Slave, Year, result);
    units = (data & 0xF);
    tens = (data >> 4 ) & 0xF;
    return ((tens * 10) + units);
}

unsigned rtc_get_SQWE(client interface i2c_master_if i2c, i2c_regop_res_t result)
{
    uint8_t data = 0;
    data = RTC_read(i2c, Addr_Slave, Al_month, result);
    return ((data >> 6) & 0xF);
}

RTC_SQW_FREQ rtc_get_SQW_Freq(client interface i2c_master_if i2c, i2c_regop_res_t result)
{
    uint8_t data = 0;
    data = RTC_read(i2c, Addr_Slave, Day, result);
    return ((data >> 4) & 0x0F);
}

