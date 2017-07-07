.. _module_rtc:

=====================
RTC Module
=====================

.. contents:: In this document
    :backlinks: none
    :depth: 3

This module provides a Service of M41T62LC6F Real Time Clock which will set the current date and time (up to melli-seconds precision) using i2c library for writing/reading the time/date. Clients could set and retrieve time/date from the Service through an interface.

The RTC Service should always run over a **COM Tile** so it can access the ports to
your SOMANET COM device where the i2c ports are defined.

.. cssclass:: github

  `See Module on Repository <https://github.com/synapticon/sc_somanet-base/tree/feature_rtc_c21_core/module_rtc>`_

How to use
==========

.. important:: We assume that you are using :ref:`SOMANET Base <somanet_base>` and your app includes the required **board support** files for your SOMANET device.

.. seealso:: You might find useful the :ref:`App test module rtc <app_test_rtc>`, which illustrates the use of this module.

1. First, add the following modules and their dependencies to your app Makefile.

    ::

        USED_MODULES = module_rtc module_board-support lib_i2c

  `Refer to i2c library for its dependencies and documentation <https://www.xmos.com/support/libraries/lib_i2c>`_

2. Include the RTC Service header **rtc_config.h** in your app.

3. Define the i2c communication ports that the Service will be using in order to set and get time/date from rtc device.

4. Inside your main function, instantiate the interfaces for the Service-Clients communication: rtc_communication interface and i2c_master_if interface.

5. At your COM TILE, instantiate the RTC Service and i2c_master_if Service that is used to communication with an I2C master component.
6. At whichever other core, now you can perform calls to the RTC Service through the interfaces connected to it.

    .. code-block:: c

	#include <CORE_C21-DX_G2.bsp>   //(select your board support files according to your device)
	#include "main.h"


	on tile[0]: I2C_ports i2c_p = SOMANET_I2C_PORTS;

	void RTC_run_test(client interface rtc_communication rtc)
	{
	    i2c_regop_res_t result;
	    rtc.init(result);
	    uint8_t data = 0;
	
	    // Set date 
	    rtc.set_Milli_Seconds(0);        // (00-99) 
	    rtc.set_Seconds(30);             // (00-59) 
	    rtc.set_Minutes(44);             // (00-59) 
	    rtc.set_Hours(11);               // (00-23) 
	    rtc.set_Day_of_week(2);          // (01-7) 
	    rtc.set_Date(30);                // (01-31) 
	    rtc.set_Month(1);                 // (01-12) 
	    rtc.set_Century(21);              // (21-23) 
	    rtc.set_Year(17);                // (00-99) 

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

API
===

Service
--------

.. doxygenfunction:: rtc_service

Interface
---------

.. doxygeninterface:: rtc_communication
