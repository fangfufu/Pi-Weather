#include <stdio.h>
#include "lowlevel.h"

#define BOARD_TEMP              0x42
#define HUMIDITY                0x43
#define SENSOR_TEMP_1           0x45
#define SENSOR_TEMP_2           0x46
#define PRESSURE                0x47

int read_board_temp()
{
    uint8_t temp;
    int r = exp_write_byte(BOARD_TEMP);
    r += exp_read(&temp, 1);
    if (r != 2) {
        fprintf(stderr, "read_board_temp error: %d\n", r);
    }
    return temp;
}

int read_humidity()
{
    uint8_t humidity;
    int r = exp_write_byte(HUMIDITY);
    r += exp_read(&humidity, 1);
    if (r != 2) {
        fprintf(stderr, "read_humidity error: %d\n", r);
    }
    return humidity;
}

float read_sensor_temp(int sensor)
{
    int r;
    if (sensor == 1) {
        r = exp_write_byte(SENSOR_TEMP_1);
    } else if (sensor == 2) {
        r = exp_write_byte(SENSOR_TEMP_2);
    } else {
        fprintf(stderr, "read_sensor_temp error: invalid sensor\n");
        return 0;
    }
    uint8_t buf[2];
    r += exp_read(buf, 2);
    if (r != 3) {
        fprintf(stderr, "read_sensor_temp error: %d", r);
    }
    int16_t* result = (int16_t*) buf;
    return (float) *result / 10;
}

float read_pressure()
{
    uint8_t buf[2];
    int r = exp_write_byte(PRESSURE);
    r += exp_read(buf, 2);
    if (r != 3) {
        fprintf(stderr, "read_sensor_temp error: %d", r);
    }
    uint16_t* result = (uint16_t*) buf;
    return (float) *result / 10;
}