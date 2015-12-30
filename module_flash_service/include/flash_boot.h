/**
 * @file flash_boot.h
 * @brief Provides functions for boot partition access
 * @author Synapticon GmbH <support@synapticon.com>
 */

#pragma once

int flash_write_boot(char data[], unsigned size);
int flash_read_boot(char data[], unsigned size);
