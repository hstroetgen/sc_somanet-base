/**
 * @file flash_boot.xc
 * @author Synapticon GmbH <support@synapticon.com>
 */

#include <flash_boot.h>
#include <print.h>
#include <string.h>
#include <stdbool.h>

#ifdef XCORE200
#include <quadflashlib.h>
#else
#include <flashlib.h>
#endif

#include <flash_common.h>

#define DEBUG

fl_BootImageInfo bootImageInfo;
unsigned image_size_rest;
unsigned int write_address          = 0;
unsigned int write_limit_address    = 0;

/***************** HELPER FUNCTIONS ***********************************/
/**
 * Return the address one past the end of the sector.
 */
static int fl_getSectorEndAddress(int sectorNum)
{
  return fl_getSectorAddress(sectorNum) + fl_getSectorSize(sectorNum);
}

/**
 * Returns the number of the first sector containing the specified
 * address.
 * \return The number of sector or -1 if there is no such sector.
 */
static int getSectorContaining(unsigned address)
{
  unsigned numSectors = fl_getNumSectors();
  unsigned sector;
  for (sector = 0; sector < numSectors; sector++) {
    if (fl_getSectorEndAddress(sector) > address)
      return sector;
  }
  return -1;
}

/**
 * Returns the number of the first sector starting at or after the specified
 * address.
 * \return The number of sector or -1 if there is no such sector.
 */
static int getSectorAtOrAfter(unsigned address)
{
  unsigned numSectors = fl_getNumSectors();
  unsigned sector;
  for (sector = 0; sector < numSectors; sector++) {
    if (fl_getSectorAddress(sector) >= address)
      return sector;
  }
  return -1;
}

/**
 * @brief: Reverses all bits in a byte and returns the result
 */
unsigned char BitRev(unsigned char c)
{
  unsigned char res = 0;
  for( int b=0; b<8; b++ )
  {
    res <<= 1;
    res |= c&1;
    c >>= 1;
  }

  return( res );
}

/**
 * @brief: Calculates the CRC of a data block and compares it to an expected CRC
 * @return: Returns the CRC calculated
 */
unsigned calc_crc_block(unsigned * data, unsigned *crc, unsigned num_words)
{
  unsigned polynom = 0xedb88320;

  for(unsigned i = 0; i < num_words; i++)
  {
    asm volatile("crc32 %0, %2, %3" : "=r" (*crc) : "0" (*crc), "r" (data[i]), "r" (polynom));
  }

  //asm volatile("crc32 %0, %2, %3" : "=r" (crc) : "0" (crc), "r" (expected_crc), "r" (polynom));

  return *crc;
}

/**
 * @brief: Checks the CRC of an image
 * @return: True if CRC is correct, false if not
 */
bool crc_check_image(unsigned image_start_address)
{
    /* Check CRC */
#ifdef DEBUG
    printstrln("Start CRC-Check:");
    printstr("CRC-Image Start Address: 0x");
    printhexln(image_start_address);
#endif

    unsigned char crc_read_buf[FLASH_PAGE_SIZE];
    unsigned expected_image_crc = 0;
    unsigned crc = 0xFFFFFFFF;
    unsigned image_size = 0;

    /* Get expected page CRC as well as image size */
    //Read the page where the image starts...
    fl_readPage(image_start_address, crc_read_buf);

    //Sort the bits read from SPI
    for(unsigned i = 0; i < FLASH_PAGE_SIZE; i++)
      crc_read_buf[i] = BitRev(crc_read_buf[i]);

    expected_image_crc = *(unsigned *)&crc_read_buf[8];
    image_size = *(unsigned *)&crc_read_buf[24];

    /* CRC header page */
    calc_crc_block((unsigned *)&crc_read_buf[12], &crc, (FLASH_PAGE_SIZE / 4) - 3);

    /* Run through remaining pages and CRC them */
    for (unsigned read_addr = image_start_address + FLASH_PAGE_SIZE;
            read_addr < image_start_address + image_size; read_addr += FLASH_PAGE_SIZE)
    {
        unsigned words = 0;

        /* Read page */
        fl_readPage(read_addr, crc_read_buf);

        /* Sort the bits read from SPI */
        for(unsigned i = 0; i < FLASH_PAGE_SIZE; i++)
          crc_read_buf[i] = BitRev(crc_read_buf[i]);

        /* Last page */
        if ((read_addr + FLASH_PAGE_SIZE) > (image_start_address + image_size))
            words = (image_start_address + image_size - read_addr) / 4;
        else /* Regular page */
           words = FLASH_PAGE_SIZE / 4;

        calc_crc_block((unsigned *)&crc_read_buf, &crc, words);
    }

    /* CRC the CRC */
    asm volatile("crc32 %0, %2, %3" : "=r" (crc) : "0" (crc), "r" (expected_image_crc), "r" (0xedb88320));

    if (crc == 0xFFFFFFFF)
    {
#ifdef DEBUG
        printstrln("CRC OK");
#endif
        return true;
    }
    else
    {
#ifdef DEBUG
        printstrln("CRC CHECK FAILED!");
#endif
        return false;
    }

}

