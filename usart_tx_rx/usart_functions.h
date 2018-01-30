/**
  ******************************************************************************
  * @file    usart_functions.h
  * @author  Ali Batuhan KINDAN
  * @version V1.0.0
  * @date    27 Jan 2018
  * @brief   This file contains all the function prototypes that are used in the 
	*          USART process
  ******************************************************************************
  */

#ifndef USART_FUNCTIONS_H
#define USART_FUNCTIONS_H

#include "stm32l0xx_ll_usart.h" // USART driver header	
#include "usart_functions.h" // USART driver header

void USART_Puts(USART_TypeDef* USARTx, volatile char *s);

#endif
