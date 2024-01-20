#include <msp430.h>
#include <hardware.h>

//void __attribute__ ((interrupt(USCIAB0RX_VECTOR))) USCI0RX_ISR(void)
//{
//    while (!(IFG2&UCA0TXIFG));                // USCI_A0 TX buffer ready?
//    UCA0TXBUF = UCA0RXBUF;                    // TX -> RXed character
//}
