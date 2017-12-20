.. _somanet_board_support_module:

=====================
Board Support Module
=====================

.. note:: You will need this module in all your **SOMANET applications** for an easy access to the hardware on your SOMANET device. 

.. contents:: In this document
    :backlinks: none
    :depth: 3

By including this module in your project you will provide access to the complete port mapping and other low-level configurations for SOMANET devices.
Furthermore, it contains the targets definition files (\*.xn) for the different SOMANET CORE boards so you can choose such targets in your app Makefile.
 
  
How to use
==========

1. Include the module in your app Makefile:

	::

		USED_MODULES = module_board-support 



2. Include in your **main.xc** the board support packages that you might need in your hardware configuration. e.g.

	::

		#include <CoreC22.bsp>
		#include <Drive100.bsp>

3. Select your right target in your app Makefile. e.g.

	::

		TARGET = SOMANET-CoreC22
       

Content
=======

Target Files
-------------

A list of target files can be found under the targets/ directory.

Set the appropriate `TARGET` in your app **Makefile**. It is not necessary to include the `.bsp` extension:

::

 TARGET = SOMANET-CoreC22


Board Support Files
-------------------

Supported SOMANET boards, including Core, Drive, and Com modules, can be found under the bsp/ directory.

Add board support files (\*.bsp) to your app by just including them. e.g.

::

	#include <ComEtherCAT-rev-a.bsp>
	#include <CoreC21-rev-b.bsp>
	#include <Drive100.bsp>


.. note:: Have a look at our demo apps to see how to use the definitions within these files. 

