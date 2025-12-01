/*
 * hal_timerA0.c
 *
 *  Created on: 27.11.2025
 *      Author: danie
 */

#include <msp430.h>
#include "hal_timerA0.h"

// configuration for TA0.2 (RPM_SENSOR) and TA0.3 (RPM_SENSOR_DIR)
void hal_timerA0_rpm_measurements_init()
{
    TA0CTL = 0;
    TA0CTL |= TASSEL__SMCLK + TACLR + MC__UP;   // clk = smckl, clear timerA0, continous-Mode
    TA0EX0 |= TAIDEX_4;
    TA0CCR0 =  500000/10;    // is set to 10Hz

    TA0CCTL0 = 0;            // set to zero initialy
    TA0CCTL0 &= ~CAP;        // compare mode
    TA0CCTL0 |= CCIE;        // interrupt enable

    TA0CCTL2 = 0;            // set to zero initialy
    TA0CCTL2 |= CM_3;        // capture mode on BOTH edge - on rising or falling the values must be doubled
    TA0CCTL2 |= SCS ;        // synchron
    TA0CCTL2 |= CAP;         // capture mode
    TA0CCTL2 |= CCIE;        // enable interrupt     //CCIFG is flag, not enable

    TA0CCTL3 = 0;            // set to zero initialy
    TA0CCTL3 |= CM_3;        // capture mode on BOTH edge
    TA0CCTL3 |= SCS ;        // synchron
    TA0CCTL3 |= CAP;         // capture mode
    TA0CCTL3 |= CCIE;        // enable interrupt     //CCIFG is flag, not enable

    // clear interrupt flags
    TA0CCTL0 &= ~CCIFG;
    TA0CCTL2 &= ~CCIFG;
    TA0CCTL3 &= ~CCIFG;
}
