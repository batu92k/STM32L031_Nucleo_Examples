/**
  ******************************************************************************
  * @file    usart_functions.c
  * @author  Ali Batuhan KINDAN
  * @version V1.0.0
  * @date    27 Jan 2018
  * @brief   This file contains all the functions that are used in the USART process
  ******************************************************************************
  */

#include "stm32l0xx_ll_usart.h" // USART driver header	
#include "usart_functions.h" // USART functions header

/**
  * @brief  This function is used for transmit a character array
	*         through USART communication
  * @param  USARTx
	* @param  txArray
  * @retval none
  */	
void USART_Puts(USART_TypeDef* USARTx, volatile char *txArray)
{
	
	while(*txArray)
	{
		while(!(USARTx ->ISR & 0x0040)); // usart kullanilabilir olana kadar bekle
		LL_USART_TransmitData8(USART2, *txArray); // veriyi gönder
		*txArray++; // bir sonraki karaktere geç
	}
	
}
