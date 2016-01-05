=============================
SOMANET Board Support Module
=============================

.. contents:: In this document
    :backlinks: none
    :depth: 3

.. important:: You will need this module in all your **SOMANET applications** for an easy use of your SOMANET hardware. 

By including this module in your project you will provide access to the complete ports definition for SOMANET devices.
Furthermore, it contains the targets definition files (*.xn) for the different SOMANET CORE boards so you can choose such targets in your app Makefile.
 
How to use
==========

* Include the module in your app Makefile:

::

 USED_MODULES = module_board-support etc etc


* Include in your main the SOMANET port definitions files you need according to your hardware configuration. Eg:

::

 #include <CORE_C22-rev-a.inc>
 #include <IFM_DC100-rev-b.inc>

* Select your right target in your app Makefile:

::

 TARGET = SOMANET-C22
       

API
===

Here the list of available targets supported by the module: 

* targets/**SOMANET-C22.xn**

If you are using a **SOMANET CORE C22**, select this target in your app Makefile

::

 TARGET = SOMANET-C22


* targets/**SOMANET-C21-DX.xn**

If you are using a **SOMANET CORE C21-DX**, select this target in your app Makefile

::

 TARGET = SOMANET-C21-DX

Here the list of supported SOMANET boards and how to include their ports mapping in your app:

.. important:: Have a look at our demo apps to see how to use the ports definition within these files. 

* bsp/COM_ECAT/COM_ECAT-rev-a.inc
::

 #include <COM_ECAT-rev-a.inc>
        
* bsp/COM_ETHERNET/COM_ETHERNET-rev-a.inc
::

 #include <COM_ETHERNET-rev-a.inc>

* bsp/CORE_C21/CORE_C21-rev-a.inc
::

 #include <CORE_C21-rev-a.inc>

* bsp/CORE_C22/CORE_C22-rev-a.inc
::

 #include <CORE_C22-rev-a.inc>

* bsp/IFM_DC100/IFM_DC100-rev-b.inc
::

 #include <IFM_DC100-rev-b.inc>

* bsp/IFM_DC300/IFM_DC300-rev-a.inc
::

 #include <IFM_DC300-rev-a.inc>

* bsp/IFM_DC1K/IFM_DC1K-rev-c2.inc
::

 #include <IFM_DC1K-rev-c2.inc>

