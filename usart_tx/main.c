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
#include "configurations.h" // Configurations header

/**
  * @brief  Program entry point
  * @param  none
  * @retval none
  */
int main()
{
	
	System_ClockConfiguration(); // configurate system clock
	
	LED3_Init(); // initialize onboard LED
	
	while(1)
	{
	
		
	}
				
}
