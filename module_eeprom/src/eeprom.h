#ifndef EEPROM_H_
#define EEPROM_H_

#include<i2c.h>
#include<string.h>

#define SLAVE_ADDRESS   0x50    // 01010000

/**
 * @brief Interface type to communicate with EEPROM Service.
 */

interface i_eeprom_communication {

    /**
     * @brief Store the data at particular address in EEPROM.
     *
     * @param addr address in EEPROM to store data
     * @param data data to be stored
     */

    void    write(uint8_t addr, uint8_t data);


    /**
     * @brief Read the data from particular address in EEPROM.
     *
     * @param addr address in EEPROM to read data
     * @return data
     */

    uint8_t    read(uint8_t addr);

    /**
     * @brief Write the data using page write mode in EEPROM.
     *
     * @param addr address in EEPROM to write data from
     * @param data set of data to be written
     * @param no_of_db number of data bytes to write from the set of data
     */


    void    page_write(uint8_t addr, uint8_t data[no_of_db], size_t no_of_db);
};

void eeprom_service(server interface i_eeprom_communication i_eeprom, client interface i2c_master_if i2c);

#endif /* EEPROM_H_ */
