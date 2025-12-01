/*
 * hal_adc12.h
 *
 *  Created on: 29.11.2025
 *      Author: danie
 */

#ifndef HARDWARE_HAL_HAL_ADC12_H_
#define HARDWARE_HAL_HAL_ADC12_H_

#include <msp430.h>

typedef struct {
  union {
    unsigned char R;
    struct {
      unsigned char ADCrdy:1; // Bit = 1, wenn Daten bereit sind
      unsigned char dummy:7;
    } B;
  } Status;

  union {
    unsigned short ADCBuffer[4];
    struct {
      unsigned short SensorLeft;
      unsigned short SensorRight;
      unsigned short SensorFront;
      unsigned short VBat;
    } Sensor;
  } Data;

} ADC12Com;

ADC12Com ADC12Data;

void hal_ADC12Init();

#endif /* HARDWARE_HAL_HAL_ADC12_H_ */
