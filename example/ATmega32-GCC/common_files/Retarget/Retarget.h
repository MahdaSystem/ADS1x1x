/**
 ******************************************************************************
 * @file   Retarget.h
 * @author Hossein.M
 * @brief  Config UART to use printf and scanf
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __RETARGET_H__
#define __RETARGET_H__

#ifdef __cplusplus
extern "C" {
#endif


/* Includes ------------------------------------------------------------------*/
#include <stdint.h>


/** 
 ===============================================================================
                              ##### Functions #####                             
 ===============================================================================
*/

/**
 * @brief  Config UART (hardware) to use printf and scanf
 * @note   This function must be called before using printf and scanf.
 * @param  CpuFreq: CPU frequency (Hz)
 * @param  Baudrate: Baudrate (bps)
 * @retval None
 */
void
Retarget_Init(uint32_t CpuFreq, uint16_t Baudrate);



#ifdef __cplusplus
}
#endif


#endif //! __RETARGET_H__
