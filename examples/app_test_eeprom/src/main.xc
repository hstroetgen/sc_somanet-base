/* PLEASE REPLACE "CORE_BOARD_REQUIRED" WITH AN APPROPRIATE BOARD SUPPORT FILE FROM module_board-support */
//#include <CORE_BOARD_REQUIRED>
#include <CORE_C21-DX_G2.bsp>

/**
 * @file main.xc
 * @brief Demo application illustrates usage of module_eeprom
 * @author Synapticon GmbH <support@synapticon.com>
 */

#include<i2c.h>

/**
 * @brief Configuration structure of the I2C ports.
 */

typedef struct {
    port p_scl;     /**< I2C clock line */
    port p_sda;     /**< I2C data line */
}I2C_ports;

on tile[0]: I2C_ports i2c_p = SOMANET_I2C_PORTS;
#define slave_address   0x50    // 01010000
#define DEVICE_SIZE 128         // 128 bytes

void eeprom_comm(client interface i2c_master_if i2c)
{
    uint8_t data_send = 0xCB, data_rcv = 0x00;
    uint8_t address_ptr[1] = {0x00};
    size_t no_bytes_sent=5;
    i2c_res_t res;
    i2c_regop_res_t res_reg;

    for(int i = 0; i<DEVICE_SIZE; i++)
    {
        // Write Operation
        res_reg = i2c.write_reg(slave_address, address_ptr[0], data_send);
        printf("The res_reg = %d\n", res_reg);

        address_ptr[0] = i;

        // Read operation
        res = i2c.write(slave_address, address_ptr, 1, no_bytes_sent, 0);
        printf("The res = %d and bytes sent = %d\n", res, no_bytes_sent);
        i2c.read(slave_address, &data_rcv, 1, 1);
        printf("The data recieved is : 0x%x\n", data_rcv);
        data_rcv = 0;
//        if(data_rcv != data_send){printf("!!!!!!! ERROR : WRONG DATA RECIEVE !!!!!!!!\n");}
    }
}
int main(void)
{
    interface i2c_master_if i2c[1];
    par {
        on tile[COM_TILE] : {
           par {

                   i2c_master(i2c, 1, i2c_p.p_scl, i2c_p.p_sda, 100);
                   eeprom_comm(i2c[0]);
                }
            }
       }
    return 0;
}
