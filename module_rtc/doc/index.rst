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

.. seealso:: You might find useful the :ref:`App test module rtc <app_test_module_rtc>`, which illustrates the use of this module.

1. First, add the following modules to your app Makefile.

    ::

        USED_MODULES = module_rtc module_board-support lib_i2c

2. Include the RTC Service header **rtc_config.h** in your app.

3. Define the i2c communication ports that the Service will be using in order to set and get time/date from rtc device.

4. Inside your main function, instantiate the interfaces for the Service-Clients communication: rtc_communication interface and i2c_master_if interface.

5. At your COM TILE, instantiate the RTC Service and i2c_master_if Service that is used to communication with an I2C master component.
6. At whichever other core, now you can perform calls to the RTC Service through the interfaces connected to it.

    .. code-block:: c

        #include <CORE_C21-rev-b.bsp>   //Board Support file for SOMANET Core C21 device
                                        //(select your board support files according to your device)

        #include "rtc_config.h" // 2

        port p_scl = on tile[COM_TILE]: XS1_PORT_1C; // 3 I2C interface ports
        port p_sda = on tile[COM_TILE]: XS1_PORT_1A; 

        int main(void)
        {
            interface i2c_master_if i2c[1]; // 4
            interface rtc_communication rtc;
                 
            par
            {
                on tile[COM_TILE]:     // 5
                {
                 par {
                       rtc_service(rtc, i2c[0]);
                       i2c_master(i2c, 1, p_scl, p_sda, 10);
                       RTC_run_test(rtc);  // 6
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
