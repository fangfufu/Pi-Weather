/**
 * @file WB-Sensor.c
 * @brief a program to read the onboard sensors.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lowlevel.h"
#include "sensors.h"

static void print_help()
{
    puts("Usage: WB-Sensor [FORMAT]");
    puts("   or: WB-Sensor [function]");
    puts("Display the sensor data from Raspberry Pi Weather Station Board.");
    puts("");
    puts("FORMAT controls the output. Interpreted sequences are:");
    puts("");
    puts("  \\n\t\tnew line");
    puts("  \\t\t\thorizontal tab");
    puts("");
    puts("  %v\t\tboard version");
    puts("  %h\t\tboard humidity, in percentage");
    puts("  %p\t\tboard atmospheric pressure, in kPa");
    puts("  %b\t\tboard temperature, in degree Celcius");
    puts("  %r\t\troom temperature, in degree Celcius");
    puts("  %o\t\toutdoor temperature, in degree Celcius");
    puts("");
    puts("Functions:");
    puts("  -h, --help\t\tshow this help text and exit");
    puts("  -s, --summary\t\tshow a summary of sensor data");
    puts("");
    exit(0);
}

static int print_summary()
{
    int r = exp_open();
    r += printf("Board Version:\t\t%d\n", read_board_version());
    r += printf("Board Pressure:\t\t%.1f kPa\n", read_pressure());
    r += printf("Board Humidity:\t\t%d %%\n", read_humidity());
    r += printf("Board Temperature:\t%d C\n", read_board_temp());
    r += printf("Room Temperature:\t%.1f C\n", read_sensor_temp(1));
    r += printf("Outdoor Temperature:\t%.1f C\n", read_sensor_temp(2));
    r += exp_close();
    return r;
}

int main(int argc, char *argv[])
{
    if (argc == 1) {
        print_help();
    } else if ( (!strcmp(argv[1], "--help")) | (!strcmp(argv[1], "-h")) ) {
        print_help();
    } else if ( (!strcmp(argv[1], "--summary")) | (!strcmp(argv[1], "-s")) ) {
        return print_summary();
    }

    char *p;
    int r = exp_open();
    for (p = argv[1]; *p != '\0'; p++) {
        if (*p == '\\') {
            switch (*++p) {
                case 'n':
                    putchar('\n');
                    break;
                case 't':
                    putchar('\t');
                    break;
                default:
                    putchar('\\');
                    putchar(*p);
                    break;
            }
        } else if (*p == '%') {
            switch (*++p) {
                case 'v':
                    printf("%d", read_board_version());
                    break;
                case 'h':
                    printf("%d", read_humidity());
                    break;
                case 'p':
                    printf("%.1f", read_pressure());
                    break;
                case 'b':
                    printf("%d", read_board_temp());
                    break;
                case 'r':
                    printf("%.1f", read_sensor_temp(1));
                    break;
                case 'o':
                    printf("%.1f", read_sensor_temp(2));
                    break;
                default:
                    putchar('%');
                    putchar(*p);
                    break;
            }
        } else {
            putchar(*p);
        }
    }
    r += exp_close();
    return r;
}
