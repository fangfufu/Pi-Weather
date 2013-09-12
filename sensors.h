#ifndef SENSORS_H
#define SENSORS_H
/**
 * @file sensors.h
 * @brief functions related to the onboard sensors.
 */

/**
 * @brief read the temperature from the onboard microcontroller.
 * @return temperature in degree Celcius
 */
int read_board_temp();

/**
 * @brief read humidity
 * @return humidity in %
 */
int read_humidity();

/**
 *  @brief read DS18B20 sensor temperature
 *  @param[in] sensor sensor number, must be 1 or 2
 *  @return temperature in degree Celcius
 */
float read_sensor_temp(int sensor);

/**
 * @brief read board pressure
 * @return board pressure in kPa
 * @warning overclocking core_freq will result in erroneous reading.
 */
float read_pressure();

#endif