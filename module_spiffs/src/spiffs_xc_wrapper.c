/*
 * spiffs_xc_wrapper.c
 *
 *  Created on: Nov 15, 2016
 *      Author: simon
 */


#include <stdio.h>
#include <xccompat.h>
#include <spiffs.h>
#include <spiffs_service.h>


#define LOG_PAGE_SIZE       256

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
    cfg.phys_size = 2*1024*1024; // use all spi flash
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


void test_wrapper_function()
{
    char buf[12];

       // Surely, I've mounted spiffs before entering here

       spiffs_file fd = SPIFFS_open(&fs, "my_file", SPIFFS_CREAT | SPIFFS_TRUNC | SPIFFS_RDWR, 0);
       if (SPIFFS_write(&fs, fd, (u8_t *)"Hello world", 12) < 0) printf("errno %i\n", SPIFFS_errno(&fs));
       SPIFFS_close(&fs, fd);

       fd = SPIFFS_open(&fs, "my_file", SPIFFS_RDWR, 0);
       if (SPIFFS_read(&fs, fd, (u8_t *)buf, 12) < 0) printf("errno %i\n", SPIFFS_errno(&fs));
       SPIFFS_close(&fs, fd);

       printf("--> %s <--\n", buf);

}
