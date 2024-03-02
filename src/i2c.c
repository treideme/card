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
#include "i2c.h"
#include <msp430.h>
#include <stdlib.h>

uint8_t *i2c_tx_data = NULL;                     // Pointer to TX data
uint8_t *i2c_rx_data = NULL;                     // Pointer to RX data
uint8_t i2c_tx_count = 0;
uint8_t i2c_rx_count = 0;

void i2c_master_init(uint8_t slaveAddress) {
    //USCI Configuration
    UCB0CTL1 |= UCSWRST;                           // Enable SW reset
    UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC;          // I2C Master, synchronous mode
    UCB0CTL1 = UCSSEL_2 + UCSWRST;                 // Use SMCLK, keep SW reset

    //Set USCI Clock Speed
    UCB0BR0 = 12;                                  // fSCL = SMCLK/12 = ~100kHz
    UCB0BR1 = 0;

    //Set Slave Address and Resume operation
    UCB0I2CSA = slaveAddress;                      // Slave Address passed as parameter
    UCB0CTL1 &= ~UCSWRST;                          // Clear SW reset, resume operation
}


void i2c_write(uint8_t count, uint8_t *txd) {
    __disable_interrupt();

    //Interrupt management
    IE2 &= ~UCB0RXIE;                              // Disable RX interrupt
    IE2 |= UCB0TXIE;                               // Enable TX interrupt

    //Pointer to where data is stored to be sent
    i2c_tx_data = (uint8_t *) txd;                 // TX array start address
    i2c_tx_count = count;                          // Load TX byte counter

    //Send start condition
    UCB0CTL1 |= UCTR + UCTXSTT;                    // I2C TX, start condition

    __bis_SR_register(CPUOFF + GIE);               // Enter LPM0 w/ interrupts
    while (UCB0CTL1 & UCTXSTP) {}
}

void i2c_read(uint8_t count, uint8_t *rxd) {
    __disable_interrupt();

    //Interrupt management
    IE2 &= ~UCB0TXIE;                              // Disable TX interrupt
    UCB0CTL1 = UCSSEL_2 + UCSWRST;                 // Use SMCLK, keep SW reset
    UCB0CTL1 &= ~UCSWRST;                          // Clear SW reset, resume operation
    IE2 |= UCB0RXIE;                               // Enable RX interrupt

    //Pointer to where data will be stored
    i2c_rx_data = (uint8_t *)rxd;                  // Start of RX buffer
    i2c_rx_count = count;                          // Load RX byte counter

    //If only 1 byte will be read send stop signal as soon as it starts transmission
    if(i2c_rx_count == 1) {
        UCB0CTL1 |= UCTXSTT;                       // I2C start condition
        while (UCB0CTL1 & UCTXSTT) { }             // Start condition sent?
        UCB0CTL1 |= UCTXSTP;                       // I2C stop condition
    } else {
        UCB0CTL1 |= UCTXSTT;                       // I2C start condition
    }

    __enable_interrupt();
    __bis_SR_register(CPUOFF + GIE);               // Enter LPM0 w/ interrupts
    while (UCB0CTL1 & UCTXSTP) {}                  // Ensure stop condition got sent
}
