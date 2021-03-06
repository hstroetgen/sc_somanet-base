/**
 * @file flash_boot.h
 * @brief Provides functions for boot partition access
 * @author Synapticon GmbH <support@synapticon.com>
 */

#pragma once


int flash_write_boot_page(unsigned char page[], unsigned size);

int flash_read_boot(unsigned char page[], unsigned size);

int flash_erase_image(void);
int flash_erase_boot_partition(void);

int flash_prepare_boot_partition();

int flash_find_images(void);

int upgrade_image_installed(void);
