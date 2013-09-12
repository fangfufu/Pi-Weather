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

/**
 * @brief Write to the weather station board.
 * @return the same as the write call
 */
int exp_write(const uint8_t *buf, int len);

/**
 * @brief read from the weather station board
 * @return the same as the read call
 */
int exp_read(uint8_t* buf, int len);

/**
 * @brief write a byte to the expansion board
 */
int exp_write_byte(const uint8_t byte);

/**
 * @brief read expansion board firmware version number
 */
int read_board_version();

#endif
