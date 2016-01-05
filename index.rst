SOMANET Base - Utility Library
===============================

.. toctree::
	:maxdepth: 1
	:hidden:

	Board Support Module <module_board-support/doc/index>
	COM Recognition Module <module_com-detect/doc/index>
	Locks Module <module_locks/doc/index>

.. important:: You will always need to include SOMANET Base library in your project in order to run any other **SOMANET Library**. 

The SOMANET Base Package is a collection useful utilities and basic firmware for SOMANET programming. SOMANET libraries It currently consist of following modules:

* `Board Support Module <module_board-support/doc/index>`_: Contains port mappings, low-level configurations and platform description files (*.xn) for all available SOMANET modules.
* `SOMANET COM Recognition Module <module_com-detect/doc/index>`_:  Enables automatic recognition of SOMANET COM modules. **For internal use only!**
* `Locks Module <module_locks/doc/index>`_: Provides an API to use locks between concurrent software tasks. **For internal use only!**

.. cssclass:: downloadable-button 

  `Download Library <https://github.com/synapticon/sc_somanet-base/archive/new_board_support_system.zip>`_

.. cssclass:: github

  `Visit Public Repository <https://github.com/synapticon/sc_somanet-base/tree/new_board_support_system>`_

Examples
--------

.. toctree:: 
 	:maxdepth: 1
 	:hidden:

 	XScope Test <examples/app_test_xscope/doc/index>
        COM Recognition Demo <examples/app_test_com-detect/doc/index>

Additionally, this repository includes the following example apps: 

* `XScope Test <examples/app_test_xscope/doc/index>`_: Simple XScope test.
* `COM Recognition Demo <examples/app_test_com-detect/doc/index>`_: Simple example on how to use the **COM Recognition Module**.
