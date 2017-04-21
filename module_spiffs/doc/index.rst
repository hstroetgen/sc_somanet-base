SPIFFS Service
==============
SPIFFS Service provides a server, which managed the SPI Flash File System.

**SPIFFS (SPI Flash File System)**

Spiffs is a file system intended for SPI NOR flash devices on embedded targets.
Spiffs is designed with following characteristics in mind:

 - Small (embedded) targets, sparse RAM without heap
 - Only big areas of data (blocks) can be erased
 - An erase will reset all bits in block to ones
 - Writing pulls one to zeroes
 - Zeroes can only be pulled to ones by erase
 - Wear leveling

How to use
==========

API
===

Definitions
------------

.. doxygendefine:: MAX_FILENAME_SIZE
.. doxygendefine:: MAX_DATA_BUFFER_SIZE

Types
-----

.. doxygenstruct:: spiffs_stat

Service
-------

.. doxygenfunction:: spiffs_service

Interface
---------

.. doxygeninterface:: SPIFFSInterface

