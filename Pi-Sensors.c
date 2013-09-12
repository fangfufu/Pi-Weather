#include <stdio.h>

#include "lowlevel.h"
#include "sensors.h"

int main()
{
    exp_open();
    printf("Board Version: %d\n", read_board_version());
    printf("Board Temperature: %d C\n", read_board_temp());
    printf("Humidity: %d %%\n", read_humidity());
    printf("Room Temperature: %.1f C\n", read_sensor_temp(1));
    printf("Outdoor Temperature: %.1f C\n", read_sensor_temp(2));
    printf("Board Pressure: %.1f\n", read_pressure());
    exp_close();
}