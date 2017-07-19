/**
 * @file eeprom.xc
 * @brief Module illustrates usage of eeprom (24LC01B)
 * @author Synapticon GmbH <support@synapticon.com>
 */


#include<eeprom.h>



void eeprom_write(uint8_t addr, uint8_t data, client interface i2c_master_if i2c)
{
    i2c_regop_res_t res_reg = 1;
    while(res_reg != 0)
    {
        res_reg = i2c.write_reg(SLAVE_ADDRESS, addr, data);
    }
}

uint8_t eeprom_read(uint8_t addr, client interface i2c_master_if i2c)
{
    size_t no_bytes_sent;
    uint8_t address_ptr[1] = {addr};
    uint8_t data;
    i2c_res_t res = 0;
    while(res == 0)
         res = i2c.write(SLAVE_ADDRESS, address_ptr, 1, no_bytes_sent, 0);
    i2c.read(SLAVE_ADDRESS, &data, 1, 1);
    return data;
}

void eeprom_page_write(uint8_t data[], size_t no_of_db, client interface i2c_master_if i2c)
{
    size_t no_bytes_sent;
    i2c_res_t res = 0;
    while(res == 0)
         res = i2c.write(SLAVE_ADDRESS, data, no_of_db + 1, no_bytes_sent, 1);
}


void eeprom_service(server interface i_eeprom_communication i_eeprom, client interface i2c_master_if i2c)
{

    while (1) {
           select {
           case i_eeprom.write(uint8_t addr, uint8_t data):
                   eeprom_write(addr, data, i2c);
                   break;

           case i_eeprom.read(uint8_t addr) -> uint8_t data :
                   data = eeprom_read(addr, i2c);
                   break;

           case i_eeprom.page_write(uint8_t addr, uint8_t data[no_of_db], size_t no_of_db) :
                   uint8_t data_l[9] = {addr};
                   memcpy(&data_l[1], data, no_of_db*sizeof(uint8_t));
                   eeprom_page_write(data_l, no_of_db, i2c);
                   break;
           }
    }
}


