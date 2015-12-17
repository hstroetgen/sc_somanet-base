/*
 * flash_service.xc
 *
 *  Created on: 17.12.2015
 *      Author: hstroetgen
 */

#include <flash_service.h>
#include <flash_boot.h>
#include <flash_data.h>

void flash_service_loop(fl_SPIPorts &SPI, server interface if_flash_data if_data, server interface if_flash_boot if_boot)
{
    int command;
    int data_length; /* data length exceeds page length error */
    int page;        /* page exceeds error, no data partition found error */
    unsigned char data[PAGE_SIZE];
    int status;      /* erase all pages atleast once if status is always 0 even if data partition is found */

    flash_init(SPI);

    // XXX code in the cases is just scrap and random or symbolic
    while (1)
    {
        select
        {
                /* Data Field update */
            case if_data.read(char data[], unsigned nbytes, unsigned address):
            {       // read

                // TODO Do flash management
                status = __read_data_flash(page, data);

            }
            break;
            case if_data.write(char data[], unsigned nbytes) -> int address:
            { // write

                status = __write_data_flash(data, data_length, page);
            }
            break;
            // XXX we don't need addresses here, because the position in the boot partition will be calculated automatically.
            // bii provides the address.
            case if_boot.read(char data[], unsigned nbytes, fl_BootImageInfo &bii):
            {
                //fl_startImageRead(b)
                read_boot_flash();
            }
            break;
            case if_boot.write(char data[], unsigned nbytes):
            {
                write_boot_flash();
            }
            break;
            default:
                break;
        }
    }
}
