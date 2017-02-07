#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <print.h>
#include <xccompat.h>
#include <flash_service.h>
#include <spiffs_service.h>
#include <command_processor.h>


void test_script(client SPIFFSInterface i_spiffs)
{
    char buf[200], par1[20], par2[100], par3[10];
    int par_num, res;
    unsigned short fd = 0;

    printstrln(">>   COMMAND SERVICE STARTING...\n");

    while(1)
    {
        gets(buf);
        par_num = sscanf(buf, "%s %s %s", par1, par2, par3);
        if (par_num > 0)
        {
            if (strcmp(par1, "open") == 0)
            {
                if (par_num > 2)
                {
                    if (strcmp(par3, "rw") == 0)
                    {
                        fd  = i_spiffs.open_file(par2, strlen(par2), SPIFFS_RDWR);
                        if (fd > 0) printf("File opened with file descriptor %i\n", fd);
                        else
                            printf("Error opening file \n");
                    }
                    else
                    if (strcmp(par3, "c") == 0)
                    {
                        fd  = i_spiffs.open_file(par2, strlen(par2), SPIFFS_CREAT | SPIFFS_TRUNC | SPIFFS_RDWR);
                        if (fd > 0) printf("File created with file descriptor %i\n", fd);
                        else
                           printf("Error creating file \n");
                     }
                    else
                        printf("Unknown parameter \n");
                }
                else
                    printf("Missing parameter \n");
            }
            else
            if (strcmp(par1, "close") == 0)
            {
                 res = i_spiffs.close_file();
                 if (res < 0) printf("errno %i\n", res);
                 else
                     printf("Success... \n");
            }
            else
            if (strcmp(par1, "write") == 0)
            {
                if (par_num > 1)
                {
                    res = i_spiffs.write((unsigned char *)par2, strlen(par2));
                    if (res < 0) printf("errno %i\n", res);
                    else
                        printf("Success... \n");
                }
            }
            else
            if (strcmp(par1, "read") == 0)
            {
                if (par_num > 1)
                {
                     res = i_spiffs.read((unsigned char *)buf, atoi(par2));
                     if (res < 0) printf("Error\n");
                     else
                         printf("--> %s <--\n", buf);
                }
            }
            else
            if (strcmp(par1, "remove") == 0)
            {
                  res = i_spiffs.remove_file();
                  if (res < 0) printf("errno %i\n", res);
                  else
                      printf("Success... \n");
            }
            else
            if (strcmp(par1, "stat") == 0)
            {
                unsigned short obj_id;
                unsigned int size;
                unsigned char type;
                unsigned short pix;
                unsigned char name[32];
                res = i_spiffs.status(obj_id, size, type, pix, name);
                if (res < 0) printf("errno %i\n", res);
                //else
                  //printf("Object ID: %04x\nSize: %u\nType: %i\npix: %i\nName: %s\n", obj_id, size, type, pix, (char *)name);

              }
              else
                  printf("Unknown command \n");
        }
    }

}
