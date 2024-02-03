#include "hardware.h"
#include <msp430.h>

void hardware_init() {
  WDTCTL = WDTPW | WDTHOLD;       // stop watchdog timer

  // Configure clock to 1MHz
  DCOCTL  = 0;           // Select lowest DCOx and MODx setting
  BCSCTL1 = CALBC1_1MHZ; // Set DCO
  DCOCTL  = CALDCO_1MHZ;
}

void delay_ms(int ms) {
    volatile unsigned int i, j;
    for(i=ms; i>0; i--) {
        for(j=0; j < 200; j++); // delay
    }
}
