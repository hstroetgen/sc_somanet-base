.. _module_reboot:

=========================================
Reboot Module for Synapticon SOMANET SoCs
=========================================
.. contents:: In this document
    :backlinks: none
    :depth: 3

This module provides a Service that can be triggered to force a SoC reset. When triggered the device will reset all internal registers and boot the first available application from flash. This first application can either be a bootloader or a user application which has been flashed as factory image to flash.

This Service **must always be run on a COM Tile** since it resets every tile connected to the system in reverse order, while the tile to which flash is connected needs to be the last one that is reset.


How to use
==========

1. Include the module in your app Makefile:

	::

		USED_MODULES = module_reboot


2. Include in your **main.xc** the board support packages that you might need in your hardware configuration as well as the reboot service header. e.g.

	::

		#include <CoreC22.bsp>
		#include <Drive100.bsp>
		#include "reboot.h"

3. Select the right target in your app Makefile. e.g.

	::

		TARGET = SOMANET-CoreC22

4. In the COM Tile intantiate the reboot service and hand it the reboot interface as a parameter.

5. Pass the interface to any other service in your application from which you want to be able to reboot the application.

6. Call the interface function to reboot the device
	
	::

		i_reboot.device_reboot();



The following code snippet shows the full usage:

 .. code-block:: c
 
		#include <xs1.h>
		#include "platform.h"

		#include "CoreC22.bsp"

		#include "reboot.h"

		/* Prototype for task that will trigger the reboot */
		void idle_and_reboot(client RebootInterface i_reboot);

		int main(void)
		{

		    /* Definition of Reboot Interface */
		    RebootInterface i_reboot;

		    par
		      {
		          on tile [COM_TILE]:
		          {
		              par
		              {
		                  /* Start reboot service */
		                  reboot_service(i_reboot);
		              }
		          }

		          on tile[IF2_TILE]:
		          {
		              par
		              {
		                  /* Start task to reboot the system */
		                  idle_and_reboot(i_reboot);
		              }
		          }
		      }


		    return 0;
		}


		void idle_and_reboot(client RebootInterface i_reboot)
		{
		    /* Do nothing for 2s */
		    delay_milliseconds(2000);

		    /* Restart the device */
		    i_reboot.device_reboot();
		}



API
===

Service
--------

.. doxygenfunction:: reboot_service

Interface
---------

.. doxygeninterface:: RebootInterface

