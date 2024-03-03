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
 * UART interrupts and examples.
 * @author Thomas Reidemeister
 * @file uart.c
 */
#include <msp430.h>
#include <stdlib.h>

volatile char* volatile uart_last_out_ptr = NULL;
char uart_last_in;

void uart_init() {
  // Initialise UART0
  UCA0CTL1 |= UCSSEL_2;        // SMCLK
  UCA0BR0 = 104;               // 1MHz 9600
  UCA0BR1 = 0;                 // 1MHz 9600
  UCA0MCTL = UCBRS0;           // Modulation UCBRSx = 1
  UCA0CTL1 &= ~UCSWRST;        // **Initialize USCI state machine**
  IE2 |= UCA0RXIE;             // Enable USCI_A0 RX interrupt
}

void uart_send(const char*s) {
  while(uart_last_out_ptr != NULL) {  }
  __disable_interrupt();
  uart_last_out_ptr = (volatile char*)s;

  // Enable interrupt
  IE2 |=UCA0TXIE;
  __enable_interrupt();
}


