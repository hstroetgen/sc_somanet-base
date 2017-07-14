.. _module_config_parser:

=========================================
Module Config Parser
=========================================


This module is used for parsing and generating data from OD (object dictionary) structure into a human readable configuration file (csv). 
Access to the configuration file is done using the SPIFFS.


.. cssclass:: github

  `See Module on Public Repository <https://github.com/synapticon/sc_somanet-base/tree/master/module_config_parser>`_

Dependent modules:
- ``module_spiffs``
- ``module_file_service``
- ``lib_ethercat``


API
===

Service
--------

.. doxygenfunction:: read_config

.. doxygenfunction:: write_config


