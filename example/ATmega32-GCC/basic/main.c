/**
 **********************************************************************************
 * @file   main.c
 * @author Hossein.M (https://github.com/Hossein-M98)
 * @brief  example code for ADS1x1x Driver (for ATmega32)
 **********************************************************************************
 *
 * Copyright (c) 2023 Mahda Embedded System (MIT License)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 **********************************************************************************
 */

#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "Retarget.h"
#include "ADS1x1x.h"
#include "ADS1x1x_platform.h"


int main(void)
{
  ADS1x1x_Handler_t Handler = {0};
  ADS1x1x_Sample_t  Sample = {0};

  Retarget_Init(F_CPU, 9600);
  printf("ADS1x1x Driver Example\r\n\r\n");

  ADS1x1x_Platform_Init(&Handler);
  ADS1x1x_Init(&Handler, ADS1X1X_DEVICE_ADS1115, 0);
  ADS1x1x_SetMode(&Handler, ADS1X1X_MODE_CONTINUOUS);
  ADS1x1x_SetPGA(&Handler, ADS1X1X_PGA_2_048);
  ADS1x1x_SetRate(&Handler, ADS1X1X_RATE_16SPS);

  while (1)
  {
    ADS1x1x_SetMux(&Handler, ADS1X1X_MUX_SINGLE_0);
    ADS1x1x_StartConversion(&Handler);
    while (ADS1x1x_CheckDataReady(&Handler) == ADS1X1X_DATA_NOT_READY)
      _delay_ms(1);

    ADS1x1x_ReadSample(&Handler, &Sample);
    printf("Voltage: %fV\r\n", Sample.Voltage);

    _delay_ms(1000);
  }

  ADS1x1x_DeInit(&Handler);
  return 0;
}
