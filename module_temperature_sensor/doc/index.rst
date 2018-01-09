.. _module_temperature_sensor:

=====================
Temperature Sensor Module
=====================

.. contents:: In this document
    :backlinks: none
    :depth: 3

This module provides a Service of PCT2075GVJ Temperature Sensor module  which will provide the interface functions to read the temperature value and to configure the temperature sensor. Clients can read and write data to Temperature Sensor from the interface calls provided by this service.

The Temperature Sensor Service should always be executed over a **COM Tile** so it can access the ports to your SOMANET COM device where the I2C ports are defined.

How to use
==========

.. important:: We assume that you are using :ref:`SOMANET Base <somanet_base>` and your app includes the required **board support** files for your SOMANET device.

.. seealso:: You might find useful the :ref:`App test module temperature sensor <app_test_temperature_sensor>`, which illustrates the use of this module.

1. First, add the following modules and their dependencies to your app Makefile.

    ::

        USED_MODULES = module_temperature_sensor module_board-support lib_i2c

  `Refer to i2c library for its dependencies and documentation <https://www.xmos.com/support/libraries/lib_i2c>`_

2. Include the Temperature Sensor Service header **temperature_sensor.h** in your app.

3. Define the i2c communication ports that the Service will be using in order to read and write data from Temperature Sensor module.

4. Inside your main function, instantiate the interfaces for the Service-Clients communication: i_temperature_sensor_communication interface and i2c_master_if interface.

5. At your COM TILE, instantiate the Temperature Sensor Service and i2c_master_if Service that is used to communication with an I2C master component.
6. At whichever other core, now you can perform calls to the Temperature Sensor Service through the interfaces calls provided by the service.

    .. code-block:: c
	#include <temperature_sensor.h>

	#define MONITOR_TEMPERATURE_ALARM  0
	on tile[0]: I2C_ports i2c_p = SOMANET_I2C_PORTS;
	on tile[0]: port os = XS1_PORT_4D;


	void temp_sensor_comm(client interface i_temperature_sensor_communication i_temperature)
	{

	    float temp_value = 0.0;
	    unsigned int value;

	#if MONITOR_TEMPERATURE_ALARM == 1
	        i_temperature.set_threshold_value(33);
        	temp_value = i_temperature.get_threshold_value();
        	printf("The threshold value = %f\n", temp_value);

        	i_temperature.set_hysteresis_value(32);
        	temp_value = i_temperature.get_hysteresis_value();
        	printf("The hysteresis value = %f\n", temp_value);
	
	#endif


    		while(1)
    		{
		#if MONITOR_TEMPERATURE_ALARM == 0
        		value = i_temperature.get_temperature_update_time();
        		printf("The time value = %d\n", value);

        		temp_value = i_temperature.get_temperature();
        		printf("The temperature value = %f\n", temp_value);

        		i_temperature.set_temperature_update_time(200);
        		value = i_temperature.get_temperature_update_time();
        		printf("The time value = %d\n", value);

        		temp_value = i_temperature.get_threshold_value();
        		printf("The threshold value = %f\n", temp_value);

        		temp_value = i_temperature.get_hysteresis_value();
        		printf("The hysteresis value = %f\n", temp_value);

        		value = i_temperature.get_configuration();
        		printf("The configuration value = %d\n", value);

        		i_temperature.enable_shutdown_mode();
        		value = i_temperature.get_configuration();
        		printf("The configuration value = %d\n", value);

        		i_temperature.enable_normal_mode();
        		value = i_temperature.get_configuration();
        		printf("The configuration value = %d\n", value);

        		i_temperature.enable_OS_comparator_mode();
        		value = i_temperature.get_configuration();
        		printf("The configuration value = %d\n", value);

        		i_temperature.enable_OS_interrupt_mode();
        		value = i_temperature.get_configuration();
        		printf("The configuration value = %d\n\n", value);
		#endif
		#if MONITOR_TEMPERATURE_ALARM == 1
        		temp_value = i_temperature.get_temperature();
        		printf("The temperature value = %f\n", temp_value);
		#endif
        	delay_seconds(1);

    		}

	}
	#if MONITOR_TEMPERATURE_ALARM == 1
	void OS_pin_check()
	{
    		uint8_t value;
    		while(1)
    		{
        		os :> value;
        		value = value & 0x04;
        		if(value)
            			value = 1;
        	else
            		value = 0;
        	printf(" ################# The Temperature Alarm  = %d ################ \n", value);
        	delay_seconds(1);
    		}

	}
	#endif

	int main(void)
	{
    		interface i2c_master_if i2c[1];
    		interface i_temperature_sensor_communication i_temperature;
    		par {
        		on tile[COM_TILE] : {
           			par {

                   			i2c_master(i2c, 1, i2c_p.p_scl, i2c_p.p_sda, 100);
                   			temperature_sensor_service(i_temperature, i2c[0]);
                   			temp_sensor_comm(i_temperature);
				#if MONITOR_TEMPERATURE_ALARM == 1
                   			OS_pin_check();
				#endif

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
.. doxygenenum:: Temp_Registers

Service
--------

.. doxygenfunction:: temperature_sensor_service

Interface
---------

.. doxygeninterface:: i_temperature_sensor_communication
