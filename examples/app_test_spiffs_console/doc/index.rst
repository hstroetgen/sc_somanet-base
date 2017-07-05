.. _spiffs_console_demo:

==========================================
SPIFFS Console Demo
==========================================

.. contents:: In this document
    :backlinks: none
    :depth: 3

The purpose of this app (app_test_spiffs_console) is showing the use of the :ref:`SPIFFS Module <somanet_spiffs_module>`. For that, it implements an app that provides access to all functions of the SPIFFS - writing/reading/erasing of files and much more using a simple console user interface.

* **Minimum Number of Cores**: 2
* **Minimum Number of Tiles**: 2

.. cssclass:: github

  `See Application on Public Repository <https://github.com/synapticon/sc_somanet-base/tree/feature_spiffs/examples/app_test_spiffs_console/>`_

Quick How-to
============

1. :ref:`Set up your XMOS development tools <getting_started_xmos_dev_tools>`. 

2. Download and :ref:`import in your workspace <getting_started_importing_library>` the :ref:`SOMANET Base Utility Library <somanet_base>` and its dependencies.

3. Open the **main.xc** within **app_test_spiffs_console/src** . Include the :ref:`board-support file according to your device <somanet_board_support_module>`. Also set the :ref:`appropriate target in your Makefile <somanet_board_support_module>`.

4. :ref:`Run the application <running_an_application>`.

5. In case of a successful start of the program on your SOMANET device, you will see messages in the text console:
	 ::

		 >>   SOMANET FLASH SERVICE STARTING...

		 >>   SPIFFS SERVICE STARTING...

		 >>   COMMAND SERVICE STARTING...

		 > 

This means that you can start working with the console.


Did everything go well? If you need further support please check out our `forum <http://forum.synapticon.com>`_


Console commands
================

**~open [-rw/-ro/-c] [file name]**

Open/create a file. (where 1st param: 

- c - create new file; 

- ro - readonly existing file;

- rw - read/write existing file)


As a result of the successful command execution you'll see "file descriptor" - number of the opened file.
You can open several files at a time, and set the opened file as current using the "set [file descriptor]" command.
 
**~close**

close currently opened file.
As a result of the command execution you'll see "Success..." or an error number.

**~write [text]**

Write to the currently opened file text data from the console.
As a result of the command execution you'll see the number of written bytes or an error number.

**~read [length]**

Read data from the currently opened file to the text console
As a result of the command execution you'll see the data read or an error number.

**~fwrite [file name]**

Write to currently opened file data from the PC file system.
As a result of the command execution you'll see the number of written bytes or an error number.

**~fread [length]**

Read data from the currently opened file to the PC file system.
As a result of the command execution you'll see the data read or an error number.

**~remove**

Remove currently opened file.
As a result of the command execution you'll see "Success..." or an error number.

**~stat**

Show information about the currently opened file on text console.

**~rename [old file name] [new file name]**

Rename file.
As a result of the command execution you'll see "Success..." or an error number.

**~format**

Formats the entire file system. The file system must not be mounted when calling this.

.. warning:: All data will be lost when executing this command.

**~unmount**

Unmount file system. 
As a result of the successful command execution you'll see "Unmounted..."

**~ls**

Print out a list of files in the file system.

**~check**

Run a consistency check on given file system.

**~seek [offset] [-set/-cur/-end]**

Move the read/write offset in currently opened file (where 2nd param: 

  - set - the file offset shall be set to offset bytes;

  - cur - the file offset shall be set to its current location plus offset;

  - end - the file offset shall be set to the size of the file plus offse, which should be negative)


**~tell**

Get the position in currently  opened file.

**~info**

Return number of total bytes available and number of used bytes.
As a result of the successful command execution you'll see the total number of bytes in file system and used number of bytes in file system.

**~errno**

Return last error of last file operation.

**~vis**

Prints out a visualization of the file system.








