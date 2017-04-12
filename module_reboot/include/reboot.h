/**
 * @file reboot.h
 * @brief Somanet Firmware Update Implemtation
 * @author Synapticon GmbH <support@synapticon.com>
 */

#pragma once

#ifdef COM_ETHERCAT
#include <ethercat_service.h>
#endif

/**
 * @file reboot.h
 * @brief Somanet Firmware Update Implemtation
 * @author Synapticon GmbH <support@synapticon.com>
 */

#pragma once

/**
 * @brief Interface to communicate with the position service
 */
typedef interface RebootInterface 
{
    /**
    * @brief Reboot all tiles of the device
    */
    void device_reboot(void);

    /**
    * @brief INTERNAL USE ONLY
    * Returns the value of the bootflag set
    * 
    * @return Value of bootflag
    */
    unsigned get_boot_flag(void);

    /**
    * @brief INTERNAL USE ONLY
    * Sets a value for the bootflag
    *
    * @param Bootflag value
    */
    void set_boot_flag(unsigned);

    /**
    * @brief INTERNAL USE ONLY
    * Boots from the application to the bootloader
    */
    void boot_to_bootloader(void);

    /**
    * @brief INTERNAL USE ONLY
    * Boots from the bootloader to the application
    */
    void boot_to_application(void);

    /**
    * @brief INTERNAL USE ONLY
    * Checks if the was a cold-boot or if the application requested a reboot to the bootloader.
    *
    * @return Returns 1 if reboot to bootloader was requested by application
    */
    int has_rebooted_from_application(void);

} RebootInterface;

/**
* @brief Service to accept reboot commands from clients.
* 
* @param i_reboot Interface between reboot service and user task (client)
*/
void reboot_service(server interface RebootInterface i_reboot);

/**
* @brief INTERNAL USE ONLY
*
* Function to execute a SoC reset
* 
*/
void reboot_device(void);

#ifdef COM_ETHERCAT
[[distributable]]
void _reboot_service_ethercat(server interface EtherCATRebootInterface i_reboot_ecat, client interface RebootInterface i_reboot);

#define reboot_service_ethercat(i_reboot_ecat) \
{\
    RebootInterface i_reboot;\
    par {\
        reboot_service(i_reboot);\
        [[distribute]] _reboot_service_ethercat(i_reboot_ecat, i_reboot);\
    }\
} while(0)
#endif /* COM_ETHERCAT */
