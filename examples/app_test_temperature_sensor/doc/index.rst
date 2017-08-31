.. _app_test_temperature_sensor:

===================================
App test Temperature Sensor for C2X core
===================================

.. contents:: In this document
    :backlinks: none
    :depth: 3

The purpose of this app (app_test_temperature_sensor) is showing the use of the :ref:`PCT2075GVJ Temperature Sensor Module <module_temperature_sensor>` over a C2X core. For that, it implements a simple app that reads the temperature value from Temperature Sensor Module and also demonstrates the configuration of Temperature Sensor Module using interface functions provided by the Temperature Sensor service.

* **Minimum Number of Cores**: 3
* **Minimum Number of Tiles**: 1

.. cssclass:: github

  `See Application on Public Repository <https://github.com/synapticon/sc_somanet-base/tree/develop/examples/app_test_temperature_sensor/>`_

.. important:: To clone the Somanet base component you can use the command
               
		"git clone --recursive <Path to repository>"
               
		To update the submodules use the command
               "git submodule update --init"

Quick How-to
============
1. :ref:`Assemble your SOMANET device <assembling_somanet_node>`.
2. Wire up your device. Check how at your specific :ref:`hardware documentation <hardware>`. Connect your power supply cable, and XTAG. Power up!
3. :ref:`Set up your XMOS development tools <getting_started_xmos_dev_tools>`. 
4. Open the **main.xc** within  the **app_test_temperature_sensor**. Include the :ref:`board-support file according to your device <somanet_board_support_module>`. Also set the :ref:`appropriate target in your Makefile <somanet_board_support_module>`.
5. :ref:`import in your workspace <getting_started_importing_library>` the I2C XMOS library and its dependencies. The I2C library and its dependencies are used as submodules. You can update the submodules by the command specified above in the document.
6. :ref:`import in your workspace <getting_started_importing_library>` the Temperature Sensor module.
7. Read and Write the data using i_temperature_sensor_communication interface functions.
8. Build the application. The output from the compilation process will be visible on the console.
9. The application when executed will read the temperature value and update configurations of Temperature Sensor and print it on the console.

.. seealso:: Did everything go well? If you need further support please check out our `forum <http://forum.synapticon.com/>`_.
