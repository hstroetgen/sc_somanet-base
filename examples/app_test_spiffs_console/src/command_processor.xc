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
    char buf[256], par1[MAX_FILENAME_SIZE], par2[100], par3[MAX_FILENAME_SIZE];
    int par_num, res;
    unsigned short fd = 0;
    unsigned short flags = 0;

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
                        flags = SPIFFS_RDWR;
                    else
                    if (strcmp(par3, "ro") == 0)
                        flags = SPIFFS_RDONLY;
                    else
                    if (strcmp(par3, "wo") == 0)
                        flags = SPIFFS_WRONLY;
                    else
                    if (strcmp(par3, "c") == 0)
                        flags = (SPIFFS_CREAT | SPIFFS_TRUNC | SPIFFS_RDWR);
                    else
                    {
                        flags = 0;
                        printf("Unknown parameter \n");
                    }

                    if (flags)
                    {
                        fd  = i_spiffs.open_file(par2, strlen(par2), flags);
                        if (fd > 0) printf("File created with file descriptor %i\n", fd);
                        else
                            printf("Error creating file \n");
                    }
                }
                else
                    printf("Missing parameter \n");
            }
            else
            if (strcmp(par1, "close") == 0)
            {
                 res = i_spiffs.close_file(fd);
                 if (res < 0) printf("errno %i\n", res);
                 else
                     printf("Success... \n");
            }
            else
            if (strcmp(par1, "write") == 0)
            {
                if (par_num > 1)
                {
                    res = i_spiffs.write(fd, (unsigned char *)par2, strlen(par2) + 1);
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
                     res = i_spiffs.read(fd, (unsigned char *)buf, atoi(par2));
                     if (res < 0) printf("Error\n");
                     else
                         printf("--> %s <--\n", buf);
                }
            }
            else
            if (strcmp(par1, "remove") == 0)
            {
                  res = i_spiffs.remove_file(fd);
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
                unsigned char name[MAX_FILENAME_SIZE];
                res = i_spiffs.status(fd, obj_id, size, type, pix, name);
                if (res < 0) printf("errno %i\n", res);
                //else
                  //printf("Object ID: %04x\nSize: %u\nType: %i\npix: %i\nName: %s\n", obj_id, size, type, pix, (char *)name);

              }
              else
              if (strcmp(par1, "rename") == 0)
              {
                  if (par_num > 2)
                  {
                       res  = i_spiffs.rename_file(par2, strlen(par2), par3, strlen(par3));
                       if (res < 0) printf("errno %i\n", res);
                       else
                           printf("Success... \n");

                   }
                   else
                       printf("Missing parameter \n");
              }
              else
              if (strcmp(par1, "format") == 0)
              {
                  res = i_spiffs.format();
                  if (res < 0) printf("errno %i\n", res);
                  else
                      printf("Success... \n");
              }
              else
              if (strcmp(par1, "seek") == 0)
              {
                  if (par_num > 2)
                  {
                      if (strcmp(par3, "set") == 0)
                          flags = SPIFFS_SEEK_SET;
                      else
                      if (strcmp(par3, "cur") == 0)
                          flags = SPIFFS_SEEK_CUR;
                      else
                      if (strcmp(par3, "end") == 0)
                          flags = SPIFFS_SEEK_END;
                      else
                      {
                          flags = 3;
                          printf("Missing parameter \n");
                      }
                      if (flags < 3)
                      {
                          res = i_spiffs.seek(fd, atoi(par2), flags);
                          if (res < 0) printf("errno %i\n", res);
                          else
                              printf("Success... \n");
                      }
                   }
               }
               else
               if (strcmp(par1, "tell") == 0)
               {
                   res = i_spiffs.tell(fd);
                   if (res < 0) printf("errno %i\n", res);
                   else
                       printf("-> %i\n", res);
               }
               else
               if (strcmp(par1, "set") == 0)
               {
                   if (par_num > 1)
                   {
                       fd = atoi(par2);
                       printf("File descriptor: %i\n", fd);
                   }
                   else
                       printf("Missing parameter \n");

               }
               else
                  printf("Unknown command \n");
        }
    }

}
