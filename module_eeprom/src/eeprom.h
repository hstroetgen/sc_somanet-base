#ifndef EEPROM_H_
#define EEPROM_H_

#include<i2c.h>
#include<string.h>

#define SLAVE_ADDRESS   0x50    // 01010000
#define EEPROM_SIZE     128     // 128 bytes

/**
 * @brief Configuration structure of the I2C ports.
 */
typedef struct {
    port p_scl;     /**< I2C clock line */
    port p_sda;     /**< I2C data line */
}I2C_ports;



/**
 * @brief Interface type to communicate with EEPROM Service.
 */

interface i_eeprom_communication {

    /**
     * @brief Read the data from particular address in EEPROM.
     *
     * @param addr base address (7 bit address ranges 0x00 to 0x7F) in EEPROM to read data
     * @param no_of_bytes number of bytes to read from that base address
     * @param data buffer to fill with data
     */

    void    read(uint8_t addr, uint8_t no_of_bytes, uint8_t data[]);

    /**
     * @brief Write the data using in EEPROM.
     *
     * @param addr address (7 bit address ranges 0x00 to 0x7F) in EEPROM to write data from
     * @param data set of data to be written
     * @param no_of_db number of data bytes to write from the set of data. (no_of_db = 1 for random write mode and 1 < no_of_db <= 8  for page write mode). The no_of_db should not be greater than 8.
     */


    void    write(uint8_t addr, uint8_t data[no_of_db], uint8_t no_of_db);
};


/**
 * @brief Service to read and write data from 24LC01BT-I/LT EEPROM.
 *
 * @param i_eeprom eeprom communication interface for the eeprom_service.
 * @param i2c_master_if communication interface with an I2C master component.
 */
void eeprom_service(server interface i_eeprom_communication i_eeprom, client interface i2c_master_if i2c);

#endif /* EEPROM_H_ */
