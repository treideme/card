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

uint8_t *i2c_tx_data = NULL;                     // Pointer to TX data
uint8_t *i2c_rx_data = NULL;                     // Pointer to RX data
uint8_t i2c_tx_count = 0;
uint8_t i2c_rx_count = 0;

void i2c_master_init(void) {
    //USCI Configuration
    UCB0CTL1 = UCSWRST;                            // Enable SW reset
    UCB0CTL0 = UCMST | UCMODE_3 | UCSYNC;          // I2C Master, synchronous mode

    //Set USCI Clock Speed
    UCB0BR0 = 10;                                  // fSCL = SMCLK/10 = ~100kHz
    UCB0BR1 = 0;

    UCB0CTL1 = UCSSEL_2;                           // Use SMCLK, release reset
}

static int _check_ack(void) {
  int err = 0;

  /* Check for ACK */
  if (UCB0STAT & UCNACKIFG) {
    /* Stop the I2C transmission */
    UCB0CTL1 |= UCTXSTP;

    /* Clear the interrupt flag */
    UCB0STAT &= ~UCNACKIFG;

    /* Set the error code */
    err = -1;
  }

  return err;
}

static int _i2c_write(const uint8_t *tx_data, size_t tx_len) {
  int err;

  /* Send the start condition */
  UCB0CTL1 |= UCTR | UCTXSTT;

  /* Wait for the start condition to be sent and ready to transmit interrupt */
  while ((UCB0CTL1 & UCTXSTT) && ((IFG2 & UCB0TXIFG) == 0)) {}

  /* Check for ACK */
  err = _check_ack();

  /* If no error and bytes left to send, transmit the data */
  while ((err == 0) && (tx_len > 0)) {
    UCB0TXBUF = *tx_data;
    while ((IFG2 & UCB0TXIFG) == 0) {
      err = _check_ack();
      if (err < 0) {
        break;
      }
    }

    tx_data++;
    tx_len--;
  }

  return err;
}

int _i2c_read(uint8_t *rx_buf, size_t rx_len) {
  int err;

  /* Send the start and wait */
  UCB0CTL1 &= ~UCTR;
  UCB0CTL1 |= UCTXSTT;

  /* Wait for the start condition to be sent */
  while (UCB0CTL1 & UCTXSTT) {}

  /*
   * If there is only one byte to receive, then set the stop
   * bit as soon as start condition has been sent
   */
  if (rx_len == 1) {
    UCB0CTL1 |= UCTXSTP;
  }

  /* Check for ACK */
  err = _check_ack();

  /* If no error and bytes left to receive, receive the data */
  while ((err == 0) && (rx_len > 0)) {
    /* Wait for the data */
    while ((IFG2 & UCB0RXIFG) == 0);

    *rx_buf = UCB0RXBUF;
    rx_buf++;
    rx_len--;

    /*
     * If there is only one byte left to receive
     * send the stop condition
     */
    if (rx_len == 1) {
      UCB0CTL1 |= UCTXSTP;
    }
  }

  return err;
}

int i2c_transfer(uint8_t addr, const uint8_t *tx_data, size_t tx_len, uint8_t *rx_buf, size_t rx_len) {
  int err = 0;

  /* Set the slave device address */
  UCB0I2CSA = addr;

  /* Transmit data is there is any */
  if (tx_len) {
    err = _i2c_write(tx_data, tx_len);
  }

  /* Receive data is there is any */
  if ((err == 0) && (rx_len > 0)) {
    err = _i2c_read(rx_buf, rx_len);
  } else {
    /* No bytes to receive send the stop condition */
    UCB0CTL1 |= UCTXSTP;
  }

  return err;
}

