/* PLEASE REPLACE "CORE_BOARD_REQUIRED" WITH AN APPROPRIATE BOARD SUPPORT FILE FROM module_board-support */
#include <CORE_BOARD_REQUIRED>

/**
 * @file main.xc
 * @brief Demo application illustrates usage of module_rtc
 * @author Synapticon GmbH <support@synapticon.com>
 */

#include "rtc.h"
#include "i2c.h"
#include <xs1.h>
#include <stdio.h>

on tile[0]: I2C_ports i2c_p = SOMANET_I2C_PORTS;

void RTC_run_test(client interface i2c_master_if i2c)
{
    i2c_regop_res_t result;
    rtc_init(i2c, result);
    uint8_t data = 0;

    /* Set date */
    rtc_set_Milli_Seconds(i2c, 0);        /* (00-99) */
    rtc_set_Seconds(i2c, 30);             /* (00-59) */
    rtc_set_Minutes(i2c, 44);             /* (00-59) */
    rtc_set_Hours(i2c, 11);               /* (00-23) */
    rtc_set_Day_of_week(i2c, 2);          /* (01-7) */
    rtc_set_Date(i2c, 30);                /* (01-31) */
    rtc_set_Month(1);                 /* (01-12) */
    rtc_set_Century(i2c, 21);              /* (21-23) */
    rtc_set_Year(i2c, 17);                /* (00-99) */
    rtc_set_SQWE(i2c, 1);                /* (0-1)  */
    rtc_set_SQW_Freq(i2c, RTC_SQW_FREQ_4KHZ);

    while (1)
    {
        // read Hours
        data = rtc_get_Hours(i2c, result);
        printf("Time is = %d", data);

        //read Minutes
        data = rtc_get_Minutes(i2c, result);
        printf(": %d", data);

        // read Seconds
        data = rtc_get_Seconds(i2c, result);
        printf(": %d", data);

        // read 10ths/100ths of seconds
        data = rtc_get_Milli_Seconds(i2c, result);
        printf(": %d", data);

        // read Date
        data = rtc_get_Date(i2c, result);
        printf(", Today is = %d", data);

        // read Month
        data = rtc_get_Month(i2c, result);
        printf("- %d", data);

        // read Century
        data = rtc_get_Century(i2c, result);
        printf("- %d", data+19);

        // read Year
        data = rtc_get_Year(i2c, result);
        printf("%d\n", data);

        // read SQWE bit
        data = rtc_get_SQWE(i2c, result);
        printf("SQWE bit = %d\n", data);

        // read Square Wave Frequency
        data = rtc_get_SQW_Freq(i2c, result);
        printf("RTC square wave frequency = %d\n", data);

        // read Day of week
        data = rtc_get_Day_of_week(i2c, result);
        printf("Day of Week = %d\n", data);
        delay_seconds(1);

    }

}
int main(void)
{
    interface i2c_master_if i2c[1];

    par {
        on tile[IF1_TILE] : {
                   par {
                       i2c_master(i2c, 1, i2c_p.p_scl, i2c_p.p_sda, 10);
                       RTC_run_test(i2c[0]);
                       }
                     }
         }
    return 0;
}
