sc_somanet-base Change Log
==========================

3.1.2
-----
  * Fix CSV file parser to handle floats (for PID settings)
  * SPIFFS - Added 2 flash sizes for 2 type of cores
  * SPIFFS - Added checking of data partition size
  * Added temperature sensor support for Core C2X modules

3.1.1
-----
  * Added support for SQWE bit update in RTC to enable or disable the Square Wave output (Core C2X)
  * Added support for configuring the frequency of square wave output of Core C2X RTC
  * Added EEPROM read and write support (Core C2X)
  * Added XMOS libraries as submodules (now use $git submodule update --init --recursive):
    * lib_gpio
    * lib_spi
    * lib_uart



3.1.0
-----
  * Improve support for GPIO-A_rev-a2 module
  * Improve support for SOMANET-C21-DX_G2 module
  * Added support for DC1K rev.D1
  * Added i2c, xassert, and logging XMOS libraries (as submodules)
  * Added support for SPIFFS (SPI File System)
  * Added support for RTC of SOMANET-C21-DX_G2 module


3.0.3
-----
  * Minor software documentation fixes

3.0.2
-----
  * Fix SOMANET-C21-DX_G2 BSP and platform files

3.0.1
-----
  * Fix issue with a not working Debug/Release build configuration for demo apps

3.0.0
-----

  * Added board support for DC1K-rev-c3, DC1K-rev-c4 and DC5K-rev-a3
  * Added board support for CORE_C21-rev-b and CORE_C21-DX_G2
  * Added initial support for IFM_DC30-rev-a
  * Added initial support for GPIO-A_rev-a2 module
  * Added BISS encoder and AMS encoder (SPI) ports to board support file of all IFM_DC boards
  * New board support files (not compatible with older versions of SOMANET libs)
  * Added module locks
  * Added communication interface detection module
  * Added reboot module
  * Added flash handling service
  * Remove xSCOPE wrapper

2.0.2
-----

  * Fix C22 bsp file to be interchangable with C21

2.0.1
-----

  * Fix legacy attributes in platform files causing OBLAC not generate valid platform files

2.0.0
-----

  * Drop nodeconfig.h support and switch to individual board support file including (see new module_board-support)
  * Include SOMANET platform files (.xn files) into module_board-support (no need to copy platform files to applications)

1.0.2
-----

  * Minor changes to documentation, READMEs


1.0.1
-----

  * Minor changes to documentation, READMEs

1.0.0
-----

  * Port Declaration for configuration of GPIO Digital ports
  * Firmware update over EtherCAT applications and module moved to sc_sncn_ehtercat 

0.9.0
-----

  * Initial Version

