/*
 * dl_Aktoren.c
 *
 *  Created on: 21.10.2025
 *      Author: danie
 */

#include "dl_Aktoren.h"
#include <msp430.h>
#include <stdint.h>  // for uint32_t or other variables

volatile int speed_controller_impuls = 0;

void dl_SetSteering(int8_t iValue)
{
    int steerVal = 10 * iValue + MIDDLE;

    if (steerVal <= MAX_LEFT)
        TA1CCR2 = MAX_LEFT;
    else if (steerVal >= MAX_RIGHT)
        TA1CCR2 = MAX_RIGHT;
    else
        TA1CCR2 = steerVal;
}

void dl_SetThrottle(int8_t iValue)
{
    // value == -100 => Max RPW
    // value == 0    => Max Break
    // value == 100  => Max FPW

    if (iValue > 100)
        iValue = 100;
    if (iValue < -100)
        iValue = -100;

    if (iValue > 0)
    {
        TA1CCR1 = MinFPW + 25 * iValue;
    }
    else if (iValue < 0)
    {
        TA1CCR1 = MinRPW + 25 * iValue;
    }
    else // value == 0
    {
        TA1CCR1 = MaxBreak;
    }

}

void driver_ESCinit()
{
    createPulses(MaxRPW, 140);
    createPulses(MinRPW, 140);
    createPulses(MinFPW, 140);
    createPulses(MaxFPW, 140);
    createPulses(MaxBreak, 40);
}

void createPulses(int pwm, int pulseDuration)
{
    speed_controller_impuls = 0;
    TA1CCR1 = pwm;
    while (speed_controller_impuls <= pulseDuration);
}
// could already be AL
void test_steering()
{
    int i;
    for (i = -100; i <= 100; i += 2)
    {
        dl_SetSteering(i);
        _delay_cycles(200000);
    }
    for (i = 100; i >= -100; i -= 2)
    {
        dl_SetSteering(i);
        _delay_cycles(200000);
    }
}

void test_driving()
{
    int i;
    for (i = -100; i <= 100; i += 2)
    {
        dl_SetThrottle(i);
        _delay_cycles(200000);
    }
    for (i = 100; i >= -100; i -= 2)
    {
        dl_SetThrottle(i);
        _delay_cycles(200000);
    }
}

#pragma vector = TIMER1_A0_VECTOR
__interrupt void TimerA0(void)
{
    speed_controller_impuls++;
    TA1CCTL0 &= ~CCIFG;  // clear interrupt flag
}

