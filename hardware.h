/**
 * @file hardware.h
 * @brief Hardware and pin configuration for device
 *
 *
 *
 *            +--------------------------+
 *       VCC -+ DVCC                DVSS +- VSS
 *      LED0 -+ P1.0                P2.6 +-
 *       RxD -+ P1.1 (RxD)          P2.7 +-
 *       TxD -+ P1.2 (TxD)          TEST +-
 *           -+ P1.3                 RST +-
 *           -+ P1.4          (SDA) P1.7 +--- SDA
 *           -+ P1.5          (SCL) P1.6 +--- SCL
 *           -+ P2.0                P2.5 +-
 *           -+ P2.1                P2.4 +-
 *           -+ P2.2                P2.3 +-
 *            +--------------------------+
 *
 *            1MHz DCO operation
 */
#ifndef _hardware_h_
#define _hardware_h_

#include <msp430.h>

#define INIT_P1DIR \
    0b00000000 /**
      00000000 = default
      ||||||||
      |||||||+-- USISWRST : USI software reset (1 = held in reset state)
      ||||||+--- USIOE    : Data output enable
      |||||+---- USIGE    : Output latch control
      ||||+----- USIMST   : Master select
      |||+------ USILSB   : LSB first transmission
      ||+------- USIPE5   : USI SCLK port enable
      |+-------- USIPE6   : USI SDO/SCL port enable
      +--------- USIPE7   : USI SDI/SDA port enable
 */
#define INIT_USICTL0 \
    0b00000000 /** USICTL0 USI Control Register 0
      00000001 = default
      ||||||||
      |||||||+-- USISWRST : USI software reset (1 = held in reset state)
      ||||||+--- USIOE    : Data output enable
      |||||+---- USIGE    : Output latch control
      ||||+----- USIMST   : Master select
      |||+------ USILSB   : LSB first transmission
      ||+------- USIPE5   : USI SCLK port enable
      |+-------- USIPE6   : USI SDO/SCL port enable
      +--------- USIPE7   : USI SDI/SDA port enable
*/

// Continue from https://github.com/heliocapella/msp430g2553_i2c/blob/master/i2c.c

void hardware_init();
void delay_ms(int ms);



#endif // _hardware_h_
