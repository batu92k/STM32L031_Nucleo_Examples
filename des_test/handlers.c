/**
  ******************************************************************************
  * @file    handlers.c
  * @author  Ali Batuhan KINDAN
  * @version V1.0.0
  * @date    27 Jan 2018
  * @brief   This file contains all of the interrupt handler functions that are 
	*          used in the application
  ******************************************************************************
  */

#include "stm32l0xx.h" // Device header
#include "stm32l0xx_ll_gpio.h" // GPIO header
#include "stm32l0xx_ll_usart.h" // USART header
#include "handlers.h"
	
/**
  * @brief  USART2 interrupt handler
  * @param  none
  * @retval none
  */	
void USART2_IRQHandler(void)
{

	if((USART2->ISR & USART_ISR_RXNE) == USART_ISR_RXNE)
	{
	    char t = USART2->RDR;
	
      if(t == 'a')			
			{			
				LL_GPIO_TogglePin(GPIOB, LL_GPIO_PIN_3);
			}
			
	}
	
}	
