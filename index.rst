.. _somanet_base:

SOMANET Base Utilities Component
================================

.. important:: You will always need to include **SOMANET Base** in your project in order to run any other **SOMANET Application**. 

The SOMANET Base Software Component is a collection of necessary utilities and basic firmware for SOMANET programming. 

.. cssclass:: downloadable-button 

  `Download Component <https://github.com/synapticon/sc_somanet-base/archive/master.zip>`_

.. cssclass:: github

  `Visit Public Repository <https://github.com/synapticon/sc_somanet-base/>`_

Modules
-------

.. toctree::
	:maxdepth: 1
	:hidden:

	Board Support Module <module_board-support/doc/index>
	COM Recognition Module <module_com-detect/doc/index>
	Locks Module <module_locks/doc/index>
	Reboot Module <module_reboot/doc/index>
	Flash Service Module <module_flash_service/doc/index>
	SPI Flash File System Module <module_spiffs/doc/index>

SOMANET Base currently consists of the following modules:

* `Board Support Module <module_board-support/doc/index.html>`_: Contains port mappings, low-level configurations and platform description files (\*.xn) for all available SOMANET hardware modules.
* `SOMANET COM Recognition Module <module_com-detect/doc/index.html>`_:  Enables automatic recognition of SOMANET COM modules. **For internal use only!**
* `Locks Module <module_locks/doc/index.html>`_: Provides an API to use locks between concurrent software tasks. **For internal use only!**
* `Reboot Module <module_reboot/doc/index.html>`_: Provides an API to reboot SOMANET chip. **For internal use only!**
* `Flash Service Module <module_flash_service/doc/index.html>`_: Provides an API to access the internal flash of SOMANET SoCs. **Mostly intended for internal use**
* `SPI Flash File System Module <module_spiffs/doc/index.html>`_: Implements File System on a data partision of flash memory. **For internal use only!**

Examples
--------

.. toctree:: 
 	:maxdepth: 1
 	:hidden:

 	XScope Test <examples/app_test_xscope/doc/index>

Additionally, this component includes the following example applications: 

* `XScope Test <examples/app_test_xscope/doc/index.html>`_: Simple xSCOPE and debug prints test
* `COM-detect Test <examples/app_test_com-detect/doc/index.html>`_: Internal use only test application for COM-boards identification. 
