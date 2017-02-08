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

typedef interface SPIFFSInterface SPIFFSInterface;

interface SPIFFSInterface {
    [[guarded]] unsigned short open_file(char path[], unsigned path_length, unsigned short flags);
    [[guarded]] int close_file(void);
    [[guarded]] int read(unsigned char data[], unsigned int len);
    [[guarded]] int write(unsigned char data[], unsigned int len);
    [[guarded]] int remove_file(void);
    [[guarded]] int vis(void);
    [[guarded]] int check(void);
    [[guarded]] int status(unsigned short &obj_id, unsigned int &size, unsigned char type, unsigned short pix, unsigned char name[]);
    [[guarded]] int rename_file(char path[], unsigned path_length, char new_path[], unsigned new_path_length);
    [[guarded]] int format(void);
    [[guarded]] int seek(int offs, int whence);
};

void spiffs_service(CLIENT_INTERFACE(FlashDataInterface, i_data), interface SPIFFSInterface server ?i_spiffs);

#endif /* SPIFFS_SERVICE_H_ */
