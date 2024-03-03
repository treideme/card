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

//static int field_seen = 0;

int main(void) {
  hardware_init();

  char tmp[20];

  uart_send("Hello World!\r\n");
  const uint8_t reg = 0x39;
  uint8_t id = 0x00;
  uart_send("Before transfer\r\n");
  int err = i2c_transfer(B8(00110000), &reg, 1, &id, 1);
  if(err) {
    uart_send("Error\r\n");
  } else {
    uart_send("OK");
    itoa(id, tmp, 10);
    uart_send(tmp);
    uart_send("\r\n");
  }
//  i2c_master_init(0x2D);
//  i2c_read(0x02, (uint8_t*)&c);
//  itoa(c, tmp, 10);
//  tmp[19] = 0;
//  uart_send(tmp);
//  uart_send("\r\nend\r\n");
//  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0, interrupts enabled
  for(;;) {}

  return 0;
}

