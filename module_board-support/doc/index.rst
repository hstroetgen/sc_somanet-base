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


* Include in your main the SOMANET port definitions files you need according to your hardware configuration:

::

 //Eg.
 #include <CORE_C22-rev-a.inc>
 #include <IFM_DC100-rev-b.inc>

* Select your right target in your app Makefile:

::

 TARGET = SOMANET-C22
       

API
===

Here the list of available targets supported by the module: 
**module_board_support/targets/**

* SOMANET-C22.xn

* SOMANET-C21-DX.xn

Here the list of supported SOMANET boards:
**module_board_support/bsp/**

* COM_ECAT
* COM_ETHERNET
* CORE_C21
* CORE_C22
* IFM_DC100
* IFM_DC300
* IFM_DC1K

