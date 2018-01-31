/**
  ******************************************************************************
  * @file    main.c
  * @author  Ali Batuhan KINDAN
  * @version V1.0.0
  * @date    26 Jan 2018
  * @brief   main program source file
  ******************************************************************************
  */

#include "configurations.h" // Configurations header
#include "usart_functions.h" // Usart functions header
#include "stm32l0xx_ll_rcc.h" // Reset and Control Clock header
#include "stm32l0xx_ll_pwr.h" // Power header
#include "stm32l0xx_ll_gpio.h" // GPIO header
#include "stm32l0xx_ll_bus.h" // Bus header
#include "stm32l0xx_ll_usart.h" // USART header
#include "stm32l0xx.h" // Device header
#include "stdio.h"

char str[50]; // USART buffer string


/**
  * @brief  Program entry point
  * @param  none
  * @retval none
  */
int main()
{
	int32_t i = 0; // general purpose
	
	System_ClockConfiguration(); // configurate system clock
	
	USART2_Init(); // inizialize USART2
	
	LED3_Init(); // initialize onboard LED
	
	/* main loop */
	while(1)
	{

		/* USART transmit routine */
		sprintf(str, "STM32L031 USART Tx Test\n");
		USART_Puts(USART2, str);
		
		i = 150000; // delay value set
		
		/* basic delay */
		while(i)
		{
			i--;
		}
		
	}
				
}
