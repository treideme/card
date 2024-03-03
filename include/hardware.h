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
#ifndef HARDWARE_H
#define HARDWARE_H

#include <msp430.h>
#include "st25dv.h"
#include "uart.h"
#include "i2c.h"

// Useful macros
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#define HEX__(n)    0x##n##LU
#define B8__(x)     ((x&0x0000000FLU)?1:0) \
                   +((x&0x000000F0LU)?2:0) \
                   +((x&0x00000F00LU)?4:0) \
                   +((x&0x0000F000LU)?8:0) \
                   +((x&0x000F0000LU)?16:0) \
                   +((x&0x00F00000LU)?32:0) \
                   +((x&0x0F000000LU)?64:0) \
                   +((x&0xF0000000LU)?128:0)

// Note bitfields are GCC extensions, use macros instead to permit pedantic checks
#define B8(d)                   ((unsigned char)B8__(HEX__(d)))
#define B16(dmsb,dlsb)          (((unsigned short)B8(dmsb)<<8) + B8(dlsb))
#define B32(dmsb,db2,db3,dlsb)  (((unsigned long)B8(dmsb)<<24) \
                               + ((unsigned long)B8(db2)<<16) \
                               + ((unsigned long)B8(db3)<<8) \
                               + B8(dlsb))

void hardware_init();
void delay_ms(int ms);

#endif // HARDWARE_H
