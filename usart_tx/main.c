/**
  ******************************************************************************
  * @file    main.c
  * @author  Ali Batuhan KINDAN
  * @version V1.0.0
  * @date    26 Jan 2018
  * @brief   main program source file
  ******************************************************************************
  */
	
#include "stm32l0xx.h" // Device header
#include "stdio.h" // standard IO header
#include "stm32l0xx_ll_usart.h" // USART driver header
#include "stm32l0xx_ll_gpio.h" // GPIO header
#include "configurations.h" // Configurations header
#include "usart_functions.h" // USART functions header

char str[50]; // USART buffer string
int32_t i = 0; // general purpose

/**
  * @brief  Program entry point
  * @param  none
  * @retval none
  */
int main()
{
	
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
