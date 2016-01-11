.. _somanet_base:

SOMANET Base - Utility Library
===============================

.. important:: You will always need to include **SOMANET Base** in your project in order to run any other **SOMANET Library**. 

The SOMANET Base Package is a collection useful utilities and basic firmware for SOMANET programming. 

.. cssclass:: downloadable-button 

  `Download Library <https://github.com/synapticon/sc_somanet-base/archive/master.zip>`_

.. cssclass:: github

  `Visit Public Repository <https://github.com/synapticon/sc_somanet-base/>`_

Modules
--------

.. toctree::
	:maxdepth: 1
	:hidden:

	Board Support Module <module_board-support/doc/index>
	COM Recognition Module <module_com-detect/doc/index>
	Locks Module <module_locks/doc/index>

SOMANET Base currently consists of the following modules:

* `Board Support Module <module_board-support/doc/index>`_: Contains port mappings, low-level configurations and platform description files (\*.xn) for all available SOMANET modules.
* `SOMANET COM Recognition Module <module_com-detect/doc/index>`_:  Enables automatic recognition of SOMANET COM modules. **For internal use only!**
* `Locks Module <module_locks/doc/index>`_: Provides an API to use locks between concurrent software tasks. **For internal use only!**

Examples
--------

.. toctree:: 
 	:maxdepth: 1
 	:hidden:

 	XScope Test <examples/app_test_xscope/doc/index>

Additionally, this repository includes the following example app: 

* `XScope Test <examples/app_test_xscope/doc/index>`_: Simple XScope test.
