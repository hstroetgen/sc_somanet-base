#ifndef EEPROM_H_
#define EEPROM_H_

#include<i2c.h>

#define SLAVE_ADDRESS   0x50    // 01010000

/**
 * @brief Interface type to communicate with EEPROM Service.
 */

interface i_eeprom_communication {

    /**
     * @brief Store the data in EEPROM.
     *
     * @param addr address in EEPROM to store data
     * @param data data to be stored
     */

    void    write(uint8_t addr, uint8_t data);


    /**
     * @brief Read the data from EEPROM.
     *
     * @param addr address in EEPROM to read data
     * @return data
     */

    uint8_t    read(uint8_t addr);
};

void eeprom_service(server interface i_eeprom_communication i_eeprom, client interface i2c_master_if i2c);

#endif /* EEPROM_H_ */
