.. _app_test_eeprom:

===================================
App test Module EEPROM for C2X core
===================================

.. contents:: In this document
    :backlinks: none
    :depth: 3

The purpose of this app (app_test_eeprom) is showing the use of the :ref:`24LC01BT-I/LT EEPROM Module <module_eeprom>` over a C2X core. For that, it implements a simple app that reads and writes the data in EEPROM using the EEPROM module.

* **Minimum Number of Cores**: 3
* **Minimum Number of Tiles**: 1

.. cssclass:: github

  `See Application on Public Repository <https://github.com/synapticon/sc_somanet-base/tree/develop/examples/app_test_eeprom/>`_

.. important:: To clone the Somanet base component you can use the command
               
		"git clone --recursive <Path to repository>"
               
		To update the submodules use the command
               "git submodule update --init"

Quick How-to
============
1. :ref:`Assemble your SOMANET device <assembling_somanet_node>`.
2. Wire up your device. Check how at your specific :ref:`hardware documentation <hardware>`. Connect your power supply cable, and XTAG. Power up!
3. :ref:`Set up your XMOS development tools <getting_started_xmos_dev_tools>`. 
4. Open the **main.xc** within  the **app_test_eeprom**. Include the :ref:`board-support file according to your device <somanet_board_support_module>`. Also set the :ref:`appropriate target in your Makefile <somanet_board_support_module>`.
5. :ref:`import in your workspace <getting_started_importing_library>` the I2C XMOS library and its dependencies. The I2C library and its dependencies are used as submodules. You can update the submodules by the command specified above in the document.
6. :ref:`import in your workspace <getting_started_importing_library>` the EEPROM module.
7. Read and Write the data using i_eeprom_communication interface functions.
8. Build the application. The output from the compilation process will be visible on the console.
9. The application when executed will write the data at specific addresses to EEPROM and read the same data and print it on the console.

.. seealso:: Did everything go well? If you need further support please check out our `forum <http://forum.synapticon.com/>`_.
