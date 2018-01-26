/**
  ******************************************************************************
  * @file    configurations.c
  * @author  Ali Batuhan KINDAN
  * @version V1.0.0
  * @date    26 Jan 2018
  * @brief   This file includes all of the microcontroller hardware configuraiton 
  *          functions that are used in application	
  ******************************************************************************
  */
	

#include "stm32l0xx_ll_rcc.h" // Reset and Control Clock header
#include "stm32l0xx_ll_pwr.h" // Power header
#include "stm32l0xx_ll_gpio.h" // GPIO header
#include "stm32l0xx_ll_bus.h" // Bus header
#include "configurations.h" // Congiurations header

/**
  * @brief  This function configurates the system clock as:
	*         - uses HSI as PLL source
	*         - uses PLL as system clock at 24 MHz
  * @param  none
  * @retval none
  */
void System_ClockConfiguration(void)
{
	LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE1); // regulator configuraiton in order to freq
	
	/* high speed internal (HSI - 16MHz) system clock avtivating
   * in order to use for PLL source clock	*/
	LL_RCC_HSI_Enable(); 
	LL_RCC_HSI_DisableDivider();

	/* PLL configuration */
  LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSI, LL_RCC_PLL_MUL_6, LL_RCC_PLL_DIV_4);
	LL_RCC_PLL_Enable();
	
	LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL); // set system clock source as PLL
	
	/* peripheral clock divide value configuraiton */
	LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1); 
	LL_RCC_SetAPB1Prescaler(LL_RCC_SYSCLK_DIV_1);	
	
	SystemCoreClockUpdate(); // system clock updating
}

/**
  * @brief  This function initializes the onboard LED3 on
  *         STM32L031 Nucleo device
  * @param  none
  * @retval none
  */
void LED3_Init(void)
{
	LL_GPIO_InitTypeDef LL_Gpio_Initstruct; // GPIO initialization struct
	
	LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOB); // Clock freq activated for GPIOB peripheral
	
	/* Pin configuration */
	LL_Gpio_Initstruct.Mode = LL_GPIO_MODE_OUTPUT;
	LL_Gpio_Initstruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	LL_Gpio_Initstruct.Pin = LL_GPIO_PIN_3;
	LL_Gpio_Initstruct.Speed = LL_GPIO_SPEED_HIGH;
	
	LL_GPIO_Init(GPIOB, &LL_Gpio_Initstruct);	// GPIO pin initialize
}
