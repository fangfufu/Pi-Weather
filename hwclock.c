/**
 * @file hwclock.c
 * @brief A hwclock replacement
 * @details This program is designed to replace hwclock in util-linux.
 * In order to use this program to synchronise time at boot and shutdown,
 * please replace all instances of /sbin/hwclock by /usr/local/bin/hwclock in
 * /etc/init.d/hwclock.sh.
 */
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "lowlevel.h"
#include "rtc.h"

static void print_help()
{
    puts("Usage:");
    puts(" hwclock [function]\n");
    puts("Functions:");
    puts(" -h, --help\t\tshow this help text and exit");
    puts(" -r, --show\t\tread hardware clock and print result");
    puts(" -s, --hctosys\t\tset the system time from the hardware clock");
    puts(" -w, --systohc\t\tset the hardware clock from the current system time\n");
    puts("Other features of hwclock in util-linux are not implemented.");
    exit(0);
}

int main(int argc, char* const* argv)
{
    /* variables for parsing options */
    int opt = 0;
    int opts_index = 0;
    char *short_opts = "hrswVufD";
    struct option long_opts[] = {
        {"help", no_argument, NULL, 'h'},
        {"show", no_argument, NULL, 'r'},
        {"hctosys", no_argument, NULL, 's'},
        {"systohc", no_argument, NULL, 'w'},
        /* unimplemented options for compatibility reason */
        {"set", optional_argument, NULL, 'z'},
        {"systz", optional_argument, NULL, 'z'},
        {"adjust", optional_argument, NULL, 'z'},
        {"getepoch", optional_argument, NULL, 'z'},
        {"setepoch", optional_argument, NULL, 'z'},
        {"predict", optional_argument, NULL, 'z'},
        {"version", optional_argument, NULL, 'z'},
        {"utc", optional_argument, NULL, 'z'},
        {"localtime", optional_argument, NULL, 'z'},
        {"rtc", optional_argument, NULL, 'z'},
        {"directisa", optional_argument, NULL, 'z'},
        {"badyear", optional_argument, NULL, 'z'},
        {"date", optional_argument, NULL, 'z'},
        {"epoch", optional_argument, NULL, 'z'},
        {"noadjfile", optional_argument, NULL, 'z'},
        {"adjfile", optional_argument, NULL, 'z'},
        {"test", optional_argument, NULL, 'z'},
        {"debug", optional_argument, NULL, 'z'},
        {0, 0, 0, 0}
    };

    /* variables for flags */
    enum MODE {
        SHOW,
        HCTOSYS,
        SYSTOHC
    } ;
    enum MODE mode;
    mode = SHOW;
    int flag_count = 0;

    while ((opt =
        getopt_long(argc, argv, short_opts, long_opts,
                    &opts_index)) != -1) {
        switch (opt) {
            case 'h':
                print_help();
                break;
            case 'r':
                mode = SHOW;
                flag_count++;
                break;
            case 's':
                mode = HCTOSYS;
                flag_count++;
                break;
            case 'w':
                mode = SYSTOHC;
                flag_count++;
                break;
            case 'V':
                puts("hwclock from Pi-Weather 1.00");
                exit(0);
                break;
            case '?':
                puts("");
                print_help();
                break;
        }
    };

    if (flag_count > 1) {
        puts("hwclock: You have specified multiple functions.");
        puts("You can only perform one function at a time.");
        exit(0);
    }

    int r = exp_open();
    if (mode == HCTOSYS) {
        r += rtc_hctosys();
    } else if (mode == SYSTOHC) {
        r += rtc_systohc();
    } else {
        time_t tt;
        time(&tt);
        struct tm* t = rtc_get_time();
        char s[40];
        strftime(s, sizeof(s), "%a %d %b %Y %T %Z", t);

        /* This part is for aesthetic reason only, so it has the same
         format as the real hwclock */
        float a = 1/((float)rand_r((unsigned int*)&tt)/1000000000);
        float b = a - (int)a;
        if (a > 1) {
            b *= -1;
        }
        printf("%s  %f seconds\n", s, b);
    }
    r += exp_close();
    return r;
}
