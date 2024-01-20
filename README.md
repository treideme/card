# MSP430G2553 Sample Code

This repo contains various code samples for the MSP-430G2 launchpad.
The processor seems reasonably low-cost for most applications and is
reasonably low-cost, when in-stock.

## Pro
 * Low cost 
 * COR in Malaysia
 * Good documentation
 * C++ support through GNU toolchain
 * [Mature user community](https://forum.43oh.com/)
 * [Can buy direct from TI](https://www.ti.com/ordering-resources/buy.html)

## Against
 * [16-bit ALU, slow compared to ARM](https://forum.43oh.com/topic/3416-stm32l-vs-msp430f5-whats-left-for-msp430)
 * Proprietary debug interface
   * not scriptable with OpenOCD
   * no Semihosting support
 * Proprietary toolchain  by default
   * Allegedly better optimized than comparable GCC toolchain
 * No dedicated Systick timer
 * [No device with crystal-less USB device operation](https://e2e.ti.com/support/microcontrollers/msp-low-power-microcontrollers-group/msp430/f/msp-low-power-microcontroller-forum/62200/msp430-usb-crystal)
   * Budget +$0.3 compared to crystal-less alternative 

# Sample Usage
 * Install MSP430GCC, MSPFlasher
 * Make sure the tools are in ```PATH```

```shell
# Build all sources
meson build
cd build
ninja
# Flash sources to target
meson compile flash_<sample_name>

# Debug any attached sample
meson debug
# Connect GDB-server compliant IDE like clion
# see run/blink.run.xml as sample
```

 * See [Hardware](inc/hardware.h) for the required peripheral connections.