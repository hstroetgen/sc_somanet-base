/**
 * @file main.xc
 * @brief Demo application illustrates usage of module_rtc
 * @author Synapticon GmbH <support@synapticon.com>
 */

#include <CORE_C21-DX_G2.bsp>
#include <xs1.h>
#include "i2c.h"
#include "rtc_config.h"
#include <stdio.h>

on tile[0]: I2C_ports i2c_p = SOMANET_I2C_PORTS;

void RTC_run_test(client interface rtc_communication rtc)
{
    i2c_regop_res_t result;
    rtc.init(result);
    uint8_t data = 0;

    /* Set date */
    rtc.set_Milli_Seconds(0);        /* (00-99) */
    rtc.set_Seconds(30);             /* (00-59) */
    rtc.set_Minutes(44);             /* (00-59) */
    rtc.set_Hours(11);               /* (00-23) */
    rtc.set_Day_of_week(2);          /* (01-7) */
    rtc.set_Date(30);                /* (01-31) */
    rtc.set_Month(1);                 /* (01-12) */
    rtc.set_Century(21);              /* (21-23) */
    rtc.set_Year(17);                /* (00-99) */

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
        on tile[COM_TILE] : {
                   par {
                       rtc_service(rtc, i2c[0]);
                       i2c_master(i2c, 1, i2c_p.p_scl, i2c_p.p_sda, 10);
                       RTC_run_test(rtc);
                       }
                     }
         }
    return 0;
}
