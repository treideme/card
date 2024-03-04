/*
 * Copyright 2024 Thomas Reidemeister
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/**
 * Utility functions for I2C transfer.
 * @file i2c.h
 * @author Thomas Reidemeister
 */
#ifndef I2C_H
#define I2C_H

#include <stdint.h>
#include <stddef.h>

/**
 * Initialize I2C master.
 */
void i2c_master_init(void);

/**
 * Deinitialize I2C.
 */
void i2c_deinit(void);

/**
 * Perform I2C transfer.
 * @param addr 7-bit address to use for client
 * @param tx_data TX data to send
 * @param tx_len Length of tx data to send.
 * @param rx_buf RX buffer to store received data.
 * @param rx_len Length of rx buffer.
 * @return 0 on success, nz on error.
 */
int i2c_transfer(uint8_t addr, const uint8_t *tx_data, size_t tx_len, uint8_t *rx_buf, size_t rx_len);

/**
 * I2C TX interrupt service routine for transmits.
 * @return 1 If system should wake up.
 */
int i2c_tx_isr(void);


#endif // I2C_H
