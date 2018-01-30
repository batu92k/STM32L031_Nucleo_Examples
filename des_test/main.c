/**
  ******************************************************************************
  * @file    main.c
  * @author  Ali Batuhan KINDAN
  * @version V1.0.0
  * @date    30 Jan 2018
  * @brief   Program main function
  ******************************************************************************
  */
	
#include "stm32l0xx.h"                  // Device header
#include "stdio.h" // Standard IO header
#include "stm32l0xx_ll_usart.h" // USART driver header
#include "stm32l0xx_ll_gpio.h" // GPIO header
#include "stm32l0xx_ll_utils.h" // Utilities header
#include "stm32l0xx_ll_rcc.h" // Reset and Control Clock header
#include "configurations.h" // Configurations header
#include "usart_functions.h" // USART functions header
#include "handlers.h" // Interrupt handers header


int main()
{
	System_ClockConfiguration(); // system clock configuration
	
	LED3_Init(); // Onboard LED initialization
	
	USART2_Init(); // USART2 initialization with RX interrupt
	
	while(1)
	{
		
	}
	
}
