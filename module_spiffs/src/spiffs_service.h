/*
 * spiffs_service.h
 *
 *  Created on: Nov 15, 2016
 *      Author: simon
 */


#ifndef SPIFFS_SERVICE_H_
#define SPIFFS_SERVICE_H_


/**
 * @brief SPIFFS Service, handling all file system operations
 */

#define MAX_FILENAME_SIZE 32
#define MAX_DATA_BUFFER_SIZE 1024

typedef struct {
  unsigned short obj_id;
  unsigned int size;
  unsigned char type;
  unsigned short pix;
  unsigned char name[MAX_FILENAME_SIZE];
} spiffs_stat;

typedef interface SPIFFSInterface SPIFFSInterface;

interface SPIFFSInterface {
    [[guarded]] unsigned short open_file(char path[], unsigned path_length, unsigned short flags);
    [[guarded]] int close_file(unsigned short fd);
    [[guarded]] int read(unsigned short fd, unsigned char data[], unsigned int len);
    [[guarded]] int write(unsigned short fd, unsigned char data[], unsigned int len);
    [[guarded]] int remove_file(unsigned short fd);
    [[guarded]] int vis(void);
    [[guarded]] int check(void);
    [[guarded]] int status(unsigned short fd, unsigned short &obj_id, unsigned int &size, unsigned char &type, unsigned short &pix, unsigned char name[]);
    [[guarded]] int rename_file(char path[], unsigned path_length, char new_path[], unsigned new_path_length);
    [[guarded]] int format(void);
    [[guarded]] void unmount(void);
    [[guarded]] int seek(unsigned short fd, int offs, int whence);
    [[guarded]] int tell(unsigned short fd);

    [[notification]] slave void service_ready ( void );
};


void spiffs_service(CLIENT_INTERFACE(FlashDataInterface, i_data), interface SPIFFSInterface server ?i_spiffs[n_spiffs], unsigned n_spiffs);

#endif /* SPIFFS_SERVICE_H_ */
