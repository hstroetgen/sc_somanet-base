.. _module_eeprom:

=====================
EEPROM Module
=====================

.. contents:: In this document
    :backlinks: none
    :depth: 3

This module provides a Service of 24LC01BT-I/LT EEPROM module  which will provide the interface functions to read and write the data from EEPROM. Clients can read and write data to EEPROM from the interface calls provided by this service.

The EEPROM Service should always be executed over a **COM Tile** so it can access the ports to your SOMANET COM device where the I2C ports are defined.

.. cssclass:: github

  `See Module on Repository <https://github.com/synapticon/sc_somanet-base/tree/develop/module_eeprom>`_

How to use
==========

.. important:: We assume that you are using :ref:`SOMANET Base <somanet_base>` and your app includes the required **board support** files for your SOMANET device.

.. seealso:: You might find useful the :ref:`App test module eeprom <app_test_eeprom>`, which illustrates the use of this module.

1. First, add the following modules and their dependencies to your app Makefile.

    ::

        USED_MODULES = module_eeprom module_board-support lib_i2c

  `Refer to i2c library for its dependencies and documentation <https://www.xmos.com/support/libraries/lib_i2c>`_

2. Include the EEPROM Service header **eeprom.h** in your app.

3. Define the i2c communication ports that the Service will be using in order to read and write data from EEPROM module.

4. Inside your main function, instantiate the interfaces for the Service-Clients communication: i_eeprom_communication interface and i2c_master_if interface.

5. At your COM TILE, instantiate the EEPROM Service and i2c_master_if Service that is used to communication with an I2C master component.
6. At whichever other core, now you can perform calls to the EEPROM Service through the interfaces calls provided by the service.

    .. code-block:: c

	#include <CORE_BOARD_REQUIRED>

	#include <xs1.h>
	#include <platform.h>
	#include <stdio.h>
	#include <eeprom.h>


	on tile[0]: I2C_ports i2c_p = SOMANET_I2C_PORTS;


	void eeprom_comm(client interface i_eeprom_communication i_eeprom)
	{
	    uint8_t data[8];
	    uint8_t addr = 0x08;
	    uint8_t d_set[8] = {0x97,0x31,0xA4, 0xB7, 0x2E,0x5B,0x97, 0xBC};
	    i_eeprom.write(addr, d_set, 8);
	    printf("### Random Read ###\n");
	    for(int i=0; i<8; i++)
	    {
	        i_eeprom.read(addr + i, 1, data);
	        printf("The data read from address 0x%x is = 0x%x\n", addr+i, data[0]);
	    }
	    printf("\n### Sequential Read ###\n");
	    addr = 0x00;
	    i_eeprom.write(addr, d_set, 8);
	    i_eeprom.read(addr, 8, data);
    	    for(int i=0; i<8; i++)
    	    {
    	    	printf("The data read from address 0x%x is = 0x%x\n", addr+i, data[i]);
    	    }
	}

	int main(void)
	{
    	    interface i2c_master_if i2c[1];
    	    interface i_eeprom_communication i_eeprom;
    	    par {
        	on tile[COM_TILE] : {
           			par {

                   			i2c_master(i2c, 1, i2c_p.p_scl, i2c_p.p_sda, 100);
                   			eeprom_service(i_eeprom, i2c[0]);
                   			eeprom_comm(i_eeprom);
                		}
            		}
       		}
   	 return 0;
	}

API
===

Types
-----

.. doxygenstruct:: I2C_ports

Service
--------

.. doxygenfunction:: eeprom_service

Interface
---------

.. doxygeninterface:: i_eeprom_communication
