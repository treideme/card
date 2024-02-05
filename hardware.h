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
 * @file hardware.h
 * @author Thomas Reidemeister
 * @verbatim
 *            +--------------------------+
 *       VCC -+ DVCC                DVSS +- VSS
 *      LED0 -+ P1.0                P2.6 +-
 *       RxD -+ P1.1 (RxD)          P2.7 +-
 *       TxD -+ P1.2 (TxD)          TEST +-
 * NFC_FIELD -+ P1.3                 RST +-
 *           -+ P1.4          (SDA) P1.7 +--- SDA
 *           -+ P1.5          (SCL) P1.6 +--- SCL
 *           -+ P2.0                P2.5 +-
 *           -+ P2.1                P2.4 +-
 *           -+ P2.2                P2.3 +-
 *            +--------------------------+
 *            1MHz DCO operation
 * @endverbatim
 */
#ifndef _hardware_h_
#define _hardware_h_

#include <msp430.h>
#include "st25dv.h"
#include "uart.h"
#include "i2c.h"

// Continue from https://github.com/heliocapella/msp430g2553_i2c/blob/master/i2c.c

void hardware_init();
void delay_ms(int ms);

#endif // _hardware_h_
