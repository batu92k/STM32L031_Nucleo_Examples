/**
  ******************************************************************************
  * @file    main.c
  * @author  Ali Batuhan KINDAN
  * @version V1.0.0
  * @date    30 Jan 2018
  * @brief   Program main function
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
#include "handlers.h" // Interrupt handers header
#include "des_module.h" // Data Encryption Standart module

DES_InitTypedef DES_InitStructure; // DES initialization structure

#define DataLenght 5 // data array lenght

#define MAX_STRLEN 30 // max character number of buffer array

volatile char buffer_string[MAX_STRLEN+1]; // buffer string

/**
  * @brief  Program entry point
	* @param  none
  * @retval none
  */
int main()
{
	System_ClockConfiguration(); // system clock configuration
	
	uint32_t i = 0; // general purpose counter
	uint8_t clean_cnt = 0; // array clear counter
	
	/* The arrays that will use in the DES routine defined */
	uint64_t plainText[DataLenght] = { 0x123456789ABCDEF, 0x023456789ABCDEF, 0x103456789ABCDEF, 0x120456789ABCDEF, 0x123456789ABCDEF};
	uint64_t cipherText[DataLenght];
	uint64_t decryptedText[DataLenght];

	/* DES structure configured */
	DES_InitStructure.Key = 0x16645779CCBCDFF1;
	DES_InitStructure.IV = 0xFCAEBBCCEE234FF1;
	DES_InitStructure.Mode = CBC;		
	
	LED3_Init(); // Onboard LED initialization
	
	USART2_Init(); // USART2 initialization with RX interrupt
	
	while(1)
	{
	
		DES_Encrypt_Data(&DES_InitStructure, plainText, cipherText, DataLenght); // DES encryption routine
		DES_Decrypt_Data(&DES_InitStructure, cipherText, decryptedText, DataLenght); // DES decryption routine
    
		/* plain text transmitting routine */
		for(i = 0; i < DataLenght; i++)
		{
			sprintf((char*)buffer_string, "Plain Text %d: %016llx\n", i ,plainText[i]);
			USART_Puts(USART2, buffer_string);	
			
			/* array cleared after the transmiting process completed */
			for(clean_cnt = 0; clean_cnt < MAX_STRLEN; clean_cnt++)
			{
				buffer_string[clean_cnt] = NULL;
			}		
			
		}
		
		/* cipher text transmitting routine */
		for(i = 0; i < DataLenght; i++)
		{
			sprintf((char*)buffer_string,"Cipher Text %d: %016llx\n", i, cipherText[i]);
			USART_Puts(USART2, buffer_string);	
			
			/* array cleared after the transmiting process completed */
			for(clean_cnt = 0; clean_cnt < MAX_STRLEN; clean_cnt++)
			{
				buffer_string[clean_cnt] = NULL;
			}				
			
		}
		
		/* decrypted text transmitting routine */
		for(i = 0; i < DataLenght; i++)
		{
			if(plainText[i] == decryptedText[i])
			{
				sprintf((char*)buffer_string,"Decrypted Text %d: %016llx - OK\n", i, decryptedText[i]);
				USART_Puts(USART2, buffer_string);	
				
				/* array cleared after the transmiting process completed */
				for(clean_cnt = 0; clean_cnt < MAX_STRLEN; clean_cnt++)
				{
					buffer_string[clean_cnt] = NULL;
				}	
				
			}
			else
			{
				sprintf((char*)buffer_string,"Decrypted Text %d: %016llx - F\n", i, decryptedText[i]);
				USART_Puts(USART2, buffer_string);
				
				/* array cleared after the transmiting process completed */
				for(clean_cnt = 0; clean_cnt < MAX_STRLEN; clean_cnt++)
				{
					buffer_string[clean_cnt] = NULL;
				}					
							
			}
		}		
		
	} // main loop
	
}
