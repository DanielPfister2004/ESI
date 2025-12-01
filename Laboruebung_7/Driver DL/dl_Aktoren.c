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
volatile int dir = 0;
volatile unsigned int speed_old, ticks, speed = 0;

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
        TA1CCR1 = MinFPW + 25 * iValue;
    else if (iValue < 0)
        TA1CCR1 = MinRPW + 25 * iValue;
    else
        // value == 0
        TA1CCR1 = MaxBreak;

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
    while (speed_controller_impuls <= pulseDuration)
        ;
}

void Driver_LCD_WriteUInt(unsigned int number, int page, int col)
{
    char text[11];
    int pos = 10;

    while (number > 0)
    {
        text[pos] = (number % 10) + '0';
        number /= 10;
        pos--;
    }

    dl_LCDWriteText(text, 11, page, col);
}

#pragma vector = TIMER1_A0_VECTOR
__interrupt void TimerA0_compare(void)
{
    speed_controller_impuls++;
    TA1CCTL0 &= ~CCIFG;  // clear interrupt flag
}

#pragma vector = TIMER0_A1_VECTOR
__interrupt void TimerA0_capture(void)
{
    uint16_t source = TA0IV;

    if (source == TA0IV_TACCR2)
    {
        ticks++;
        TA0CCTL2 &= ~CCIFG;  // optional, TA0IV löscht automatisch
    }

    if (source == TA0IV_TACCR3)
    {
        dir = TA0CCR3;
        TA0CCTL3 &= ~CCIFG;  // optional
    }
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void TimerA0_calc(void)
{
    speed = (ticks * 5 * 10 + speed_old) / 2; // (ticks * 5mm * 10Hz + speed_old) / 2
    speed_old = speed;
    ticks = 0;

    TA0CCTL0 &= ~CCIFG;  // optional
}

