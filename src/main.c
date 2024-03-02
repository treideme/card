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
 * Main firmware entry point.
 * @author Thomas Reidemeister
 * @file main.c
 */
#include <stdlib.h>
#include <hardware.h>
#include <msp430.h>
#include "uart.h"
#include "i2c.h"

//static int field_seen = 0;

int main(void) {
  hardware_init();

  uint16_t c = 0;
  char tmp[20];

  uart_send("Hello World!\r\n");
  i2c_master_init(0x2D);
  i2c_read(0x02, (uint8_t*)&c);
  itoa(c, tmp, 10);
  tmp[19] = 0;
  uart_send(tmp);
  uart_send("\r\nend\r\n");
  for(;;);
//  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0, interrupts enabled
  for(;;) {}

  return 0;
}

