/**
 * @file flash_common.h
 * @brief Flash device access
 * @author Synapticon GmbH <support@synapticon.com>
 */

#pragma once

#include <xccompat.h>

#ifdef XCORE200
#include <quadflashlib.h>
#else
#include <flashlib.h>
#endif

#define DATA_PAGES_PER_TYPE         4
#define FLASH_PAGE_SIZE             256

#define NO_ERROR                    0
#define ERR_NO_FACTORY_IMAGE        10
#define ERR_NO_UPGRADE_IMAGE        11
#define ERR_UPGRADE_FAILED          12
#define ERR_CONNECT_FAILED          13
#define ERR_DISCONNECT_FAILED       14
#define ERR_WRITE_FAILED            15
#define ERR_ERASE_FAILED            16
#define ERR_NO_DATA_PARTITION       17
#define ERR_DATA_PACKAGE_TOO_SMALL  18
#define ERR_OUT_OF_LIMITS           19
#define ERR_CRC_CHECK_FAILED        20

//Standard ref. core clock frequency Mhz
#define USEC_STD 100
//Fast ref. core clock frequency Mhz
#define USEC_FAST 250

#ifdef XCORE200
void flash_init(REFERENCE_PARAM(fl_QSPIPorts, SPI));
void change_FlashDeviceSpec(int usec);
#else
void flash_init(REFERENCE_PARAM(fl_SPIPorts, SPI));
#endif
int connect_to_flash(void);


