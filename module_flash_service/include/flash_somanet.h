/**
 * @file flash_somanet.h
 * @brief Somanet Firmware Update Implemtation
 * @author Synapticon GmbH <support@synapticon.com>
 */

#pragma once

#include <flashlib.h>
#include <xccompat.h>



/**
 * @brief Firmware update handler
 *
 * This function waits for flash update transfere in module ethercat
 * and perfroms the necessary steps to update this node and any subsequent
 * node connected.
 *
 * @note This thread must be on CORE 0 only
 *
 * @param &SPI          reference to the asociated SPI ports
 * @param foe_comm      data channel for FoE communication
 * @param foe_signal    FoE signal channel
 * @param c_flash_data  channel to flash data (r/w)
 * @param c_nodes[]     channel to subsequent nodes
 * @param reset         signal from firmware updater a reset occured.
 */



void reset_cores1(void);
/* software auto reset functions */
//void reset_cores(chanend sig_in, NULLABLE_RESOURCE(chanend, sig_out));

