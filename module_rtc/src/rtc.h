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
 * @brief RTC Square Wave Frequency types
 */
typedef enum
{
    RTC_SQW_FREQ_NONE = 0x00,           /**< RTC Square Wave Frequency None */
    RTC_SQW_FREQ_32KHZ = 0x10,          /**< RTC Square Wave Frequency 32 KHZ */
    RTC_SQW_FREQ_8KHZ = 0x20,           /**< RTC Square Wave Frequency 8 KHZ */
    RTC_SQW_FREQ_4KHZ = 0x30,           /**< RTC Square Wave Frequency 4 KHZ */
    RTC_SQW_FREQ_2KHZ = 0x40,           /**< RTC Square Wave Frequency 2 KHZ */
    RTC_SQW_FREQ_1KHZ = 0x50,           /**< RTC Square Wave Frequency 1 KHZ */
    RTC_SQW_FREQ_512HZ = 0x60,          /**< RTC Square Wave Frequency 512 HZ */
    RTC_SQW_FREQ_256HZ = 0x70,          /**< RTC Square Wave Frequency 256 HZ */
    RTC_SQW_FREQ_128HZ = 0x80,          /**< RTC Square Wave Frequency 128 HZ */
    RTC_SQW_FREQ_64HZ = 0x90,           /**< RTC Square Wave Frequency 64 HZ */
    RTC_SQW_FREQ_32HZ = 0xA0,           /**< RTC Square Wave Frequency 32 HZ */
    RTC_SQW_FREQ_16HZ = 0xB0,           /**< RTC Square Wave Frequency 16 HZ */
    RTC_SQW_FREQ_8HZ = 0xC0,            /**< RTC Square Wave Frequency 8 HZ */
    RTC_SQW_FREQ_4HZ = 0xD0,            /**< RTC Square Wave Frequency 4 HZ */
    RTC_SQW_FREQ_2HZ = 0xE0,            /**< RTC Square Wave Frequency 2 HZ */
    RTC_SQW_FREQ_1HZ = 0xF0             /**< RTC Square Wave Frequency 1 HZ */
} RTC_SQW_FREQ;

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


void    rtc_init(client interface i2c_master_if i2c, i2c_regop_res_t result);

/**
     * @brief Setter for Hours.
     *
     * @param data Hours data (00-23).
     */

void    rtc_set_Hours(client interface i2c_master_if i2c, uint8_t data);

    /**
     * @brief Setter for Minutes.
     *
     * @param data Minutes data (00-59).
     */

void    rtc_set_Minutes(client interface i2c_master_if i2c, uint8_t data);

    /**
     * @brief Setter for Seconds.
     *
     * @param data Seconds data (00-59).
     */

void    rtc_set_Seconds(client interface i2c_master_if i2c, uint8_t data);

    /**
     * @brief Setter for Milli Seconds.
     *
     * @param data Milli Seconds data (00-99).
     */

void    rtc_set_Milli_Seconds(client interface i2c_master_if i2c, uint8_t data);

    /**
     * @brief Setter for Day of the week.
     *
     * @param data Day of the week data (01-7).
     */

void    rtc_set_Day_of_week(client interface i2c_master_if i2c, uint8_t data);

    /**
     * @brief Setter for Date.
     *
     * @param data Date data (01-31).
     */

void    rtc_set_Date(client interface i2c_master_if i2c, uint8_t data);

    /**
     * @brief Setter for Year.
     *
     * @param data Year data (00-99).
     */

void    rtc_set_Year(client interface i2c_master_if i2c, uint8_t data);

    /**
     * @brief Setter for Month.
     *
     * @param data Month data (01-12).
     */

uint8_t   rtc_set_Month(uint8_t data);

    /**
     * @brief Setter for Century.
     *
     * @param data Century data (21-23).
     */

void    rtc_set_Century(client interface i2c_master_if i2c, uint8_t data);

    /**
     * @brief Setter for SQWE bit.
     *
     * @param data SQWE bit value (0 or 1).
     */

