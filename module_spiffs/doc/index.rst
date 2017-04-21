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

Spiffs is allocated to a part or all of the memory of the SPI flash device. 
This area is divided into logical blocks, which in turn are divided into 
logical pages. The boundary of a logical block must coincide with one or more 
physical blocks.

.. figure:: images/spiffs_block_structure.png
   :width: 60%

A logical block is divided further into a number of logical pages. A page 
defines the smallest data holding element known to spiffs.

.. figure:: images/spiffs_file.png
   :width: 60%



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

