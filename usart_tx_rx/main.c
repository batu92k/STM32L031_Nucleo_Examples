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
#include "configurations.h" // configurations header

/**
  * @brief  Program entry point
  * @param  none
  * @retval none
  */
int main(void)
{
	
	System_ClockConfiguration(); // system clock configuration 
	
	LED3_Init(); // on board LED initialization
	
	/* main loop */
	while(1)
	{
		
	}
	
}	
