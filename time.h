#ifndef TIME_H
#define TIME_H

#include <stdint.h>
/**
 * @file time.h
 * @brief RTC related functions
 */

/**
 * @brief Structure for 
 */
typedef union {
    uint8_t data[7];
    struct {
        unsigned int second : 8;
        unsigned int minute : 8;
        unsigned int hour : 8;
        unsigned int week_day : 8;
        unsigned int month_day : 8;
        unsigned int month;
        unsigned int year : 8;
    } time;
} WB_Time;
#endif