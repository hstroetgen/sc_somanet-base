/*
 * rtc_config.h
 *
 *  Created on: Jan 27, 2017
 *      Author: rawia
 */


#ifndef RTC_CONFIG_H_
#define RTC_CONFIG_H_
#include "i2c.h"

// M41T62LC6F clock registers
#define tens_hundreds_seconds   0x0
#define Seconds                 0x1
#define Minutes                 0x2
#define Hours                   0x3
#define Day                     0x4
#define Date                    0x5
#define Century_Month           0x6
#define Year                    0x7
#define Calibration             0x8
#define Al_month                0xA
#define Flags                   0xF
#define Addr_Slave              0x68  // (1101000)

interface rtc_communication {
    void    init(i2c_regop_res_t result);
    void    set_Hours(uint8_t data);
    void    set_Minutes(uint8_t data);
    void    set_Seconds(uint8_t data);
    void    set_Day(uint8_t data);
    void    set_Date(uint8_t data);
    void    set_Year(uint8_t data);
    void    set_Century_Month(uint8_t data);
    unsigned get_Hours(i2c_regop_res_t result);
    unsigned get_Minutes(i2c_regop_res_t result);
    unsigned get_Seconds(i2c_regop_res_t result);
    unsigned get_Month(i2c_regop_res_t result);
    unsigned get_Day(i2c_regop_res_t result);
    unsigned get_Date(i2c_regop_res_t result);
    unsigned get_Year(i2c_regop_res_t result);
    unsigned get_Century(i2c_regop_res_t result);
};

void RTC_write(client interface i2c_master_if i2c, uint8_t device_addr, uint8_t reg, uint8_t data);
uint8_t RTC_read(client interface i2c_master_if i2c, uint8_t device_addr, uint8_t reg, i2c_regop_res_t &result);
void rtc_service(server interface rtc_communication rtc, client interface i2c_master_if i2c);

#endif /* RTC_CONFIG_H_ */
