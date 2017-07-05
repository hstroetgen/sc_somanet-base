/*
 * spiffs_service.h
 *
 *  SPIFFS Service, handling all file system operations
 *  Created on: Nov 15, 2016
 *      Author: Synapticon GmbH <support@synapticon.com>
 */

#ifndef SPIFFS_SERVICE_H_
#define SPIFFS_SERVICE_H_

#include <flash_service.h>
#include <xccompat.h>

/**
 * @brief Maximum size of file name in bytes
 * !Should be the same value as defined in SPIFFS_OBJ_NAME_LEN file spiffs_config.h!
 */
#define SPIFFS_MAX_FILENAME_SIZE 128

/**
 * @brief Maximum value of file descriptor
 */
#define SPIFFS_MAX_FILE_DESCRIPTOR 4

/**
 * @brief Maximum value of itmes, which returns ls_struct() function
 */
#define SPIFFS_MAX_FILELIST_ITEMS 32

/**
 * @brief Maximum data buffer size
 */
#define SPIFFS_MAX_DATA_BUFFER_SIZE 1024

/* If the opened file exists, it will be truncated to zero length before opened */
#define SPIFFS_TRUNC                    (1<<1)
#define SPIFFS_O_TRUNC                  SPIFFS_TRUNC
/* If the opened file does not exist, it will be created before opened */
#define SPIFFS_CREAT                    (1<<2)
#define SPIFFS_O_CREAT                  SPIFFS_CREAT
 /* The opened file may only be read */
#define SPIFFS_RDONLY                   (1<<3)
#define SPIFFS_O_RDONLY                 SPIFFS_RDONLY
/* The opened file may only be written */
#define SPIFFS_WRONLY                   (1<<4)
#define SPIFFS_O_WRONLY                 SPIFFS_WRONLY
/* The opened file may be both read and written */
#define SPIFFS_RDWR                     (SPIFFS_RDONLY | SPIFFS_WRONLY)
#define SPIFFS_O_RDWR                   SPIFFS_RDWR

#define SPIFFS_EOF                      -10003
#define SPIFFS_ERR_NOT_FOUND            -10002
#define SPIFFS_ERR_FULL                 -10001

#define SPIFFS_SEEK_SET                 (0)
#define SPIFFS_SEEK_CUR                 (1)
#define SPIFFS_SEEK_END                 (2)

typedef struct {
  unsigned short obj_id;
  unsigned int size;
  unsigned char type;
  unsigned short pix;
  unsigned char name[SPIFFS_MAX_FILENAME_SIZE];
} spiffs_stat;


typedef interface SPIFFSInterface SPIFFSInterface;

interface SPIFFSInterface {

    /**
     * @brief Opens/creates a file.
     * @param path          the path of the new file
     * @param path_length   the lenght of path of the new file
     * @param flags         the flags for the open command, can be combinations of
     *                      SPIFFS_O_APPEND, SPIFFS_O_TRUNC, SPIFFS_O_CREAT, SPIFFS_O_RDONLY,
     *                      SPIFFS_O_WRONLY, SPIFFS_O_RDWR, SPIFFS_O_DIRECT, SPIFFS_O_EXCL
     * @returns the filehandle
     */
    [[guarded]] short open_file(char path[], unsigned path_length, unsigned short flags);

    /**
     * @brief Closes a filehandle. If there are pending write operations, these are finalized before closing.
     * @param fd            the filehandle of the file to close
     */
    [[guarded]] int close_file(unsigned short fd);

    /**
     * @brief Reads from given filehandle.
     * @param fd            the filehandle
     * @param buf           where to put read data
     * @param len           how much to read
     * @returns number of bytes read, or -1 if error
     */
    [[guarded]] int read(unsigned short fd, unsigned char data[], unsigned int len);

    /**
     * @brief Writes to given filehandle.
     * @param fd            the filehandle
     * @param buf           the data to write
     * @param len           how much to write
     * @returns number of bytes written, or -1 if error
     */
    [[guarded]] int write(unsigned short fd, unsigned char data[], unsigned int len);

    /**
     * @brief Removes a file by filehandle
     * @param fd            the filehandle of the file to remove
     */
    [[guarded]] int remove_file(unsigned short fd);

    /**
     * @brief Prints out a visualization of the filesystem.
     */
    [[guarded]] int vis(void);

    /**
     * @brief Prints out a list of files in filesystem.
     */
    [[guarded]] int ls(void);


