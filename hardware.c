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
  WDTCTL = WDTPW | WDTHOLD;       // stop watchdog timer
  // Configure clock to 1MHz
  DCOCTL  = 0;           // Select lowest DCOx and MODx setting
  BCSCTL1 = CALBC1_1MHZ; // Set DCO
  DCOCTL  = CALDCO_1MHZ;
  // Clock config
  BCSCTL1 = XT2OFF | DIVA1 | DIVA0 | 0b111; // turn XT2 off, and divide ACLK by 8, RSEL ~ 1MHz
  BCSCTL3 = LFXT1S1;  // Use 12KHz VLOCLK as ACLK

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

  // Initialise I2c
  UCB0CTL1 |= UCSWRST;                           // Enable SW reset
  UCB0CTL0 = UCMST | UCMODE0 | UCMODE1 | UCSYNC; // Enable I2C master
  UCB0CTL1 = UCSSEL1 | UCTXSTT | UCSWRST;        // SMCLK as source, generate start condition
  UCB0BR0 = 12;                                  // fSCL = SMCLK/12 = ~100kHz
  UCB0BR1 = 0;

  UCB0I2CSA = 0x2D;

  // Configure timer to use 12KHz crystal
}

void delay_ms(int ms) {
    volatile unsigned int i;
    for(i=ms; i>0; i--) {
        for(int j=0; j < 200; j++); // delay
    }
}
