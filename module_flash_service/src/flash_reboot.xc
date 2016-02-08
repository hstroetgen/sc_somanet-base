/**
 * @file flash_somanet.xc
 * @brief Somanet Firmware Update implementation
 * @brief Flash device access
 * @author Synapticon GmbH <support@synapticon.com>
 */

#include <flash_reboot.h>
#include <xs1.h>
#include <platform.h>


/* Code by Xcore from module_avb_util reboot.xc */
void flash_reboot_device(void)
{
    unsigned int pllVal;
    unsigned int localTileId = get_local_tile_id();
    unsigned int tileId;
    unsigned int tileArrayLength;
    #ifdef DEBUG
    printstrln("Reboot...");
    #endif

    asm volatile ("ldc %0, tile.globound":"=r"(tileArrayLength));

    // Reset all remote tiles
    for(int i = 0; i < tileArrayLength; i++)
    {
        // Cannot cast tileref to unsigned
        tileId = get_tile_id(tile[i]);

        // Do not reboot local tile yet
        if (localTileId != tileId)
        {
            read_sswitch_reg(tileId, 6, pllVal);
            write_sswitch_reg_no_ack(tileId, 6, pllVal);
        }
    }

    // Finally reboot this tile
    read_sswitch_reg(localTileId, 6, pllVal);
    write_sswitch_reg_no_ack(localTileId, 6, pllVal);
}
