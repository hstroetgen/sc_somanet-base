#ifndef COMM_PROC_H_
#define COMM_PROC_H_


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

#define SPIFFS_SEEK_SET                 (0)
#define SPIFFS_SEEK_CUR                 (1)
#define SPIFFS_SEEK_END                 (2)


void spiffs_console(client SPIFFSInterface i_spiffs);

#endif
