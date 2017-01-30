/*
 * main.xc
 *
 *  Created on: Jan 25, 2017
 *      Author: rawia
 */
#include <xs1.h>
#include "i2c.h"
#include "rtc_config.h"
#include <CORE_C21-rev-b.bsp>
#include <stdio.h>

// I2C interface ports
port p_scl = on tile[0]: XS1_PORT_1C;
port p_sda = on tile[0]: XS1_PORT_1A;

void RTC_run_test(client interface rtc_communication rtc)
{
    i2c_regop_res_t result;
    rtc.init(result);
    uint8_t data = 0;

    /* Set date */
    rtc. set_Milli_Seconds(0);
    rtc. set_Seconds(30);
    rtc. set_Minutes(44);
    rtc. set_Hours(11);
    rtc. set_Day_of_week(2);
    rtc. set_Date(30);
    //rtc. set_Century_Month(0x41);
    rtc.set_Month(1);
    rtc.set_Century(21);
    rtc. set_Year(17);

    while (1)
    {
        // read Hours
        data = rtc.get_Hours(result);
        printf("Time is = %d", data);

        //read Minutes
        data = rtc.get_Minutes(result);
        printf(": %d", data);

        // read Seconds
        data = rtc.get_Seconds(result);
        printf(": %d", data);

        // read 10ths/100ths of seconds
        data = rtc.get_Milli_Seconds(result);
        printf(": %d", data);

//        // read Day of week
//        data = rtc.get_Day_of_week(result);
//        printf(", Today is = %d", data);

        // read Date
        data = rtc.get_Date(result);
        printf(", Today is = %d", data);

        // read Month
        data = rtc.get_Month(result);
        printf("- %d", data);

        // read Century
        data = rtc.get_Century(result);
        printf("- %d", data+19);

        // read Year
        data = rtc.get_Year(result);
        printf("%d\n", data);

        delay_seconds(5);
    }

}
int main(void)
{
    interface i2c_master_if i2c[1];
    interface rtc_communication rtc;

    par {
        on tile[0] : {
                   par {
                       rtc_service(rtc, i2c[0]);
                       i2c_master(i2c, 1, p_scl, p_sda, 10);
                       RTC_run_test(rtc);
                       }
                     }
         }
    return 0;
}