/***************************** MAIN FUNCTIONS *************************************************/
/**
 * @brief Trys to find an upgrade image. First error (no factory image) should never occur.
 * @return 0 if factory and upgrade image were found.
 */
int flash_find_images(void) {
    if (fl_getFactoryImage(&bootImageInfo)) {
        return ERR_NO_FACTORY_IMAGE;
    }

#ifdef DEBUG
    printstr("Start address Factory Image: 0x"); printhexln(bootImageInfo.startAddress);
    printstr("Size: "); printintln(bootImageInfo.size);
    printstr("factory: "); printintln(bootImageInfo.factory);
#endif
    // 0 if image found; 1, when not
    if (fl_getNextBootImage(&bootImageInfo)) {
        return ERR_NO_UPGRADE_IMAGE;
    }
    return NO_ERROR;
}

/**
 * @brief Checks if a bootable image is installed
 * @return 0 if factory and upgrade image were found.
 */
int upgrade_image_installed(void)
{
    int error = connect_to_flash();

    if (error)
        return ERR_CONNECT_FAILED;

    error = flash_find_images();

    if (error)
    {
        fl_disconnect();
        return error;
    }


    /* CRC Check of the upgrade image */
    if (!crc_check_image(bootImageInfo.startAddress))
    {
#ifdef DEBUG
        printstrln("Upgrade Image CRC CHECK FAILED!");
#endif
        fl_disconnect();

        return ERR_CRC_CHECK_FAILED;
    }

#ifdef DEBUG
    printstrln("Upgrade Image CRC OK");
#endif

    // Disconnect from the flash
    if (fl_disconnect()){
        #ifdef DEBUG
        printstr( "Could not disconnect from FLASH\n" );
        #endif
        return ERR_DISCONNECT_FAILED;
    }

    /* Signal success */
    return 0;
}

/**
 * @brief Writes a page into the boot partition. Addresses are automatically calculated in fl_writeImagePage.
 *        Image_size_rest is set in flash_prepare_boot_partition and equals the total size of the upgrade image.
 * @param page      Contains one page of the image.
 * @param size      Size of the page.
 * @return 0 if writing is succesful.
 */
int flash_write_boot_page(unsigned char page[], unsigned size)
{
    unsigned char readBuf[FLASH_PAGE_SIZE];
    int error = 0;

    if (size < FLASH_PAGE_SIZE)
    {
        #ifdef DEBUG
            printstrln("ERROR: Data package smaller than page size");
        #endif
        return ERR_DATA_PACKAGE_TOO_SMALL;
    }

    unsigned char * data_ptr = &page[0];

    /* Make sure we write everything page-by-page */
    while (1)
    {
        if (image_size_rest > 0)
        {
            error = connect_to_flash();
            if (error) {
                return ERR_CONNECT_FAILED;
            }

            /* Check if we are still within the limits */
            if ((write_address + FLASH_PAGE_SIZE) >= write_limit_address)
                return ERR_OUT_OF_LIMITS;

            /* Check if we cross sector boundary, if we do -> delete sector before writing */
            if (getSectorContaining(write_address) != getSectorContaining(write_address + FLASH_PAGE_SIZE))
                fl_eraseSector(getSectorContaining(write_address + FLASH_PAGE_SIZE));

            /* If write error happened, try 5 times, then give up */
            for (int i = 0; i < 5; i ++)
            {
                /* Write data to flash */
                fl_writePage(write_address, data_ptr);

                /* Check if data is correct */
                fl_readPage(write_address, readBuf);
                error = memcmp(data_ptr, readBuf, FLASH_PAGE_SIZE);

                #ifdef DEBUG
                    if (error != 0)
                    {
                        printstr("Write attempt "); printint(i); printstrln(" failed");
                    }
                #endif

                if (error == 0)
                    break;
            }

            if (error) {
                #ifdef DEBUG
                printstr("Writing failed!\n");
                #endif
                return ERR_WRITE_FAILED;
            }

            /* Increment write address */
            write_address += FLASH_PAGE_SIZE;

            // Disconnect from the flash
            error = fl_disconnect();
            if (error){
                #ifdef DEBUG
                printstr( "Could not disconnect from FLASH\n" );
                #endif
                return ERR_DISCONNECT_FAILED;
            }
            image_size_rest -= size;
        }

        /* Increment page array pointer */
        data_ptr += FLASH_PAGE_SIZE;

        /* Break condition - make sure we never run out of boundaries */
        if (data_ptr >= &page[size - 1])
            break;
    }

    return NO_ERROR;
}

/**
 * @brief Read on boot page
 * @param[out] data Page buffer.
 * @param[in] size  Size of page buffer.
 * @return 0, if no error occured
 */
int flash_read_boot(unsigned char data[], unsigned size) {
    //TODO
    return 0;
}

/**
 * @brief Erase upgrade image if there is one.
 * @return 0, if no error occured.
 */
