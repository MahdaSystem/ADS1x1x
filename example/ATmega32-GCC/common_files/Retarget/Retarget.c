/**
 **********************************************************************************
 * @file   Retarget.c
 * @author Hossein.M (https://github.com/Hossein-M98)
 * @brief  Config UART to use printf and scanf
 **********************************************************************************
 */

/* Includes ---------------------------------------------------------------------*/
#include "Retarget.h"
#include <stdio.h>
#include <avr/io.h>


/* Private Data Types -----------------------------------------------------------*/
typedef union UBRR_u
{
  struct
  {
    uint8_t UBRRu8L;
    uint8_t UBRRu8H;
  };
  uint16_t UBRRu16;
} ubrr_t;



/**
 ==================================================================================
                           ##### Private Functions #####                           
 ==================================================================================
 */

static int
Retarget_PutChar(char var, FILE *stream)
{
  (void)(stream);
  while (!(UCSRA & (_BV(UDRE))));
  UDR = var;
  return 0;
}

static int
Retarget_GetChar(FILE *stream)
{
  (void)(stream);
  while (!(UCSRA & (_BV(RXC))));
  return UDR;
}


/**
 ==================================================================================
                           ##### Public Functions #####                            
 ==================================================================================
 */

/**
 * @brief  Config UART (hardware) to use printf and scanf
 * @note   This function must be called before using printf and scanf.
 * @param  CpuFreq: CPU frequency (Hz)
 * @param  Baudrate: Baudrate (bps)
 * @retval None
 */
void
Retarget_Init(uint32_t CpuFreq, uint16_t Baudrate)
{
  static FILE STDInOut = FDEV_SETUP_STREAM(Retarget_PutChar, Retarget_GetChar,
                                         _FDEV_SETUP_WRITE | _FDEV_SETUP_READ);
  ubrr_t ubrr = {0};

  stdin = &STDInOut;
  stdout = &STDInOut;

  ubrr.UBRRu16 = CpuFreq / 16 / Baudrate - 1;
  UBRRH = ubrr.UBRRu8H;
  UBRRL = ubrr.UBRRu8L;
  UCSRB = (1 << RXEN) | (1 << TXEN);
  UCSRC = (1 << URSEL) | (3 << UCSZ0);
}
