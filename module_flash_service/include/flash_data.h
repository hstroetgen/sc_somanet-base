/*
 * flash_data.h
 *
 *  Created on: 17.12.2015
 *      Author: hstroetgen
 */

/**
 * @brief Provides functions for data partition access.
 */

#ifndef FLASH_DATA_H_
#define FLASH_DATA_H_

/**
 * @brief Initialized the data partition. If partition is not available, the partition will be created with the size "partition_size" or
 *        with the maximum remaining memory space.
 */
int flash_data_init(unsigned partition_size);

int flash_write_data(char data[], unsigned size);
int flash_read_data(char data[], unsigned size);

#endif /* FLASH_DATA_H_ */