int flash_erase_image(void) {
    int found_image, error;

    error = connect_to_flash();
    if (error) {
        #ifdef DEBUG
        printstr("Error: Connect to flash during preparation\n");
        #endif
        return ERR_CONNECT_FAILED;
    }

    // error should be 0 or 11. 11 equals No upgrade image found.
    error = flash_find_images();

    // Convert error in found_image flag. An error of 0 equals upgrade image were found -> 1.
    // An error of 11 equals no upgrade image was found -> 0.
    found_image = !error;

    // If image was found, delete it (deleting means: erase the first image page)
    if (found_image)
    {
        // Reset bootimageInfo and get factory image info.
        // fl_eraseNextBootImage will call fl_getNextBootImage to get upgrade image info.
        if (fl_getFactoryImage(&bootImageInfo)) {
            #ifdef DEBUG
            printstr("ERR_NO_FACTORY_IMAGE\n");
            #endif
            return ERR_NO_FACTORY_IMAGE;
        }
        error = fl_eraseNextBootImage(&bootImageInfo);

        if (error) {
            #ifdef DEBUG
            printstr("Error: Erasing upgrade image failed\n");
            #endif
            return ERR_ERASE_FAILED;
        }
    }
    else
        return ERR_NO_UPGRADE_IMAGE;

    return NO_ERROR;
}


/**
 * @brief Prepares the boot partition to accept a new image
 * @return 0, if no error occured.
 */
int flash_prepare_boot_partition() {
    int error = 0;

    #ifdef DEBUG
    printstr("Prepare boot partition\n");
    #endif

    // Connect to flash
    error = connect_to_flash();
    if (error) {
        #ifdef DEBUG
        printstr("Error: Connect to flash during preparation\n");
        #endif
        return ERR_CONNECT_FAILED;
    }

    /* Get information about the factory image */
    fl_getFactoryImage(&bootImageInfo);

    /* Calculate maximum image size */
    unsigned max_image_size = fl_getFlashSize() - fl_getDataPartitionSize() - (bootImageInfo.size + bootImageInfo.startAddress);
    image_size_rest = max_image_size;

    /* Calculate start address + limit address for writing */
    write_address       = bootImageInfo.startAddress + bootImageInfo.size;
    write_limit_address = fl_getFlashSize() - fl_getDataPartitionSize();
    /* Erase first sector after address */
    fl_eraseSector(getSectorAtOrAfter(write_address));

    /* Get sector start address, which is start address for writing */
    write_address = fl_getSectorAddress(getSectorAtOrAfter(write_address));

    #ifdef DEBUG
        printstrln("Preparing image area...");
        printstr("Start address to delete: "); printintln(write_address);
        printstr("Max write address: "); printintln(write_limit_address);
    #endif


    #ifdef DEBUG
        printstrln("1st Sector Deleted!");
    #endif


    #ifdef DEBUG
        printstrln("Area prepared!");
    #endif

    // Disconnect from the flash
    error = fl_disconnect();
    if (error){
        #ifdef DEBUG
        printstr("Could not disconnect from FLASH\n");
        #endif
        return ERR_DISCONNECT_FAILED;
    }

    return NO_ERROR;
}



/**
 * @brief Erases the whole boot-partition only keeping the bootloader image
 * @return 0, if no error occured.
 */
int flash_erase_boot_partition()
{
    int error = 0;

    #ifdef DEBUG
    printstr("Erase boot partition\n");
    #endif

    // Connect to flash
    error = connect_to_flash();
    if (error) {
        #ifdef DEBUG
        printstr("Error: Connect to flash during preparation\n");
        #endif
        return ERR_CONNECT_FAILED;
    }

    /* Get information about the factory image */
    fl_getFactoryImage(&bootImageInfo);

    /* Calculate maximum image size */
    unsigned max_image_size = fl_getFlashSize() - fl_getDataPartitionSize() - (bootImageInfo.size + bootImageInfo.startAddress);
    image_size_rest = max_image_size;

    /* Erase everything between end of factory image and data partition */
    int eraseStartSector    = getSectorAtOrAfter(bootImageInfo.startAddress + bootImageInfo.size);
    int dataPartSize        = fl_getDataPartitionSize();
    int eraseEndSector      = 0;
    if (dataPartSize > 0)
        eraseEndSector = getSectorContaining(fl_getFlashSize() - fl_getDataPartitionSize()) - 1;
    else
        eraseEndSector = fl_getNumSectors() - 1;

    #ifdef DEBUG
        printstrln("Deleting image area...");
        printstr("Start address to delete: "); printintln(fl_getSectorAddress(eraseStartSector));
        printstr("End address to delete: "); printintln(fl_getSectorEndAddress(eraseEndSector));
    #endif

    // Do actual erase
    for (int i = eraseStartSector; i <= eraseEndSector; i ++)
        fl_eraseSector(i);

    #ifdef DEBUG
        printstrln("Deleted!");
    #endif


    // Disconnect from the flash
    error = fl_disconnect();
    if (error){
        #ifdef DEBUG
        printstr("Could not disconnect from FLASH\n");
        #endif
        return ERR_DISCONNECT_FAILED;
    }

    return NO_ERROR;
}
