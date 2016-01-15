.. _somanet_board_support_module:

=============================
SOMANET Board Support Module
=============================

.. note:: You will need this module in all your **SOMANET applications** for an easy access to the hardware on your SOMANET device. 

.. contents:: In this document
    :backlinks: none
    :depth: 3

By including this module in your project you will provide access to the complete port mapping and other low-level configurations for SOMANET devices.
Furthermore, it contains the targets definition files (\*.xn) for the different SOMANET CORE boards so you can choose such targets in your app Makefile.
 
.. cssclass:: github

  `See Module on Public Repository <https://github.com/synapticon/sc_somanet-base/tree/master/module_board-support>`_
  
How to use
==========

1. Include the module in your app Makefile:

	::

		USED_MODULES = module_board-support module_locks module_com-detect

    .. note:: Just module_board-support will be required. However, for simplicity, when using a library it is recommended to include always all the contained modules. 

2. Include in your **main.xc** the board support packages that you might need in your hardware configuration. e.g.

	::

		#include <CORE_C22-rev-a.bsp>
		#include <IFM_DC100-rev-b.bsp>

3. Select your right target in your app Makefile. e.g.

	::

		TARGET = SOMANET-C22
       

Content
=======

Target Files
-------------

Here the list of available targets supported by the module: 

* targets/**SOMANET-C22.xn**
* targets/**SOMANET-C21-DX.xn**

Select your target in your app **Makefile** accordingly:

::

 TARGET = SOMANET-C22

or

::

 TARGET = SOMANET-C21-DX

Board Support Files
-------------------
Here the list of supported SOMANET boards and how to include their support files in your app:

* bsp/CORE_C21/**CORE_C21-rev-a.bsp**
* bsp/CORE_C22/**CORE_C22-rev-a.bsp**


* bsp/IFM_DC100/**IFM_DC100-rev-b.bsp**
* bsp/IFM_DC300/**IFM_DC300-rev-a.bsp**
* bsp/IFM_DC1K/**IFM_DC1K-rev-c2.bsp**


* bsp/COM_ECAT/**COM_ECAT-rev-a.bsp**
* bsp/COM_ETHERNET/**COM_ETHERNET-rev-a.bsp**

Add board support files (\*.bsp) in your app by just including them. e.g.

::

	#include <COM_ECAT-rev-a.bsp>
	#include <CORE_C22-rev-a.bsp>
	#include <IFM_DC100-rev-b.bsp>

or

::

	#include <CORE_C21-rev-a.bsp>
	#include <IFM_DC1K-rev-c2.bsp>


.. note:: Have a look at our demo apps to see how to use the definitions within these files. 

