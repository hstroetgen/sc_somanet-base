/**
 * @file reboot.xc
 * @brief Somanet Firmware Update implementation
 * @brief Flash device access
 * @author Synapticon GmbH <support@synapticon.com>
 */

//#include <ethercat_service.h>
#include <reboot.h>
#include <xs1.h>
#include <platform.h>


// Todo: Decide based on board used


#ifdef XCORE200
/* xCORE-200 */
/* Note range 0x7FFC8 - 0x7FFFF guarenteed to be untouched by tools */
#define FLAG_ADDRESS 0x7ffcc
#else
/* Note range 0x1FFC8 - 0x1FFFF guarenteed to be untouched by tools */
#define FLAG_ADDRESS 0x1ffcc
#endif


#ifdef XCORE200
#define PLL_MASK 0x7FFFFFFF
#else
#define PLL_MASK 0xFFFFFFFF
#endif


/************************************** Local function prototypes **************************************/
static void SetDFUFlag(unsigned x);
static unsigned GetDFUFlag(void);


/**************************************** Service Implementation ***********************************/
#ifdef COM_ETHERCAT
[[distributable]]
void _reboot_service_ethercat(server interface EtherCATRebootInterface i_reboot_ecat, client interface RebootInterface i_reboot)
{
    while (1)
    {
        select
        {
            case i_reboot_ecat.boot_to_bootloader():
                i_reboot.boot_to_bootloader();
                break;
        }
    }
}
#endif

void reboot_service(server interface RebootInterface i_reboot)
{
    while (1)
    {
        select
        {
            case i_reboot.device_reboot():
                reboot_device();
                break;
            case i_reboot.get_boot_flag() -> unsigned flag:
                flag = GetDFUFlag();
                break;
            case i_reboot.set_boot_flag(unsigned flag):
                SetDFUFlag(flag);
                break;
            case i_reboot.boot_to_bootloader(void):
                SetDFUFlag(2);
                reboot_device();
                break;
            case i_reboot.boot_to_application(void):
                SetDFUFlag(1);
                reboot_device();
                break;
            case i_reboot.has_rebooted_from_application(void) -> int ret:

                unsigned flag = GetDFUFlag();
                if (flag == 2)
                    ret = 1;
                else
                    ret = 0;

                break;
        }
    }
}


/************************************* Reboot implementation ****************************************/
void reboot_device(void)
{
    unsigned int pllVal;
    unsigned int localTileId = get_local_tile_id();
    unsigned int tileId;
    unsigned int tileArrayLength;

    #ifdef DEBUG
    printstrln("Reboot...");
    #endif

    asm volatile ("ldc %0, tile.globound":"=r"(tileArrayLength));

    /* Check if reboot is called on tile 0 (tile connected to flash), otherwise throw error! */
    //assert(get_local_tile_id() == get_tile_id(tile[0]) && msg("Function can only be called on tile[0] (tile connected to SPI flash)!"));

    /* Reset all remote tiles in reverse order to ensure links to second chip
     * on dual chip boards isn't killed before second chip is rebooted
     */
    for(int i = tileArrayLength - 1; i >= 0; i--)
    {
        // Cannot cast tileref to unsigned
        tileId = get_tile_id(tile[i]);

        // Do not reboot local tile yet
        if (localTileId != tileId)
        {
            read_sswitch_reg(tileId, 6, pllVal);
            pllVal &= PLL_MASK;
            write_sswitch_reg_no_ack(tileId, 6, pllVal);
        }
    }

    // Finally reboot this tile
    read_sswitch_reg(localTileId, 6, pllVal);
    pllVal &= PLL_MASK;
    write_sswitch_reg_no_ack(localTileId, 6, pllVal);
}


/************************************** Local function implementations **************************************/
/* Store Flag to fixed address */
static void SetDFUFlag(unsigned x)
{
    asm volatile("stw %0, %1[0]" :: "r"(x), "r"(FLAG_ADDRESS));
}

/* Load flag from fixed address */
static unsigned GetDFUFlag()
{
    unsigned x;
    asm volatile("ldw %0, %1[0]" : "=r"(x) : "r"(FLAG_ADDRESS));
    return x;
}
