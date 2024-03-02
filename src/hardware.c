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
 * Hardware and pin configuration for device
 * @file hardware.c
 * @author Thomas Reidemeister
 */
#include "hardware.h"

void hardware_init() {
  WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
  // Configure clock to 1MHz
  DCOCTL  = 0;                // Select lowest DCOx and MODx setting
  BCSCTL1 = CALBC1_1MHZ;      // Set DCO
  DCOCTL  = CALDCO_1MHZ;

  // Pin configurations
  P1DIR |= BIT0;

  // Make P1.3 interrupt source
  P1DIR &= ~BIT3; // Enable P1.3 in
  P1REN |= BIT3;  // Enable P1.3 pull-up
  P1OUT |= BIT3;  // Enable P1.3 pull-up

  P1IES |= BIT3;  // await falling interrupt
  P1IE  |= BIT3;  // enable P1.3 interrupt


  P1SEL = BIT1 + BIT2;    // P1.1 = RXD, P1.2=TXD
  P1SEL2 = BIT1 + BIT2;   // P1.1 = RXD, P1.2=TXD

  uart_init();

  P1SEL |= BIT6 + BIT7; // Assign I2C pins to USCI_B0
  P1SEL2|= BIT6 + BIT7; // Assign I2C pins to USCI_B0

  i2c_master_init(0x2D);
}

void delay_ms(int ms) {
    volatile unsigned int i, j;
    for( i = ms; i > 0; i--) {
        for( j = 0; j < 200; j++) {} // delay
    }
}
