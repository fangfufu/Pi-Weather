#ifndef EXP_H
#define EXP_H

/**
 * @file lowlevel.h
 * @brief low level functions for the Raspberry Pi Weather Board
 */

#include <stdint.h>

/**
 * @brief Initialise the Weather Board
 * @return
 * - on success: 0
 * - on partial failure: the number of bytes sent to the expander
 * - on failure related to open/ioctl: -1
 */
int exp_open();

/**
 * @brief close down the Weather Board
 * @return 0, on success
 */
int exp_close();

int exp_write(const uint8_t *buf, int len);

int exp_read(uint8_t* buf, int len);
#endif
