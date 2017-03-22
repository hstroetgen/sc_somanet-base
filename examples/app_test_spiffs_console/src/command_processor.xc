#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <print.h>
#include <xccompat.h>
#include <flash_service.h>
#include <spiffs_service.h>
#include <command_processor.h>
#include <syscall.h>

#define BUFFER_SIZE 5000

void test_script(client SPIFFSInterface i_spiffs)
{
    unsigned char buf[BUFFER_SIZE];
    char par1[MAX_FILENAME_SIZE], par2[1024], par3[MAX_FILENAME_SIZE];
    int par_num, res;
    unsigned short fd = 0;
    unsigned short flags = 0;

    select {
        case i_spiffs.service_ready():

            printstrln(">>   COMMAND SERVICE STARTING...\n");

            while(1)
            {
            printstr(">");
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
                            if (fd > 0) printf("File opened with file descriptor %i\n", fd);
                            else
                                printf("Error opening file \n");
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
                        memset(buf, 0 , sizeof(buf));
                        res = i_spiffs.write(fd, (unsigned char *)par2, strlen(par2) + 1);
                        if (res < 0) printf("errno %i\n", res);
                        else
                            printf("Writed: %i\n", res);
                    }
                }
                else
                if (strcmp(par1, "read") == 0)
                {
                    if (par_num > 1)
                    {
                         memset(buf, 0 , sizeof(buf));
                         res = i_spiffs.read(fd, (unsigned char *)buf, atoi(par2));
                         if (res < 0) printf("Error\n");
                         else
                             printf("Readed: %i b\n--> %s <--\n",res, buf);
                    }
                }
                else
                if (strcmp(par1, "fwrite") == 0)
                {
                    if (par_num > 1)
                    {
                        int cfd = _open(par2, O_RDONLY, 0);
                        if (cfd == -1)
                        {
                            printstrln("Error: file open failed");
                            //break;
                        }

                        int fread_size = 1;
                        int writed_counter = 0;
                        while (fread_size > 0)
                        {
                            memset(buf, 0 , sizeof(buf));
                            fread_size = _read(cfd, buf, BUFFER_SIZE);

                            res = i_spiffs.write(fd, buf, fread_size);
                            if (res < 0)
                            {
                                printf("errno %i\n", res);
                                break;
                            }
                            else
                            {
                                writed_counter += res;
                                printf("Writed: %i\n", writed_counter);
                                i_spiffs.flush(fd);
                            }
                        }

                        if (_close(cfd) != 0)
                        {
                            printstrln("Error: file close failed.");
                            //break;
                        }
                    }
                }
                else
                if (strcmp(par1, "fread") == 0)
                {
                    if (par_num > 1)
                    {
                        unsigned short obj_id;
                        unsigned int size;
                        unsigned char type;
                        unsigned short pix;
                        unsigned char name[MAX_FILENAME_SIZE];

                        int cfd = _open(par2, O_WRONLY | O_CREAT | O_TRUNC, S_IREAD | S_IWRITE);
                        if (cfd == -1)
                        {
                             printstrln("Error: file open failed");
                             break;
                        }

                        memset(buf, 0 , sizeof(buf));
                        res = i_spiffs.status(fd, obj_id, size, type, pix, name);
                        if (res < 0)
                        {
                            printf("errno %i\n", res);
                            //break;
                        }

                        int readed_counter = 0;
                        for (int il = size; il > 0; il = il - BUFFER_SIZE)
                        {
                            int read_len = (il > BUFFER_SIZE ? BUFFER_SIZE : il);
                            res = i_spiffs.read(fd, buf, read_len);
                            if (res < 0)
                            {
                                printf("Error\n");
                                //break;
                            }
                            else
                            {
                                readed_counter += res;
                                printf("Readed: %i b\n",readed_counter);
                            }

                            int fwrite_size = _write(cfd, buf, read_len);
                        }

                        if (_close(cfd) != 0)
                        {
                            printstrln("Error: file close failed.");
                            break;
                        }
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
                    else
                      printf("Object ID: %04x\nSize: %u\nType: %i\npix: %i\nName: %s\n", obj_id, size, type, pix, (char *)name);

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
                      printf("Formatting... \n");
                      res = i_spiffs.format();
                      if (res < 0) printf("errno %i\n", res);
                      else
                          printf("Success... \n");
                  }
                  else
                  if (strcmp(par1, "vis") == 0)
                  {
                      res = i_spiffs.vis();
                      if (res < 0) printf("errno %i\n", res);
                      else
                          printf("Success... \n");
                  }
                  else
                  if (strcmp(par1, "ls") == 0)
                  {
                      printf("Scanning file system... \n");
                      res = i_spiffs.ls();
                      if (res < 0) printf("errno %i\n", res);
                      else
                          printf("Success... \n");
                  }
                  else
                  if (strcmp(par1, "check") == 0)
                  {
                      printf("Checking... \n");
                      res = i_spiffs.check();
                      if (res < 0) printf("errno %i\n", res);
                      else
                          printf("Success... \n");
                  }
                  else
                  if (strcmp(par1, "unmount") == 0)
                  {
                      i_spiffs.unmount();
                      printf("Unmounted... \n");
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
                   if (strcmp(par1, "info") == 0)
                   {
                       unsigned int total, used;
                       res = i_spiffs.fs_info(total, used);
                       if (res < 0) printf("errno %i\n", res);
                       else
                           printf("Total: %i, Used: %i\n", total, used);
                   }
                   else
                   if (strcmp(par1, "errno") == 0)
                   {
                       res = i_spiffs.errno();
                       if (res < 0) printf("errno %i\n", res);
                       else
                          printf("No errors\n");
                    }
                   else
                   if (strcmp(par1, "flush") == 0)
                   {
                       res = i_spiffs.flush(fd);
                       if (res < 0) printf("errno %i\n", res);
                       else
                           printf("Success... \n", res);
                    }
                    else
                    if (strcmp(par1, "gc") == 0)
                    {
                        if (par_num > 1)
                        {
                            res = i_spiffs.gc(atoi(par2));
                            if (res < 0) printf("errno %i\n", res);
                            else
                                printf("Success... \n", res);
                         }
                         else
                             printf("Missing parameter \n");
                    }
                    else
                    if (strcmp(par1, "gcq") == 0)
                    {
                        if (par_num > 1)
                        {
                            res = i_spiffs.gc_quick(atoi(par2));
                            if (res < 0) printf("errno %i\n", res);
                            else
                                printf("Success... \n", res);
                         }
                         else
                             printf("Missing parameter \n");
                    }
                    else
                      printf("Unknown command \n");
            }
        }
    break;
    }


}
