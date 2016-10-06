/**
 * @file flash_boot.xc
 * @author Synapticon GmbH <support@synapticon.com>
 */

#include <flash_boot.h>
#include <print.h>
#include <flashlib.h>
#include <flash_common.h>

//#define DEBUG

fl_BootImageInfo bootImageInfo;
unsigned image_size_rest;

/**
 * @brief Trys to find an upgrade image. First error (no factory image) should never occur.
 * @return 0 if factory and upgrade image were found.
 */
int flash_find_images(void) {
    if (fl_getFactoryImage(&bootImageInfo)) {
        return ERR_NO_FACTORY_IMAGE;
    }

    // 0 if image found; 1, when not
    if (fl_getNextBootImage(&bootImageInfo)) {
        return ERR_NO_UPGRADE_IMAGE;
    }
    return NO_ERROR;
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

    if (image_size_rest > 0)
    {
        int error = connect_to_flash();
        if (error) {
            return ERR_CONNECT_FAILED;
        }

        error = fl_writeImagePage(page);

        if (error) {
            #ifdef DEBUG
            printstr("Writing failed!\n");
            #endif
            return ERR_WRITE_FAILED;
        }

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
    #ifdef DEBUG
    printstrln("");
    #endif
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
 * @brief Prepares the boot partition. This means, the function is searching other images
 *        and calculates in dependencies of found images the addresses for the upgrade image.
 * @return 0, if no error occured.
 */
int flash_prepare_boot_partition() {
    // Calculating addresses of the factory image.
    int found_image;
    int complete = 0;
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

    /* Calculate maximum image size */
    fl_BootImageInfo bootImageInfoFactoryImage;
    fl_getFactoryImage(&bootImageInfoFactoryImage);
    unsigned max_image_size = fl_getFlashSize() - fl_getDataPartitionSize() - (bootImageInfoFactoryImage.size + bootImageInfoFactoryImage.startAddress);

    // error should be 0 or 11. 11 equals No upgrade image found.
    error = flash_find_images();

    if (error == ERR_NO_FACTORY_IMAGE)
    {
        #ifdef DEBUG
        printstr("ERR_NO_FACTORY_IMAGE\n");
        #endif
        return ERR_NO_FACTORY_IMAGE;
    }
    // Convert error in found_image flag. An error of 0 equals upgrade image were found -> 1.
    // An error of 11 equals no upgrade image was found -> 0.
    found_image = !error;

    image_size_rest = max_image_size;

    // While loop is necessary, cause both of the functions need sometimes more then one call.
    while (!complete) {
        if (found_image) {
            // Replace Image
            #ifdef DEBUG
            printstr("Replace Image\n");
            #endif
            complete = fl_startImageReplace(&bootImageInfo, max_image_size);
        } else {
            // Add Image
            #ifdef DEBUG
            printstr("Add Image\n");
            #endif
            complete = fl_startImageAdd(&bootImageInfo, max_image_size, 0);
        }
    }

    // Disconnect from the flash
    error = fl_disconnect();
    if (error){
        #ifdef DEBUG
        printstr("Could not disconnect from FLASH\n");
        #endif
        return ERR_DISCONNECT_FAILED;
    }
    #ifdef DEBUG
    //printstrln("");
    #endif
    return NO_ERROR;
}
