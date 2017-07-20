/**
 * @file rtc_config.h
 * @author Synapticon GmbH <support@synapticon.com>
 */

#ifndef RTC_CONFIG_H_
#define RTC_CONFIG_H_
#include "i2c.h"

/**
 * @brief Definition for referring to M41T62LC6F clock registers
 */

#define tens_hundreds_seconds   0x0
#define Seconds                 0x1
#define Minutes                 0x2
#define Hours                   0x3
#define Day                     0x4
#define Date                    0x5
#define Century_Month           0x6
#define Year                    0x7
#define Calibration             0x8
#define Al_month                0xA
#define Flags                   0xF
#define Addr_Slave              0x68  // (1101000)


/**
 * @brief Configuration structure of the I2C ports.
 */

typedef struct {
    port p_scl;     /**< I2C clock line */
    port p_sda;     /**< I2C data line */
}I2C_ports;

/**
 * @brief Interface type to communicate with RTC Service.
 */

interface rtc_communication {

    /**
     * @brief Initialization of M41T62LC6F rtc device.
     *
     * @param resultat i2c_regop_res_t structure from i2c library to report back on whether the read/write operation of the i2c was a success or not.
     */

    void    init(i2c_regop_res_t result);

    /**
     * @brief Setter for Hours.
     *
     * @param data Hours data (00-23).
     */

    void    set_Hours(uint8_t data);

    /**
     * @brief Setter for Minutes.
     *
     * @param data Minutes data (00-59).
     */

    void    set_Minutes(uint8_t data);

    /**
     * @brief Setter for Seconds.
     *
     * @param data Seconds data (00-59).
     */

    void    set_Seconds(uint8_t data);

    /**
     * @brief Setter for Milli Seconds.
     *
     * @param data Milli Seconds data (00-99).
     */

    void    set_Milli_Seconds(uint8_t data);

    /**
     * @brief Setter for Day of the week.
     *
     * @param data Day of the week data (01-7).
     */

    void    set_Day_of_week(uint8_t data);

    /**
     * @brief Setter for Date.
     *
     * @param data Date data (01-31).
     */

    void    set_Date(uint8_t data);

    /**
     * @brief Setter for Year.
     *
     * @param data Year data (00-99).
     */

    void    set_Year(uint8_t data);

    /**
     * @brief Setter for Month.
     *
     * @param data Month data (01-12).
     */

    void    set_Month(uint8_t data);

    /**
     * @brief Setter for Century.
     *
     * @param data Century data (21-23).
     */

    void    set_Century(uint8_t data);

    /**
     * @brief Setter for SQWE bit.
     *
     * @param data SQWE bit value (0 or 1).
     */

    void    set_SQWE(uint8_t data);

    /**
     * @brief Setter for Square Wave output frequency.
     *
     * @param data integer value corresponding to frequency (1 to 15).
     */

    void    set_square_wave_frequency(uint8_t data);


    /**
     * @brief Getter for Hours.
     *
     * @param resultat i2c_regop_res_t structure from i2c library to report back on whether the read/write operation of the i2c was a success or not.
     *
     * @return value of Hours
     */

    unsigned get_Hours(i2c_regop_res_t result);

    /**
     * @brief Getter for Minutes.
     *
     * @param resultat i2c_regop_res_t structure from i2c library to report back on whether the read/write operation of the i2c was a success or not.
     *
     * @return value of Minutes
     */

    unsigned get_Minutes(i2c_regop_res_t result);

    /**
     * @brief Getter for Seconds.
     *
     * @param resultat i2c_regop_res_t structure from i2c library to report back on whether the read/write operation of the i2c was a success or not.
     *
     * @return value of Seconds
     */

    unsigned get_Seconds(i2c_regop_res_t result);

    /**
     * @brief Getter for Milli Seconds.
     *
     * @param resultat i2c_regop_res_t structure from i2c library to report back on whether the read/write operation of the i2c was a success or not.
     *
     * @return value of Milli Seconds
     */

    unsigned get_Milli_Seconds(i2c_regop_res_t result);

    /**
     * @brief Getter for Month.
     *
     * @param resultat i2c_regop_res_t structure from i2c library to report back on whether the read/write operation of the i2c was a success or not.
     *
     * @return value of Month
     */

    unsigned get_Month(i2c_regop_res_t result);

    /**
     * @brief Getter for Day of the week.
     *
     * @param resultat i2c_regop_res_t structure from i2c library to report back on whether the read/write operation of the i2c was a success or not.
     *
     * @return value of Day of the week.
     */

    unsigned get_Day_of_week(i2c_regop_res_t result);

    /**
     * @brief Getter for Date.
     *
     * @param resultat i2c_regop_res_t structure from i2c library to report back on whether the read/write operation of the i2c was a success or not.
     *
     * @return value of Date.
     */

    unsigned get_Date(i2c_regop_res_t result);

    /**
     * @brief Getter for Year.
     *
     * @param resultat i2c_regop_res_t structure from i2c library to report back on whether the read/write operation of the i2c was a success or not.
     *
     * @return value of year.
     */

    unsigned get_Year(i2c_regop_res_t result);

    /**
     * @brief Getter for Century.
     *
     * @param resultat i2c_regop_res_t structure from i2c library to report back on whether the read/write operation of the i2c was a success or not.
     *
     * @return value of Century.
     */

    unsigned get_Century(i2c_regop_res_t result);


    /**
     * @brief Getter for SQWE bit.
     *
     * @param resultat i2c_regop_res_t structure from i2c library to report back on whether the read/write operation of the i2c was a success or not.
     *
     * @return value of SQWE bit.
     */

    unsigned get_SQWE(i2c_regop_res_t result);

    /**
     * @brief Getter for integer value corresponding to square wave frequency.
     *
     * @param resultat i2c_regop_res_t structure from i2c library to report back on whether the read/write operation of the i2c was a success or not.
     *
     * @return value integer value corresponding to square wave frequency.
     */

    unsigned get_square_wave_frequency(i2c_regop_res_t result);
};

/**
 * @brief Write an 8-bit register on a slave device using i2c library.
 *
 * @param i2c_master_if communication interface with an I2C master component.
 * @param device_addr 7-bit address of the rtc slave device.
 * @param reg address of the register to write to.
 */

void RTC_write(client interface i2c_master_if i2c, uint8_t device_addr, uint8_t reg, uint8_t data);

/**
 * @brief Read an 8-bit register from a slave device using i2c library.
 *
 * @param i2c_master_if communication interface with an I2C master component.
 * @param device_addr 7-bit address of the rtc slave device.
 * @param reg address of the register to read from.
 * @param resultat i2c_regop_res_t structure from i2c library to report back on whether the read/write operation of the i2c was a success or not.
 *
 * @return the value of the register.
 */

uint8_t RTC_read(client interface i2c_master_if i2c, uint8_t device_addr, uint8_t reg, i2c_regop_res_t &result);

/**
 * @brief Service to set and get time/date from M41T62LC6F Real Time Clock device.
 *
 * @param rtc rtc_communication communication interface for the RTC_service.
 * @param i2c_master_if communication interface with an I2C master component.
 */

void rtc_service(server interface rtc_communication rtc, client interface i2c_master_if i2c);

#endif /* RTC_CONFIG_H_ */
