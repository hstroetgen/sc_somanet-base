.. _app_test_module_rtc:

================================
App test Module RTC for C21 core
================================

.. contents:: In this document
    :backlinks: none
    :depth: 3

The purpose of this app (app_test_module_rtc) is showing the use of the :ref:`M41T62LC6F Real Time Clock Module <module_rtc>` over a C21 core. For that, it implements a simple app that sets the current time and date (Hours, Minutes, Seconds, Millisenconds, Day of the week, date, month, year and century) using the rtc module. Afterwards, the current time/date can be read by sending a request to the module.

* **Minimum Number of Cores**: 3
* **Minimum Number of Tiles**: 1

.. cssclass:: github

  `See Application on Public Repository <https://github.com/synapticon/sc_somanet-base/tree/feature_rtc_c21_core/examples/app_test_module_rtc/>`_

.. important:: To clone the Somanet base component you can use the command
               
		"git clone --recursive <Path to repository>"
               
		To update the submodules use the command
               "git submodule update --init"

Quick How-to
============
1. :ref:`Assemble your SOMANET device <assembling_somanet_node>`.
2. Wire up your device. Check how at your specific :ref:`hardware documentation <hardware>`. Connect your power supply cable, and XTAG. Power up!
3. :ref:`Set up your XMOS development tools <getting_started_xmos_dev_tools>`. 
4. Open the **main.xc** within  the **app_test_module_rtc**. Include the :ref:`board-support file according to your device <somanet_board_support_module>`. Also set the :ref:`appropriate target in your Makefile <somanet_board_support_module>`.
5. :ref:`import in your workspace <getting_started_importing_library>` the I2C XMOS library and its dependencies. The I2C library and its dependencies are used as submodules. You can update the submodules by the command specified above in the document.
6. :ref:`import in your workspace <getting_started_importing_library>` the RTC module.
7. Change the I2C port mapping as per your SOMANET board by configuring following data structure.

.. doxygenstruct:: I2C_ports

8. Set the current time/date as parameter of rtc_communication interface <rtc> functions.

.. code-block:: c

                                
                    rtc. set_Milli_Seconds(0);
                    rtc. set_Seconds(30);
                    rtc. set_Minutes(44);
                    rtc. set_Hours(11);
                    rtc. set_Day_of_week(2);
                    rtc. set_Date(30);
                    rtc.set_Month(1);
                    rtc.set_Century(21);
                    rtc. set_Year(17);

                   int main(void)
                   {
                       interface i2c_master_if i2c[1];
                       interface rtc_communication rtc;

                       par {
                               on tile[COM_TILE] : {
                                   par {
                                           rtc_service(rtc, i2c[0]);
                                           i2c_master(i2c, 1, p_scl, p_sda, 10);
                                           RTC_run_test(rtc);
                                                   }
                                        }
                           }
                       return 0;
                   }

7. :ref:`Run the application using printing forwarding functions via XScope <http://www.xmos.com/support/examples/AN10090>`.

.. seealso:: Did everything go well? If you need further support please check out our `forum <http://forum.synapticon.com/>`_.
