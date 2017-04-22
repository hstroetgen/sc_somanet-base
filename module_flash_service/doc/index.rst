.. _module_flash_service:

=====================
SOMANET Flash Service
=====================
.. contents:: In this document
    :backlinks: none
    :depth: 3

The SOMANET Flash Service offers an abstraction layer to access internal flash of SOMANET devices. The usage of this module is currently not recommended for end-users since the module release in SOMANET SDK 3.0 only offers preliminary functionality for internal use. 
With SDK release 3.1 end-user friendly functionality will be added.

.. cssclass:: github

  `See Module on Public Repository <https://github.com/synapticon/sc_somanet-base/tree/master/module_flash_service>`_

|
|
|

.. important:: The usage of this module can erase all contents from flash and render your SoC unusable.




API
===

Service
--------

.. doxygenfunction:: flash_service

Interface
---------

.. doxygeninterface:: FlashBootInterface
.. doxygeninterface:: FlashDataInterface


Types
-----
.. doxygenenum:: configuration_type
