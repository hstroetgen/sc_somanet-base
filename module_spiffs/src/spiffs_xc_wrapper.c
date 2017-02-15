/*
 * spiffs_xc_wrapper.c
 *
 *  Created on: Nov 15, 2016
 *      Author: simon
 */


#include <stdio.h>
#include <xccompat.h>
#include <spiffs.h>
#include <spiffs_xc_wrapper.h>

#define LOG_PAGE_SIZE       256
#define MAX_OPEN_FILES       16

static u8_t spiffs_work_buf[LOG_PAGE_SIZE*2];
static u8_t spiffs_fds[32*4];
static u8_t spiffs_cache_buf[(LOG_PAGE_SIZE+32)*4];

static spiffs fs;

//----------------------------------

static s32_t my_spiffs_read(CLIENT_INTERFACE(FlashDataInterface, i_data), u32_t addr, u32_t size, u8_t *dst)
{
    if_read_flash(i_data, addr, size, dst);
    return SPIFFS_OK;
}


static s32_t my_spiffs_write(CLIENT_INTERFACE(FlashDataInterface, i_data), u32_t addr, u32_t size, u8_t *src)
{
    if_write_flash(i_data, addr, size, src);
    return SPIFFS_OK;
}

static s32_t my_spiffs_erase(CLIENT_INTERFACE(FlashDataInterface, i_data), u32_t addr, u32_t size)
{
    if_erase_flash(i_data, addr, size);
    return SPIFFS_OK;
}


void my_spiffs_mount(CLIENT_INTERFACE(FlashDataInterface, i_data))
{
    spiffs_config cfg;
    cfg.phys_size = 2*1024*1024 - 524288; // use only data part (start from phys. addr 0x80000)
    cfg.phys_addr = 0; // start spiffs at start of spi flash
    cfg.phys_erase_block = 65536; // according to datasheet
    cfg.log_block_size = 65536; // let us not complicate things
    cfg.log_page_size = LOG_PAGE_SIZE; // as we said

    cfg.if_spi_flash = i_data;
    cfg.hal_read_f = my_spiffs_read;
    cfg.hal_write_f = my_spiffs_write;
    cfg.hal_erase_f = my_spiffs_erase;

    int res = SPIFFS_mount(&fs,
            &cfg,
            spiffs_work_buf,
            spiffs_fds,
            sizeof(spiffs_fds),
            spiffs_cache_buf,
            sizeof(spiffs_cache_buf),
            0);
    printf("mount res: %i\n", res);


}

void spiffs_init(CLIENT_INTERFACE(FlashDataInterface, i_data))
{
    my_spiffs_mount(i_data);
}


unsigned short iSPIFFS_open(char path[], unsigned short flags)
{
    unsigned short fd = SPIFFS_open(&fs, path,  flags, 0);
    return fd;
}

int iSPIFFS_close(unsigned short fd)
{
    int res;
    res = SPIFFS_close(&fs, fd);
    return res;
}

int iSPIFFS_write(unsigned short fd, unsigned char data[], unsigned int len)
{
    int res;
    res = SPIFFS_write(&fs, fd, data, len);
    return res;
}

int iSPIFFS_read(unsigned short fd, unsigned char data[], unsigned int len)
{
    int res;
    res = SPIFFS_read(&fs, fd, data, len);
    return res;
}

int iSPIFFS_vis(void)
{
    int res;
    res = SPIFFS_vis(&fs);
    return res;
}

int iSPIFFS_ls(void)
{
    int res;
    res = SPIFFS_ls(&fs);
    return res;
}

int iSPIFFS_check(void)
{
    int res;
    res = SPIFFS_check(&fs);
    return res;
}

int iSPIFFS_remove(unsigned short fd)
{
    int res;
    res = SPIFFS_fremove(&fs, fd);
    return res;
}

int iSPIFFS_format(void)
{
    int res;
    res = SPIFFS_format(&fs);
    return res;
}

int iSPIFFS_rename(char old[], char newPath[])
{
    int res;
    res = SPIFFS_rename(&fs, old, newPath);
    return res;
}

int iSPIFFS_seek(unsigned short fd, int offs, int whence)
{
    int res;
    res = SPIFFS_lseek(&fs, fd, offs, whence);
    return res;
}

int iSPIFFS_tell(unsigned short fd)
{
    int res;
    res = SPIFFS_tell(&fs, fd);
    return res;
}

void iSPIFFS_unmount(void)
{
    SPIFFS_unmount(&fs);
}


int iSPIFFS_status(unsigned short fd, unsigned stat[])
{
    int res;
    res = SPIFFS_fstat(&fs, fd, (spiffs_stat *)stat);
    return res;
}

int iSPIFFS_flush(unsigned short fd)
{
    int res;
    res = SPIFFS_fflush(&fs, fd);
    return res;
}

int iSPIFFS_errno(void)
{
    int res;
    res = SPIFFS_errno(&fs);
    return res;
}

int iSPIFFS_info(unsigned int total[], unsigned int used[])
{
    int res;
    res = SPIFFS_info(&fs, total, used);
    return res;
}
