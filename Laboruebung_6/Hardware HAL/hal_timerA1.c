#include <msp430.h>
#include "hal_timerA1.h"

void hal_timerA1_Init()
{
    TA1CTL = 0;
    TA1CTL |= TASSEL__SMCLK + TACLR + MC__UP;   // clear timerA1, clk = SMCKL, up-Mode

    TA1CCTL0 = 0;            // set to zero initialy
    TA1CCTL0 &= ~CAP;        // compare mode
    TA1CCTL0 |= CCIE;        // interrupt enable

    TA1CCTL1 = 0;            // set to zero initialy
    TA1CCTL1 &= ~CAP;        // comapre mode
    TA1CCTL1 |= OUTMOD_7;    // reset/set

    TA1CCTL2 = 0;            // set to zero initialy
    TA1CCTL2 &= ~CAP;        // comapre mode
    TA1CCTL2 |= OUTMOD_7;    // reset/set

    TA1CCR0 = 41667;         // for 60Hz 2,5MHz
    TA1CCR1 = 0;             // CCR1 throttle
    TA1CCR2 = 0;             // CCR2 steering

    TA1CCTL0 &= ~CCIFG;
}


// configuration for TA0.2 (RPM_SENSOR) and TA0.3 (RPM_SENSOR_DIR)
void hal_timerA0_rpm_measurements_init()
{
    TA0CTL = 0;
    TA0CTL |= TASSEL__SMCLK + TACLR + MC__CONTINOUS;   // clk = smckl, clear timerA0, continous-Mode

    TA0CCTL2 = 0;            // set to zero initialy
    TA0CCTL2 |= CM_1;        // capture mode on rising edge
    TA0CCTL2 |= SCS ;        // synchron
    TA0CCTL2 |= CAP;         // capture mode
    TA0CCTL2 |= CCIE;        // enable interrupt     //CCIFG is flag, not enable

    TA0CCTL3 = 0;            // set to zero initialy
    TA0CCTL3 |= CM_1;        // capture mode on rising edge
    TA0CCTL3 |= SCS ;        // synchron
    TA0CCTL3 |= CAP;         // capture mode
    TA0CCTL3 |= CCIE;        // enable interrupt     //CCIFG is flag, not enable

    // clear interrupt flags
    TA0CCTL2 &= ~CCIFG;
    TA0CCTL3 &= ~CCIFG;
}









