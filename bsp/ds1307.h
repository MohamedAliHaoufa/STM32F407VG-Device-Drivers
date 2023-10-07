/**
 * @file ds1307.h
 * @author Mohamed Ali Haoufa
 * @brief This file contains definitions and function prototypes for interfacing with a DS1307 Real-Time Clock (RTC) module.
 * @version 0.1
 * @date 2023-10-07
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef DS1307_H_
#define DS1307_H_

#include "../drivers/Inc/stm32f407xx.h"

/**
 * @defgroup DS1307 DS1307 RTC Driver
 * @brief DS1307 Real-Time Clock (RTC) driver for STM32F4xx MCUs.
 * @{
 */


/**
 * @defgroup DS1307_MACROS DS1307 Macros
 * @brief Macros for DS1307 configuration and settings.
 * @{
 */

/**
 * @defgroup DS1307_CONFIGURABLE_ITEMS DS1307 Configurable Items
 * @brief Macros for DS1307 configuration settings.
 * @{
 */
#define DS1307_I2C              I2C1
#define DS1307_I2C_GPIO_PORT    GPIOB
#define DS1307_I2C_SDA_PIN      GPIO_PIN_NO_7
#define DS1307_I2C_SCL_PIN      GPIO_PIN_NO_6
#define DS1307_I2C_SPEED        I2C_SC_SPEED_SM
#define DS1307_I2C_PUPD         GPIO_PIN_PU // with internal pull-ups
#define DS1307_I2C_ADDRESS      0x68 // 1101000
/** @} */

/**
 * @defgroup DS1307_REGISTER_ADDRESSES Register Addresses
 * @brief Macros for DS1307 register addresses as per DS1307's Data-sheet.
 * @{
 */
#define DS1307_ADDR_SEC         0x00
#define DS1307_ADDR_MIN         0x01
#define DS1307_ADDR_HRS         0x02
#define DS1307_ADDR_DAY         0x03
#define DS1307_ADDR_DATE        0x04
#define DS1307_ADDR_MONTH       0x05
#define DS1307_ADDR_YEAR        0x06
/** @} */

/**
 * @defgroup DS1307_TIME_FORMAT Time Formats
 * @brief Macros for DS1307 time format settings.
 * @{
 */
#define TIME_FORMAT_12HRS_AM    0
#define TIME_FORMAT_12HRS_PM    1
#define TIME_FORMAT_24HRS       2
/** @} */

/**
 * @defgroup DS1307_DAYS_OF_WEEK Days of the Week
 * @brief Macros for DS1307 day of the week settings.
 * @{
 */
#define SUNDAY                  1
#define MONDAY                  2
#define TUESDAY                 3
#define WEDNESDAY               4
#define THURSDAY                5
#define FRIDAY                  6
#define SATURDAY                7
/** @} */

/** @} */ // End of DS1307_MACROS group

/**
 * @brief Data structure for holding date information.
 */
typedef struct {
    uint8_t date;   /*!< Day of the month (1-31). */
    uint8_t month;  /*!< Month (1-12). */
    uint8_t year;   /*!< Year (0-99). */
    uint8_t day;    /*!< Day of the week (1-7, where 1 is Sunday). */
} RTC_date_t;

/**
 * @brief Data structure for holding time information.
 */
typedef struct {
    uint8_t seconds;       /*!< Seconds (0-59). */
    uint8_t minutes;       /*!< Minutes (0-59). */
    uint8_t hours;         /*!< Hours (0-23). */
    uint8_t time_format;   /*!< Time format (12HRS_AM, 12HRS_PM, 24HRS). */
} RTC_time_t;

/**
 * @defgroup DS1307_APIS DS1307 APIs
 * @brief APIs supported by the DS1307 driver.
 * @{
 */

/**
 * @brief Initialize the DS1307 module.
 * @return Status:
 *  - 0: Success
 *  - 1: Error
 */
uint8_t ds1307_init();

/**
 * @brief Set the current time on the DS1307 RTC module.
 * @param[in] Pointer to a structure containing the time to set.
 */
void ds1307_set_current_time(RTC_time_t *);

/**
 * @brief Get the current time from the DS1307 RTC module.
 * @param[out] Pointer to a structure to store the retrieved time.
 */
void ds1307_get_current_time(RTC_time_t *);

/**
 * @brief Set the current date on the DS1307 RTC module.
 * @param[in] Pointer to a structure containing the date to set.
 */
void ds1307_set_current_date(RTC_date_t *);

/**
 * @brief Get the current date from the DS1307 RTC module.
 * @param[out] Pointer to a structure to store the retrieved date.
 */
void ds1307_get_current_date(RTC_date_t *);

/** @} */ // End of DS1307_APIS group

#endif /* DS1307_H_ */

/** @} */ // End of DS1307 group
