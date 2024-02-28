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

extern uint8_t *i2c_tx_data;                     // Pointer to TX data
extern uint8_t *i2c_rx_data;                     // Pointer to RX data
extern uint8_t i2c_tx_count;                     // Transmit bytes left
extern uint8_t i2c_rx_count;

//static uint8_t TxByteCtr;
//static uint8_t RxByteCtr;

void i2c_master_init(uint8_t slaveAddress);
void i2c_write(uint8_t ByteCtr, uint8_t *TxData);
void i2c_read(uint8_t ByteCtr, volatile uint8_t *RxData);



#endif // I2C_H
