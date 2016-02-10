sc_somanet-base Change Log
==========================

3.0.0
-----

  * New board support files (not compatible with older versions of SOMANET libs)
  * Added module locks
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

