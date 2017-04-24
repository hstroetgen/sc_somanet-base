==========================================
SPIFFS Console Demo
==========================================

.. contents:: In this document
    :backlinks: none
    :depth: 3

The purpose of this app (app_test_spiffs_console) is showing the use of the :ref:`SPIFFS Module <module_spiffs>`. For that, it implements an app that provides access to all functions of the spiffs - writing/reading/erasing of files and much more using console user interface.

* **Minimum Number of Cores**: 2
* **Minimum Number of Tiles**: 2

.. cssclass:: github

  `See Application on Public Repository <https://github.com/synapticon/sc_somanet-base/tree/feature_spiffs/examples/app_test_spiffs_console/>`_

Quick How-to
============

1. :ref:`Set up your XMOS development tools <getting_started_xmos_dev_tools>`. 
2. Download and :ref:`import in your workspace <module_flash_service>` the SOMANET SPIFFS Service module and its dependencies.
3. Download and :ref:`import in your workspace <module_spiffs>` the SOMANET SPIFFS Service module and its dependencies.

??

4. In case of successful start of the program on your board, you will see messages in the text console:
 >>   SOMANET FLASH SERVICE STARTING...

 >>   SPIFFS SERVICE STARTING...

 >>   COMMAND SERVICE STARTING...

 > 

That means that you can start working with the console.


Console commands
================

**~open [-rw/-ro/-c] [file name]**

 Opens/creates a file. (where 1st param: 

  - c - create new file; 

  - ro - readonly existing file;

  - rw - read/write existing file)


As a result of the successful command execution you'll see "file descriptor" - number of the opened file.
You can open few files in one time, and set opened file as current using "set [file descriptor]" command.
 
**~close**

close current opened file.
As a result of the command execution you'll see "Succsess..." or error number.

**~write [text]**

Write to current opened file text data from console.
As a result of the command execution you'll see number of writed bytes or error number.

**~read [length]**

Read data from current opened file to text console
As a result of the command execution you'll readed data or error number.

**~fwrite [file name]**

Write to current opened file data from PC file system.
As a result of the command execution you'll see number of writed bytes or error number.

**~fread [length]**

Read data from current opened file to PC file system.
As a result of the command execution you'll readed data or error number.

**~remove**

Remove current opened file.
As a result of the command execution you'll see "Succsess..." or error number.

**~stat**

Show information about current opened file on text console.

**~rename [old file name] [new file name]**

Rename file.
As a result of the command execution you'll see "Succsess..." or error number.

**~format**

Format the entire file system. All data will be lost. The file system must not be mounted when calling this.

**~unmount**

Unmount file system. 
As a result of the successful command execution you'll see "Unmounted..."

**~ls**

Print out a list of files in file system.

**~check**

Run a consistency check on given filesystem.

**~seek [offset] [-set/-cur/-end]**

 Move the read/write offset in current opened file (where 2nd param: 

  - set - the file offset shall be set to offset bytes;

  - cur - the file offset shall be set to its current location plus offset;

  - end - the file offset shall be set to the size of the file plus offse, which should be negative)


**~tell**

Get position in current opened file.

**~info**

Return number of total bytes available and number of used bytes.
As a result of the successful command execution you'll see total number of bytes in file system and used number of bytes in file system.

**~errno**

Return last error of last file operation.







