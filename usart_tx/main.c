/**
  ******************************************************************************
  * @file    main.c
  * @author  Ali Batuhan KINDAN
  * @version V1.0.0
  * @date    27 Jan 2018
  * @brief   main program source file
  ******************************************************************************
  */
	
#include "stm32l0xx.h" // Device header
#include "stdio.h" // Standard IO header
#include "stm32l0xx_ll_usart.h" // USART driver header
#include "stm32l0xx_ll_gpio.h" // GPIO header
#include "stm32l0xx_ll_utils.h" // Utilities header
#include "stm32l0xx_ll_rcc.h" // Reset and Control Clock header
#include "configurations.h" // Configurations header
#include "usart_functions.h" // USART functions header

char str[50]; // USART buffer string
static int32_t i = 0; // general purpose counter

/**
  * @brief  Program entry point
  * @param  none
  * @retval none
  */
int main(void)
{
	
	System_ClockConfiguration(); // system clock configuration 
	
	LED3_Init(); // onboard LED initialization
	
	USART2_Init(); // USART2 initialization
	
	
	
	/* main loop */
	while(1)
	{
		
		sprintf(str, "STM32L031 USART Test\n");
		USART_Puts(USART2, str);
		
		i = 1500000;
		
		/* basic delay */
		while(i)
		{
			i--;
		}	
		
	}
	
}	
