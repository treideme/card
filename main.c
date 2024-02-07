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
#include <hardware.h>
#include <msp430.h>
#include "uart.h"
#include "i2c.h"

//static int field_seen = 0;

int main(void) {
  hardware_init();

  uart_send("Hello World!\r\n");
//  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0, interrupts enabled
  for(;;);


  return 0;
}

