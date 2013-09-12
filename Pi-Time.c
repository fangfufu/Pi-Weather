#include <stdio.h>

#include "time.h"

int main()
{
    WB_Time time;
    time.time.second = 1;
    time.time.minute = 2;
    time.time.hour = 3;
    time.time.week_day = 4;
    time.time.month_day = 5;
    time.time.month = 6;
    time.time.year = 7;
    for (int i = 0 ; i < 7 ; i++) {
        printf("%d\n", time.data[i]);
    }
    printf("%d\n", time.time.second);
    printf("%d\n", time.time.minute);
    printf("%d\n", time.time.hour);
    printf("%d\n", time.time.week_day);
    printf("%d\n", time.time.month_day);
    printf("%d\n", time.time.month);
    printf("%d\n", time.time.year);
}