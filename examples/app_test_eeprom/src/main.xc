/* PLEASE REPLACE "CORE_BOARD_REQUIRED" WITH AN APPROPRIATE BOARD SUPPORT FILE FROM module_board-support */
#include <CORE_BOARD_REQUIRED>

/**
 * @file main.xc
 * @brief Demo application illustrates usage of module_eeprom
 * @author Synapticon GmbH <support@synapticon.com>
 */
#include <xs1.h>
#include <platform.h>
#include<stdio.h>
#include<eeprom.h>


on tile[0]: I2C_ports i2c_p = SOMANET_I2C_PORTS;


void eeprom_comm(client interface i_eeprom_communication i_eeprom)
{
    uint8_t data[8];
    uint8_t addr = 0x08;
    uint8_t d_set[8] = {0x97,0x31,0xA4, 0xB7, 0x2E,0x5B,0x97, 0xBC};
    i_eeprom.write(addr, d_set, 8);
    printf("### Random Read ###\n");
    for(int i=0; i<8; i++)
    {
        i_eeprom.read(addr + i, 1, data);
        printf("The data read from address 0x%x is = 0x%x\n", addr+i, data[0]);
    }
    printf("\n### Sequential Read ###\n");
    addr = 0x00;
    i_eeprom.write(addr, d_set, 8);
    i_eeprom.read(addr, 8, data);
    for(int i=0; i<8; i++)
    {
        printf("The data read from address 0x%x is = 0x%x\n", addr+i, data[i]);
    }
}

int main(void)
{
    interface i2c_master_if i2c[1];
    interface i_eeprom_communication i_eeprom;
    par {
        on tile[IF1_TILE] : {
           par {

                   i2c_master(i2c, 1, i2c_p.p_scl, i2c_p.p_sda, 100);
                   eeprom_service(i_eeprom, i2c[0]);
                   eeprom_comm(i_eeprom);
                }
            }
       }
    return 0;
}
