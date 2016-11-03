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

typedef interface RebootInterface {
    void device_reboot(void);
    unsigned get_boot_flag(void);
    void set_boot_flag(unsigned);
} RebootInterface;


void reboot_service(server interface RebootInterface i_reboot);
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
}
#endif /* COM_ETHERCAT */
