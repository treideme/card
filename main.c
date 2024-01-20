//#include <hardware.h>
//#include <msp430.h>
//
//int main(void) {
//  hardware_init();
//
//  P1SEL = BIT1 + BIT2 ;                     // P1.1 = RXD, P1.2=TXD
//  P1SEL2 = BIT1 + BIT2 ;                    // P1.1 = RXD, P1.2=TXD
//  UCA0CTL1 |= UCSSEL_2;                     // SMCLK
//  UCA0BR0 = 104;                            // 1MHz 9600
//  UCA0BR1 = 0;                              // 1MHz 9600
//  UCA0MCTL = UCBRS0;                        // Modulation UCBRSx = 1
//  UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
//  IE2 |= UCA0RXIE;                          // Enable USCI_A0 RX interrupt
//
//  __bis_SR_register(GIE);       // Enter LPM0, interrupts enabled // LPM0_bits +
//  while(1);
//  return 0;
//}
//
//void __attribute__ ((interrupt(USCIAB0RX_VECTOR))) USCI0RX_ISR(void)
//{
//    while (!(IFG2&UCA0TXIFG));                // USCI_A0 TX buffer ready?
//    UCA0TXBUF = UCA0RXBUF;                    // TX -> RXed character
//}


#include  "msp430g2553.h"

int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  BCSCTL1 = CALBC1_1MHZ;                    // Set DCO
  DCOCTL = CALDCO_1MHZ;
  P1SEL = BIT1 + BIT2 ;                     // P1.1 = RXD, P1.2=TXD
  P1SEL2 = BIT1 + BIT2 ;                     // P1.1 = RXD, P1.2=TXD
  UCA0CTL1 |= UCSSEL_2;                     // SMCLK
  UCA0BR0 = 104;                            // 1MHz 9600
  UCA0BR1 = 0;                              // 1MHz 9600
  UCA0MCTL = UCBRS0;                        // Modulation UCBRSx = 1
  UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
  IE2 |= UCA0RXIE;                          // Enable USCI_A0 RX interrupt

  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0, interrupts enabled
  return 0;
}

//  Echo back RXed character, confirm TX buffer is ready first
void __attribute__ ((interrupt(USCIAB0RX_VECTOR)))  USCI0RX_ISR(void)
{
  while (!(IFG2&UCA0TXIFG));                // USCI_A0 TX buffer ready?
  UCA0TXBUF = UCA0RXBUF;                    // TX -> RXed character
}
