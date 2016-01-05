=============================
SOMANET Board Support Module
=============================

.. note:: You will need this module in all your **SOMANET applications** for an easy use of your SOMANET hardware. 

.. contents:: In this document
    :backlinks: none
    :depth: 3

By including this module in your project you will provide access to the complete port mapping and other low-level configurations for SOMANET devices.
Furthermore, it contains the targets definition files (*.xn) for the different SOMANET CORE boards so you can choose such targets in your app Makefile.
 
How to use
==========

* Include the module in your app Makefile:

::

 USED_MODULES = module_board-support etc etc


* Include in your **main.xc** the board support packages that you might need in your hardware configuration. e.g.

::

 #include <CORE_C22-rev-a.bsp>
 #include <IFM_DC100-rev-b.bsp>

* Select your right target in your app Makefile. e.g.

::

 TARGET = SOMANET-C22
       

Content
=======

Target Files
------
Here the list of available targets supported by the module: 

* targets/**SOMANET-C22.xn**
* targets/**SOMANET-C21-DX.xn**

If you are using a **SOMANET Core C22**, select this target in your app Makefile

::

 TARGET = SOMANET-C22

If you are using a **SOMANET Core C21-DX**, select this target in your app Makefile

::

 TARGET = SOMANET-C21-DX

Board Support Files
-------------------
Here the list of supported SOMANET boards and how to include their support files in your app:

.. note:: Have a look at our demo apps to see how to use the definitions within these files. 

* bsp/CORE_C21/**CORE_C21-rev-a.bsp**
* bsp/CORE_C22/**CORE_C22-rev-a.bsp**

  
* bsp/IFM_DC100/**IFM_DC100-rev-b.bsp**
* bsp/IFM_DC300/**IFM_DC300-rev-a.bsp**
* bsp/IFM_DC1K/**IFM_DC1K-rev-c2.bsp**


* bsp/COM_ECAT/**COM_ECAT-rev-a.bsp**
* bsp/COM_ETHERNET/**COM_ETHERNET-rev-a.bsp**

Add board support files (*.bsp) in your app by just including them. e.g.

::

 #include <COM_ECAT-rev-a.bsp>
        
or 

::

 #include <CORE_C21-rev-a.bsp>

or

::

 #include <IFM_DC1K-rev-c2.bsp>

