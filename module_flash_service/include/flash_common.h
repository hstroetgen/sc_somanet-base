/**
 * @file flash_common.h
 * @brief Flash device access
 * @author Synapticon GmbH <support@synapticon.com>
 */

#pragma once

#include <xccompat.h>
#include <flash.h>

#define DATA_PAGES_PER_TYPE     4

#define NO_ERROR                0
#define ERR_NO_FACTORY_IMAGE    10
#define ERR_NO_UPGRADE_IMAGE    11
#define ERR_UPGRADE_FAILED      12
#define ERR_CONNECT_FAILED      13
#define ERR_DISCONNECT_FAILED   14
#define ERR_WRITE_FAILED        15
#define ERR_ERASE_FAILED        16
#define ERR_NO_DATA_PARTITION   17

void flash_init(REFERENCE_PARAM(fl_SPIPorts, SPI));
int connect_to_flash(void);