void    rtc_set_SQWE(client interface i2c_master_if i2c, uint8_t data);

    /**
     * @brief Setter for Square Wave output frequency.
     *
     * @param data variable of type RTC_SQW_FREQ.
     */

void    rtc_set_SQW_Freq(client interface i2c_master_if i2c, RTC_SQW_FREQ data);


    /**
     * @brief Getter for Hours.
     *
     * @param resultat i2c_regop_res_t structure from i2c library to report back on whether the read/write operation of the i2c was a success or not.
     *
     * @return value of Hours
     */

unsigned get_Hours(client interface i2c_master_if i2c, i2c_regop_res_t result);

    /**
     * @brief Getter for Minutes.
     *
     * @param resultat i2c_regop_res_t structure from i2c library to report back on whether the read/write operation of the i2c was a success or not.
     *
     * @return value of Minutes
     */

unsigned get_Minutes(client interface i2c_master_if i2c, i2c_regop_res_t result);

    /**
     * @brief Getter for Seconds.
     *
     * @param resultat i2c_regop_res_t structure from i2c library to report back on whether the read/write operation of the i2c was a success or not.
     *
     * @return value of Seconds
     */

unsigned get_Seconds(client interface i2c_master_if i2c, i2c_regop_res_t result);

    /**
     * @brief Getter for Milli Seconds.
     *
     * @param resultat i2c_regop_res_t structure from i2c library to report back on whether the read/write operation of the i2c was a success or not.
     *
     * @return value of Milli Seconds
     */

unsigned get_Milli_Seconds(client interface i2c_master_if i2c, i2c_regop_res_t result);

    /**
     * @brief Getter for Month.
     *
     * @param resultat i2c_regop_res_t structure from i2c library to report back on whether the read/write operation of the i2c was a success or not.
     *
     * @return value of Month
     */

unsigned get_Month(client interface i2c_master_if i2c, i2c_regop_res_t result);

    /**
     * @brief Getter for Day of the week.
     *
     * @param resultat i2c_regop_res_t structure from i2c library to report back on whether the read/write operation of the i2c was a success or not.
     *
     * @return value of Day of the week.
     */

unsigned get_Day_of_week(client interface i2c_master_if i2c, i2c_regop_res_t result);

    /**
     * @brief Getter for Date.
     *
     * @param resultat i2c_regop_res_t structure from i2c library to report back on whether the read/write operation of the i2c was a success or not.
     *
     * @return value of Date.
     */

unsigned get_Date(client interface i2c_master_if i2c, i2c_regop_res_t result);

    /**
     * @brief Getter for Year.
     *
     * @param resultat i2c_regop_res_t structure from i2c library to report back on whether the read/write operation of the i2c was a success or not.
     *
     * @return value of year.
     */

unsigned get_Year(client interface i2c_master_if i2c, i2c_regop_res_t result);

    /**
     * @brief Getter for Century.
     *
     * @param resultat i2c_regop_res_t structure from i2c library to report back on whether the read/write operation of the i2c was a success or not.
     *
     * @return value of Century.
     */

unsigned get_Century(client interface i2c_master_if i2c, i2c_regop_res_t result);


    /**
     * @brief Getter for SQWE bit.
     *
     * @param resultat i2c_regop_res_t structure from i2c library to report back on whether the read/write operation of the i2c was a success or not.
     *
     * @return value of SQWE bit.
     */

unsigned get_SQWE(client interface i2c_master_if i2c, i2c_regop_res_t result);

    /**
     * @brief Getter for square wave frequency value.
     *
     * @param resultat i2c_regop_res_t structure from i2c library to report back on whether the read/write operation of the i2c was a success or not.
     *
     * @return value of type RTC_SQW_FREQ.
     */

RTC_SQW_FREQ get_SQW_Freq(client interface i2c_master_if i2c, i2c_regop_res_t result);

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


#endif /* RTC_CONFIG_H_ */
