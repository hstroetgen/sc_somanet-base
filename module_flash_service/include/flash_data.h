/**
 * @file flash_data.h
 * @brief Provides functions for data partition access
 * @author Synapticon GmbH <support@synapticon.com>
 */

#pragma once

/**
 * @brief Initialized the data partition. If partition is not available,
 * the partition will be created with the size "partition_size" or with
 * the maximum remaining memory space.
 */
int flash_data_init(unsigned partition_size);

int flash_write_data(char data[], unsigned size);
int flash_read_data(char data[], unsigned size);
