#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "lowlevel.h"
#include "rtc.h"

#define GET_TIME_DATE   0x2C
#define SET_TIME_DATE   0x2F

struct tm* rtc_get_time()
{
    uint8_t buf[7];
    static struct tm t;
    int r = exp_write_byte(GET_TIME_DATE);
    r += exp_read(buf, 7);
    if (r != 8) {
        fprintf(stderr, "get_time_date error: I/O error.\n");
        return NULL;
    }

    t.tm_sec  = buf[0];
    t.tm_min  = buf[1];
    t.tm_hour = buf[2];
    /* The RTC's week is between 1 - 7, for struct tm, it is 0 - 6 */
    t.tm_wday = buf[3] - 1;
    t.tm_mday = buf[4];
    t.tm_mon  = buf[5];
    /* The RTC only stores year between 0 to 99 */
    t.tm_year = buf[6] + 100;

    return &t;
}

int rtc_set_time(struct tm* t)
{
    uint8_t buf[8];
    if (t == NULL) {
        time_t tt;
        tt = time(NULL);
        t = gmtime(&tt);
    }
    buf[0] = SET_TIME_DATE;
    buf[1] = t -> tm_sec;
    buf[2] = t -> tm_min;
    buf[3] = t -> tm_hour;
    /* The RTC's week is between 1 - 7, for struct tm, it is 0 - 6 */
    buf[4] = t -> tm_wday + 1;
    buf[5] = t -> tm_mday;
    buf[6] = t -> tm_mon;
    /* The RTC only stores year between 0 to 99 */
    buf[7] = t -> tm_year - 100;
    int r = exp_write(buf, 8);
    if (r != 8) {
        fprintf(stderr, "set_time_date error: %d\n", r);
        return r;
    }
    return 0;
}

int rtc_systohc()
{
    if (!rtc_set_time(NULL)) {
        return 0;
    }
    return -1;
}

int rtc_hctosys()
{
    struct tm* t = rtc_get_time();
    time_t s = timegm(t);
    int r = stime(&s);
    if (r != 0) {
        fprintf(stderr, "rtc_hctosys error: %s\n", strerror(errno));
    }
    return r;
}
