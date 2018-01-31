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
#include "stm32l0xx_ll_usart.h" // USART header
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
	LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE3); // regulator configuraiton in order to freq
	
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
	LL_RCC_SetAPB2Prescaler(LL_RCC_SYSCLK_DIV_1);	
	
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
	LL_GPIO_InitTypeDef LL_GPIO_Initstruct; // GPIO initialization struct
	
	LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOB); // Clock freq activated for GPIOB peripheral
	
	/* Pin configuration */
	LL_GPIO_Initstruct.Mode = LL_GPIO_MODE_OUTPUT;
	LL_GPIO_Initstruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	LL_GPIO_Initstruct.Pin = LL_GPIO_PIN_3;
	LL_GPIO_Initstruct.Speed = LL_GPIO_SPEED_HIGH;
	
	LL_GPIO_Init(GPIOB, &LL_GPIO_Initstruct);	// GPIO pin initialize
}

/**
  * @brief  This function initializes the USART2
  * @param  none
  * @retval none
  */
void USART2_Init(void)
{
	LL_USART_InitTypeDef LL_Usart_InitStruct; // USART initialization struct	
	LL_GPIO_InitTypeDef LL_GPIO_Initstruct; // GPIO initialization struct
	
	
	LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA); // Clock freq activated for GPIOA peripheral
	
	/* GPIO pin configuration */
	LL_GPIO_Initstruct.Alternate = LL_GPIO_AF_4;
	LL_GPIO_Initstruct.Mode = LL_GPIO_MODE_ALTERNATE;
	LL_GPIO_Initstruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	LL_GPIO_Initstruct.Pin = LL_GPIO_PIN_9; // Tx Pin
	LL_GPIO_Initstruct.Pull = LL_GPIO_PULL_UP;
	LL_GPIO_Initstruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
	
	LL_GPIO_Init(GPIOA, &LL_GPIO_Initstruct);	// GPIO pin initialize
	
	LL_GPIO_Initstruct.Alternate = LL_GPIO_AF_4;
	LL_GPIO_Initstruct.Mode = LL_GPIO_MODE_ALTERNATE;
	LL_GPIO_Initstruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	LL_GPIO_Initstruct.Pin = LL_GPIO_PIN_10; // Rx Pin
	LL_GPIO_Initstruct.Pull = LL_GPIO_PULL_UP;
	LL_GPIO_Initstruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
	
	LL_GPIO_Init(GPIOA, &LL_GPIO_Initstruct);	// GPIO pin initialize

	/* Important: we need to disable related USART first in order to write 
	 * USART segisters properly! */
	LL_USART_Disable(USART2);
	
	LL_RCC_SetUSARTClockSource(LL_RCC_USART2_CLKSOURCE_SYSCLK); // define usart clocksource as system clock
	
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2); // Clock freq activated for USART2 peripheral
	
	/* USART initialization struct configurations */
	LL_Usart_InitStruct.BaudRate = 115200;
	LL_Usart_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
	LL_Usart_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
	LL_Usart_InitStruct.Parity = LL_USART_PARITY_NONE;
	LL_Usart_InitStruct.StopBits = LL_USART_STOPBITS_1;
	LL_Usart_InitStruct.TransferDirection = LL_USART_TXRX_STANDARD;
	
	LL_USART_Init(USART2, &LL_Usart_InitStruct); // edit USART registers from related struct
	
	LL_USART_Enable(USART2); // enable USART

}
