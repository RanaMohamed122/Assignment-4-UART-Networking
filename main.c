//*****************************************************************************
//
// timers.c - Timers example.
//
// Copyright (c) 2012-2017 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
//
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
//
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
//
// This is part of revision 2.1.4.178 of the EK-TM4C123GXL Firmware Package.
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"

void delay(uint32_t n)
{
    int i,j;
    for (i = 0; i < n; ++i) {
        for (j = 0; j < 3180; ++j) {

        }
    }
}
void PortAIntHandler(){
GPIOIntClear(GPIO_PORTF_BASE, GPIO_PIN_4);
GPIOIntDisable(GPIO_PORTF_BASE, GPIO_PIN_4);
        blink();
        UARTCharPut(UART1_BASE, 'c');
GPIOIntEnable(GPIO_PORTF_BASE, GPIO_PIN_4);
}
void blink(){
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);
    delay(500);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x0);
}
int main(){
//
// Enable the GPIOA peripheral
//
SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);

//
// Wait for the GPIOA module to be ready.
//
while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
{
}
while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOC))
{
}

while(!SysCtlPeripheralReady(SYSCTL_PERIPH_UART1))
{

}
UARTConfigSetExpClk(UART1_BASE, SysCtlClockGet(), 38400,
(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
UART_CONFIG_PAR_NONE));
//
// Register the port-level interrupt handler. This handler is the first
// level interrupt handler for all the pin interrupts.
//
//
// Initialize the GPIO pin configuration.
//
// Set pins 2, 4, and 5 as input, SW controlled.
//
GPIOPinTypeGPIOInput(GPIO_PORTF_BASE,GPIO_PIN_4 );
GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1);

GPIOPadConfigSet(GPIO_PORTF_BASE,GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);



// Make pins 2 and 4 rising edge triggered interrupts.
//

GPIOIntTypeSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_FALLING_EDGE);
GPIOIntRegister(GPIO_PORTF_BASE, PortAIntHandler);
GPIOIntEnable(GPIO_PORTF_BASE, GPIO_INT_PIN_4);
GPIOPinConfigure(GPIO_PC4_U1RX);
GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_4);
GPIOPinConfigure(GPIO_PC5_U1TX);
GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_5);


while(1){

    if(UARTCharGet(UART1_BASE))
        blink();
//    if(UARTCharGetNonBlocking(UART1_BASE))
//        blink();

}

}
//
// Write some pins. Even though pins