    /**
     * @brief Moves list of files in filesystem to array of spiffs_stat structs
     * @param s  array of the file status structs
     */
    [[guarded]] int ls_struct(spiffs_stat s[]);

    /**
     * @brief Runs a consistency check on given filesystem.
     */
    [[guarded]] int check(void);

    /**
     * Gets file status by filehandle
     * @param fd            the filehandle of the file to stat
     * @param obj_id           Object id
     * @param size             Size of file
     * @param type             Type of file
     * @param pix              Page index
     * @param name             Name of file
     */
    [[guarded]] int status(unsigned short fd, unsigned short &obj_id, unsigned int &size, unsigned char &type, unsigned short &pix, char name[]);


    /**
    * @brief Gets file size by filehandle
    */
    [[guarded]] int get_file_size(unsigned short fd);

    /**
     * @brief Renames a file
     * @param path                 path of file to rename
     * @param path_length          length of path of file to rename
     * @param new_path             new path of file
     * @param new_path_length      length of new path of file
     */
    [[guarded]] int rename_file(char path[], unsigned path_length, char new_path[], unsigned new_path_length);

    /**
     * @brief Formats the entire file system. All data will be lost.
     * The filesystem must not be mounted when calling this.
     *
     */
    [[guarded]] int format(void);

    /**
     * @brief Unmounts the file system. All file handles will be flushed of any
     * cached writes and closed.
     */
    [[guarded]] void unmount(void);

    /**
     * @brief Moves the read/write file offset. Resulting offset is returned or negative if error.
     * seek(fd, 0, SPIFFS_SEEK_CUR) will thus return current offset.
     * @param fd            the filehandle
     * @param offs          how much/where to move the offset
     * @param whence        if SPIFFS_SEEK_SET, the file offset shall be set to offset bytes
     *                      if SPIFFS_SEEK_CUR, the file offset shall be set to its current location plus offset
     *                      if SPIFFS_SEEK_END, the file offset shall be set to the size of the file plus offse, which should be negative
     */
    [[guarded]] int seek(unsigned short fd, int offs, int whence);

    /**
     * @brief Get position in file.
     * @param fh            the filehandle of the file to check
     */
    [[guarded]] int tell(unsigned short fd);

    /**
     * @brief Flushes all pending write operations from cache for given file
     * @param fd           the filehandle of the file to flush
     */
    [[guarded]] int flush(unsigned short fd);

    /**
     * @brief Returns last error of last file operation.
     */
    [[guarded]] int errno(void);

    /**
     * @brief Returns number of total bytes available and number of used bytes.
     * This is an estimation, and depends on if there a many files with little
     * data or few files with much data.
     * @param itotal         total number of bytes in filesystem
     * @param iused          used number of bytes in filesystem
     */
    [[guarded]] int fs_info(unsigned int &itotal, unsigned int &iused);

    /**
     * @brief Will try to make room for given amount of bytes in the filesystem by moving
     * pages and erasing blocks.
     * If it is physically impossible, err_no will be set to SPIFFS_ERR_FULL. If
     * there already is this amount (or more) of free space, SPIFFS_gc will
     * silently return. It is recommended to call SPIFFS_info before invoking
     * this method in order to determine what amount of bytes to give.
     *
     * @param size          amount of bytes that should be freed
     */
    [[guarded]] int gc(unsigned int size);

    /**
     * @brief Tries to find a block where most or all pages are deleted, and erase that
     * block if found. Does not care for wear levelling. Will not move pages
     * around.
     * If parameter max_free_pages are set to 0, only blocks with only deleted
     * pages will be selected.
     *
     * Will set err_no to SPIFFS_OK if a block was found and erased,
     * SPIFFS_ERR_NO_DELETED_BLOCK if no matching block was found,
     * or other error.
     *
     * @param max_free_pages maximum number allowed free pages in block
     */
    [[guarded]] int gc_quick(unsigned short max_free_pages);


    [[notification]] slave void service_ready ( void );
};


/**
 * @brief SPIFFS Service provides a server, which managed the SPI Flash File System.
 *
 * @param CLIENT_INTERFACE(FlashDataInterface, i_data)  Client interface for flash service
 * @param i_spiffs   Server interfaces for SPIFFS service
 * @param n_spiffs   Pattern variable for SPIFFS service
 *
 */
void spiffs_service(CLIENT_INTERFACE(FlashDataInterface, i_data), interface SPIFFSInterface server i_spiffs[n_spiffs], unsigned n_spiffs);

#endif /* SPIFFS_SERVICE_H_ */
