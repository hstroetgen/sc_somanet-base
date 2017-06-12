/**
 * @file flash_common.c
 * @brief Flash device access
 * @author Synapticon GmbH <support@synapticon.com>
 */
#include <flash_common.h>
#include <platform.h>
#include <string.h>


#ifdef XCORE200
#include <quadflash.h>
#include <QuadSpecMacros250Mhz.h>
#else
#include <flash.h>
#endif

#include <print.h>

#ifdef XCORE200
#define MAX_FLASH_DEVICES 6
fl_QSPIPorts *SPI_port;
fl_QuadDeviceSpec dSpecs[MAX_FLASH_DEVICES];

void change_FlashDeviceSpec(int usec)
{
    // List of QuadSPI devices
    if (usec == USEC_STD)
    {
        fl_QuadDeviceSpec QuadDeviceSpecs[] = {
            FL_QUADDEVICE_SPANSION_S25FL116K,
            FL_QUADDEVICE_SPANSION_S25FL132K,
            FL_QUADDEVICE_SPANSION_S25FL164K,
            FL_QUADDEVICE_ISSI_IS25LQ080B,
            FL_QUADDEVICE_ISSI_IS25LQ016B,
            FL_QUADDEVICE_ISSI_IS25LQ032B
        };
        memcpy(dSpecs, QuadDeviceSpecs, sizeof(QuadDeviceSpecs));
    }
    else
    if (usec == USEC_FAST)
    {
        fl_QuadDeviceSpec QuadDeviceSpecs[] = {
            FL_QUADDEVICE_SPANSION_S25FL116K_250MHZ,
            FL_QUADDEVICE_SPANSION_S25FL132K_250MHZ,
            FL_QUADDEVICE_SPANSION_S25FL164K_250MHZ,
            FL_QUADDEVICE_ISSI_IS25LQ080B_250MHZ,
            FL_QUADDEVICE_ISSI_IS25LQ016B_250MHZ,
            FL_QUADDEVICE_ISSI_IS25LQ032B_250MHZ
        };
        memcpy(dSpecs, QuadDeviceSpecs, sizeof(QuadDeviceSpecs));
    }
}
#else
fl_SPIPorts *SPI_port;

// List of SPI devices that are supported by default.
fl_DeviceSpec dSpecs[] =
{
    FL_DEVICE_ATMEL_AT25DF041A,
    FL_DEVICE_ST_M25PE10,
    FL_DEVICE_ST_M25PE20,
    FL_DEVICE_ATMEL_AT25FS010,
    FL_DEVICE_WINBOND_W25X40,
    FL_DEVICE_AMIC_A25L016,
    FL_DEVICE_AMIC_A25L40PT,
    FL_DEVICE_AMIC_A25L40PUM,
    FL_DEVICE_AMIC_A25L80P,
    FL_DEVICE_ATMEL_AT25DF021,
    FL_DEVICE_ATMEL_AT25F512,
    FL_DEVICE_ESMT_F25L004A,
    FL_DEVICE_NUMONYX_M25P10,
    FL_DEVICE_NUMONYX_M25P16,
    FL_DEVICE_NUMONYX_M45P10E,
    FL_DEVICE_SPANSION_S25FL204K,
    FL_DEVICE_SST_SST25VF010,
    FL_DEVICE_SST_SST25VF016,
    FL_DEVICE_SST_SST25VF040,
    FL_DEVICE_WINBOND_W25X10,
    FL_DEVICE_WINBOND_W25X20,
    FL_DEVICE_AMIC_A25L40P,
    FL_DEVICE_MACRONIX_MX25L1005C,
    FL_DEVICE_MICRON_M25P40,
    FL_DEVICE_ALTERA_EPCS1,
};
#endif

/**
 * @brief Saves the spi port in a global variable.
 * @param SPI   Struct with the port definitions.
 */
#ifdef XCORE200
/**
 * @brief Connect to the flash. Should be called before any accessing the flash memory.
 */
void flash_init(fl_QSPIPorts *SPI)
{
    SPI_port = SPI;
    connect_to_flash();
}
#else
/**
 * @brief Connect to the flash. Should be called before any accessing the flash memory.
 */
void flash_init(fl_SPIPorts *SPI)

{
    SPI_port = SPI;
    connect_to_flash();
}
#endif


/**
 * @brief Connect to the flash. Should be called before any accessing the flash memory.
 * @return  0 if connecting was successful.
 */
int connect_to_flash(void) {

    int result =  fl_connectToDevice(SPI_port, dSpecs, sizeof(dSpecs)/sizeof(dSpecs[0]));

    if (result != 0) {
        printstrln("\nCould not connect to flash memory \n");
    }

    return result;
}



