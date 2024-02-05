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
 * Interrupt service routines.
 * @author Thomas Reidemeister
 * @file interrupts.c
 */
#include <msp430.h>
#include <stdlib.h>
#include "hardware.h"

// PORT1_VECTOR
void __attribute__ ((interrupt(PORT1_VECTOR)))  PORT1_ISR(void)
{
  if(P1IFG & BIT3) {
    st25dv_field_flag = 1;
    P1IE &= ~BIT3;  // disable P1.3 interrupt
    P1IFG &= ~BIT3; // P1.3 IFG cleared
    __bic_SR_register_on_exit(LPM0_bits); // wake system up
  }
}

//  Echo back RXed character, confirm TX buffer is ready first
void __attribute__ ((interrupt(USCIAB0RX_VECTOR)))  USCI0RX_ISR(void)
{
  // UART0
  if(IFG2 & UCA0RXIE) {
    uart_last_in = UCA0RXBUF;                    // TX -> RXed character
  }
  if(IFG2 & UCB0RXIE) {
    RxByteCtr--;                              // Decrement RX byte counter
    if (RxByteCtr)
    {
      RxWord = (unsigned int)UCB0RXBUF << 8;  // Get received byte
      if (RxByteCtr == 1)                     // Only one byte left?
        UCB0CTL1 |= UCTXSTP;                  // Generate I2C stop condition
    }
    else
    {
      RxWord |= UCB0RXBUF;                    // Get final received byte,
                                              // Combine MSB and LSB
    }
  }
}

//  Echo back RXed character, confirm TX buffer is ready first
void __attribute__ ((interrupt(USCIAB0TX_VECTOR)))  USCI0TX_ISR(void)
{
  // UART0
  if(IFG2 & UCA0TXIE) {
    if(uart_last_out_ptr != NULL) {
      if(*uart_last_out_ptr != '\0') {
        UCA0TXBUF = *uart_last_out_ptr++;
      } else {
        uart_last_out_ptr = NULL;
        IE2 &= ~UCA0TXIE;                   // Disable interrupt
      }
    } else {
      IE2 &= ~UCA0TXIE;                     // Disable interrupt
    }
  }
}
