sc_somanet-base Change Log
==========================

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

  * Add board support for DC1K-rev-c3, DC1K-rev-c4 and DC5K-rev-a3
  * Add board support for CORE_C21-rev-b and CORE_C21-DX_G2
  * Add initial support for IFM_DC30-rev-a
  * Add initial support for GPIO-A_rev-a2 module
  * Add BISS encoder and AMS encoder (SPI) ports to board support file of all IFM_DC boards
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

