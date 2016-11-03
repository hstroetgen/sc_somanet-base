/**
 * @file reboot.h
 * @brief Somanet Firmware Update Implemtation
 * @author Synapticon GmbH <support@synapticon.com>
 */

#pragma once

#include <ethercat_service.h>

#if 0 /* -> interface definition in ethercat_service.h */
interface EtherCATRebootInterface {
    void device_reboot(void);
    unsigned get_boot_flag(void);
    void set_boot_flag(unsigned);
};
#endif

void reboot_service(server interface EtherCATRebootInterface i_reboot);
void reboot_device(void);

unsigned GetDFUFlag(void); /* obsolete?! */
