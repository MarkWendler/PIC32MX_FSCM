# MPLAB X Project: PIC32MX_FSCM_Test_USBIII

FSCM Test code for PIC32MX450F256L USB Starter kit III
Fail safe clock monitor enabled and interrupt implemented

## Getting Started

1. Clone or Download project.
2. Connect USB mini connector PKOB4. (Pickit on Board)
3. Open project with MPLAB X
4. Build project then program the HW

## Operation
* MCU starts with external crystal + PLL 48MHz.
* LED1 is blinking from timer 1 interrupt (500ms)
* Shortcut the Y1 Oscilaltor pins with a 1kOhm resistor
   * FSCM interrupt occures -> LED3 switch ON
   * Oscillator switches to internal FRC -> LED2 switch ON
   * LED1 blinks slowly -> system clock slowed down to 8MHz