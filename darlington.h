#ifndef DARLINGTON_H
#define DARLINGTON_H
/**
 * @file darlington.h
 * @brief functions related to the Darlington array.
 */

/**
 * @brief Turn on the Darlington transistor for a certain pin
 * @param[in] p pin number, must be between 1 to 4.
 * @return
 * - 0, on success.
 * - 1, if the pin number is invalid.
 * - 2, if there is some kind of I2C error.
 */
int darlington_on(int p);

/**
 * @brief Turn off the Darlington transistor for a certain pin
 * @param[in] p pin number, must be between 1 to 4.
 * @return
 * - 0, on success.
 * - 1, if the pin number is invalid.
 * - 2, if there is some kind of I2C error.
 */
int darlington_off(int p);
#endif
