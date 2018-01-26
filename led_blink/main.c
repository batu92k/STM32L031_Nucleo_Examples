/**
  ******************************************************************************
  * @file    main.c
  * @author  Ali Batuhan KINDAN
  * @version V1.0.0
  * @date    26 Jan 2018
  * @brief   Program main source file
  ******************************************************************************
  */

#include "stm32l0xx.h" // Device header
#include "stm32l0xx_ll_gpio.h" // GPIO header
#include "stm32l0xx_ll_rcc.h" // Reset and Control Clock header
#include "stm32l0xx_ll_bus.h" // Bus header
#include "configurations.h" // Congiurations header

/**
  * @brief  Program entry point
  * @param  none
  * @retval none
  */
int main()
{
	int32_t i = 0; // general purpose counter
	
  System_ClockConfiguration(); // system clock configuration
	
	LED3_Init(); // onboard led init
	
	while(1)
	{
		
		LL_GPIO_TogglePin(GPIOB, LL_GPIO_PIN_3); // toggle LED
		
		i = 1500000;
		
		/* basic delay */
		while(i)
		{
			i--;
		}
		
	}

}
