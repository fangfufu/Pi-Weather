#ifndef TIME_H
#define TIME_H

#include <stdint.h>
#include <time.h>
/**
 * @file rtc.h
 * @brief RTC related functions
 */

/**
 * @brief get the time from the RTC
 * @return pointer to a struct tm on success, null on failure
 */
struct tm* rtc_get_time();

/**
 * @brief set the time to the RTC
 * @param[in] *t pointer to a WB_Time variable containing the time to set.
 * if *t is null, the RTC's time is set to current UTC time.
 * @return
 * - on success: 0,
 * - on error: the number of bytes sent through the I2C bus.
 */
int rtc_set_time(struct tm* t);

/**
 * @brief set time RTC time to system time
 * @return 0 on success, -1 on error
 */
int rtc_systohc();

/**
 * @brief set system time to RTC time
 * @return 0 on success, -1 on error
 */
int rtc_hctosys();
#endif
