/**
  ******************************************************************************
  * @file    des_module.c
  * @author  Ali Batuhan KINDAN
  * @version V1.0.0
  * @date    02 Dec 2017
  * @brief   This file contains the sources of DES (Data Encryption Standart) calculation
  * 		 		 routine functions
  ******************************************************************************
  */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "des_module.h"

// DES - Permuted choice 1 matrix
const uint8_t PC_1[56] = {	57,   49,    41,   33,    25,    17,    9,
														 1,   58,    50,   42,    34,    26,   18,
														10,    2,    59,   51,    43,    35,   27,
														19,   11,     3,   60,    52,    44,   36,
														63,   55,    47,   39,    31,    23,   15,
														 7,   62,    54,   46,    38,    30,   22,
														14,    6,    61,   53,    45,    37,   29,
														21,   13,     5,   28,    20,    12,    4	};

// DES - Permuted choice 2 matrix
const uint8_t PC_2[48] = { 	14,    17,   11,    24,     1,    5,
														 3,    28,   15,     6,    21,   10,
														23,    19,   12,     4,    26,    8,
														16,     7,   27,    20,    13,    2,
														41,    52,   31,    37,    47,   55,
														30,    40,   51,    45,    33,   48,
														44,    49,   39,    56,    34,   53,
														46,    42,   50,    36,    29,   32   };

// DES - Initial Permutation Matrix
const uint8_t IP[64] = {  58,    50,   42,   34,   26,   18,   10,   2,
													60,    52,   44,   36,   28,   20,   12,   4,
													62,    54,   46,   38,   30,   22,   14,   6,
													64,    56,   48,   40,   32,   24,   16,   8,
													57,    49,   41,   33,   25,   17,    9,   1,
													59,    51,   43,   35,   27,   19,   11,   3,
													61,    53,   45,   37,   29,   21,   13,   5,
													63,    55,   47,   39,   31,   23,   15,   7  };

// IP^-1 Permutation Matrix
const uint8_t IP_[64] = {  40,    8,   48,   16,   56,   24,   64,  32,
													 39,    7,   47,   15,   55,   23,   63,  31,
													 38,    6,   46,   14,   54,   22,   62,  30,
													 37,    5,   45,   13,   53,   21,   61,  29,
													 36,    4,   44,   12,   52,   20,   60,  28,
													 35,    3,   43,   11,   51,   19,   59,  27,
													 34,    2,   42,   10,   50,   18,   58,  26,
													 33,    1,   41,    9,   49,   17,   57,  25  };


// DES - Calculated Keys 0-15 (Kn)
uint64_t Sub_Keys[16];

// 28 bits left part of subkeys
uint32_t Cn[17];

// 28 bits right part of subkeys
uint32_t Dn[17];

// DES - Bit Shift Table
const uint8_t Shift_Table[16] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };

// DES - E bit selection table
const uint8_t E_Bit_Selection_Table[48] = { 32,     1,    2,     3,     4,    5,
																						 4,     5,    6,     7,     8,    9,
																						 8,     9,   10,    11,    12,   13,
																						12,    13,   14,    15,    16,   17,
																						16,    17,   18,    19,    20,   21,
																						20,    21,   22,    23,    24,   25,
																						24,    25,   26,    27,    28,   29,
																						28,    29,   30,    31,    32,    1 };

// S-Box S 1 to 8
const uint8_t SBox[8][4][16] =
{
	{
			{  14,  4,  13,  1,   2, 15,  11,  8,   3,  10,   6,  12,  5,  9,  0,  7 },
			{		0, 15,   7,  4,  14,  2,  13,  1,  10,   6,  12,  11,  9,  5,  3,  8 },
			{		4,  1,  14,  8,  13,  6,   2, 11,  15,  12,   9,   7,  3, 10,  5,  0 },
			{  15, 12,   8,  2,   4,  9,   1,  7,   5,  11,   3,  14, 10,  0,  6, 13 }
	},

	{
			{  15,  1,   8, 14,   6, 11,   3,  4,   9,   7,   2,  13, 12,  0,  5, 10 },
			{		3, 13,   4,  7,  15,  2,   8, 14,  12,   0,   1,  10,  6,  9, 11,  5 },
			{		0, 14,   7, 11,  10,  4,  13,  1,   5,   8,  12,   6,  9,  3,  2, 15 },
			{  13,  8,  10,  1,   3, 15,   4,  2,  11,   6,   7,  12,  0,  5, 14,  9 }
	},

	{
			{  10,  0,   9, 14,   6,  3,  15,  5,   1,  13,  12,   7,  11,  4,  2,  8 },
			{  13,  7,   0,  9,   3,  4,   6, 10,   2,   8,   5,  14,  12, 11, 15,  1 },
			{  13,  6,   4,  9,   8, 15,   3,  0,  11,   1,   2,  12,   5, 10, 14,  7 },
			{   1, 10,  13,  0,   6,  9,   8,  7,   4,  15,  14,   3,  11,  5,  2, 12 }

	},

	{
			{   7, 13,  14,  3,   0,  6,   9, 10,   1,   2,   8,   5,  11, 12,  4, 15 },
			{  13,  8,  11,  5,   6, 15,   0,  3,   4,   7,   2,  12,   1, 10, 14,  9 },
			{  10,  6,   9,  0,  12, 11,   7, 13,  15,   1,   3,  14,   5,  2,  8,  4 },
			{   3, 15,   0,  6,  10,  1,  13,  8,   9,   4,   5,  11,  12,  7,  2, 14 }
	},

	{
			{   2, 12,   4,  1,   7, 10,  11,  6,   8,   5,   3,  15,  13,  0, 14,  9 },
			{  14, 11,   2, 12,   4,  7,  13,  1,   5,   0,  15,  10,   3,  9,  8,  6 },
			{   4,  2,   1, 11,  10, 13,   7,  8,  15,   9,  12,   5,   6,  3,  0, 14 },
			{  11,  8,  12,  7,   1, 14,   2, 13,   6,  15,   0,   9,  10,  4,  5,  3 }
	},

	{
			{  12,  1,  10, 15,   9,  2,   6,  8,   0,  13,   3,   4,  14,  7,  5, 11 },
			{  10, 15,   4,  2,   7, 12,   9,  5,   6,   1,  13,  14,   0, 11,  3,  8 },
			{   9, 14,  15,  5,   2,  8,  12,  3,   7,   0,   4,  10,   1, 13, 11,  6 },
			{   4,  3,   2, 12,   9,  5,  15, 10,  11,  14,   1,   7,   6,  0,  8, 13 }
	},

	{
			{   4, 11,   2, 14,  15,  0,   8, 13,   3,  12,   9,   7,   5, 10,  6,  1 },
			{  13,  0,  11,  7,   4,  9,   1, 10,  14,   3,   5,  12,   2, 15,  8,  6 },
			{   1,  4,  11, 13,  12,  3,   7, 14,  10,  15,   6,   8,   0,  5,  9,  2 },
			{   6, 11,  13,  8,   1,  4,  10,  7,   9,   5,   0,  15,  14,  2,  3, 12 }
	},

	{
			{   13,  2,   8,  4,   6, 15,  11,  1,  10,   9,   3,  14,   5,  0, 12,  7 },
			{    1, 15,  13,  8,  10,  3,   7,  4,  12,   5,   6,  11,   0, 14,  9,  2 },
			{    7, 11,   4,  1,   9, 12,  14,  2,   0,   6,  10,  13,  15,  3,  5,  8 },
			{    2,  1,  14,  7,   4, 10,   8, 13,  15,  12,   9,   0,   3,  5,  6, 11 }
	}

};

// The Permutation
const uint8_t P[32] = {  16,   7,  20,  21,
												 29,  12,  28,  17,
													1,  15,  23,  26,
													5,  18,  31,  10,
													2,   8,  24,  14,
												 32,  27,   3,   9,
												 19,  13,  30,   6,
												 22,  11,   4,  25 };


/**
  * @brief  this function is used for DES encryption of data array
  * @param  DESx
  * @param 	plainData
  * @param  cipherText
  * @retval none
  */
void DES_Encrypt_Data(DES_InitTypedef* DESx, uint64_t* plainData, uint64_t* cipherData, uint16_t lenght)
{
	uint16_t i = 0;
	uint64_t chainBuffer = 0x0000000000000000;

	switch(DESx->Mode)
	{
		// Electronic Code Book
		case ECB:

			DES_Get_Subkeys(DESx); // Sub Key calculation

			for(i = 0; i < lenght; i++)
			{
				cipherData[i] = DES_Encode_BlockData(plainData[i]);
			}

			break;

		// Cipher Block Chaining
		case CBC:

			DES_Get_Subkeys(DESx); // Sub Key calculation

			chainBuffer = (DESx->IV ^ plainData[0]);

			cipherData[0] = DES_Encode_BlockData(chainBuffer);

			for(i = 1; i < lenght; i++)
			{
				chainBuffer = (cipherData[i-1] ^ plainData[i]);

				cipherData[i] = DES_Encode_BlockData(chainBuffer);
			}

			break;

		default:

			break;
	}

}

/**
  * @brief  this function is used for DES decryption of data array
  * @param  DESx
  * @param 	plainData
  * @param  cipherText
  * @retval none
  */
void DES_Decrypt_Data(DES_InitTypedef* DESx, uint64_t* cipherData, uint64_t* plainData, uint16_t lenght)
{
	uint16_t i = 0;
	uint64_t chainBuffer = 0x0000000000000000;

	switch(DESx->Mode)
	{
		case ECB:

			DES_Get_Subkeys(DESx);

			for(i = 0; i < lenght; i++)
			{
				plainData[i] = DES_Decode_BlockData(cipherData[i]);
			}

			break;

		case CBC:

			DES_Get_Subkeys(DESx);

			chainBuffer = DES_Decode_BlockData(cipherData[0]);

			plainData[0] = (chainBuffer ^ DESx->IV);

			for(i = 1; i < lenght; i++)
			{
				chainBuffer = DES_Decode_BlockData(cipherData[i]);

				plainData[i] = (chainBuffer ^ cipherData[i-1]);
			}

			break;

		default:

			break;

	}

}

/**
  * @brief  this function is used for calculating the subkeys from given key
  * @param  DESx
  * @retval none
  */
void DES_Get_Subkeys(DES_InitTypedef* DESx)
{
	uint64_t permutedKey = 0x0000000000000000; // permuted key K+
	uint64_t bitShift_Buffer = 0x0000000000000000; // buffer value
	uint64_t cnBuffer = 0x0000000000000000; // C value buffer
	uint64_t dnBuffer = 0x0000000000000000; // D value buffer
	uint64_t preSubKey = 0x0000000000000000; // buffer value 2
	uint8_t i = 0; // general purpose sentinel variable
	uint8_t j = 0; // general purpose sentinel variable

	// clear all subkeys
	for(i = 0; i < 16; i++)
	{
		Sub_Keys[i] = 0x0000000000000000;
	}

	// permuted key K+ (key_) creating from original key and PC_1 matrix
	for(i = 0; i < 56; i++)
	{
		bitShift_Buffer = 0x8000000000000000; // inititial value for big endian bit shifting
		bitShift_Buffer = (bitShift_Buffer >> (PC_1[i]-1)); // shift the buffer value according to PC_1 matrix
		bitShift_Buffer = bitShift_Buffer & (DESx->Key); // find the related bit value of original key
		bitShift_Buffer = (bitShift_Buffer << (PC_1[i]-1)); // revoke the shifting process
		bitShift_Buffer = (bitShift_Buffer >> i); // shift buffer value according to permuted key bit number

		permutedKey = (permutedKey | bitShift_Buffer); // add calculated bit value to related permuted key bit
	}

	//printf("K+ 0x%I64X\n", key_);

	Cn[0] = (0xFFFFFFF000000000 & permutedKey) >> 32; // 28 bits left part of permuted key K+
	Dn[0] = (0x0000000FFFFFFF00 & permutedKey) >> 4; // 28 bits right part of permuted key K+

	//printf("C_0 0x%I32X\n", Cn[0]);
	//printf("D_0 0x%I32X\n", Dn[0]);

	// pre-permuted subkey parts (Cn, Dn) calculation routine
	for(i = 0; i < 16; i++)
	{
		// every part of subkeys creating from the related previous part
		Cn[i+1] = DES_Subkey_BitShifter(Cn[i], Shift_Table[i]);
		Dn[i+1] = DES_Subkey_BitShifter(Dn[i], Shift_Table[i]);

		//printf("C_%d 0x%I32X\n", (i+1), Cn[i+1]);
		//printf("D_%d 0x%I32X\n", (i+1), Dn[i+1]);
	}

	// subkey calculation and permutation
	for(i = 0; i < 16; i++)
	{
		cnBuffer = Cn[i+1]; // left part of pre-permuted key copied to buffer value
		cnBuffer = (cnBuffer << 32); // align the value to left part of buffer
		dnBuffer = Dn[i+1]; // right part of pre-permuted key copied to buffer value
		dnBuffer = (dnBuffer << 4); // align the value to right part of buffer
		preSubKey = (cnBuffer | dnBuffer); // unite left and right buffer parts and get pre-permuted key

		// key permutation with PC-2 matrix
		for(j = 0; j < 48; j++)
		{
			bitShift_Buffer = 0x8000000000000000; // inititial value for big endian bit shifting
			bitShift_Buffer = (bitShift_Buffer >> (PC_2[j]-1)); // shift the buffer value according to PC_1 matrix
			bitShift_Buffer = bitShift_Buffer & (preSubKey); // find the related bit value of pre-permuted key
			bitShift_Buffer = (bitShift_Buffer << (PC_2[j]-1));	// revoke the shifting process
			bitShift_Buffer = (bitShift_Buffer >> j);	// shift buffer value according to permuted key bit number

			Sub_Keys[i] = (Sub_Keys[i] | bitShift_Buffer); // add calculated bit value to related permuted key bit
		}

		//printf("K_%d 0x%I64X\n", (i+1), Sub_Keys[i]);
	}

} // Get_Subkeys Function



/**
  * @brief  this function is used for left circular bit shifting of 28 bit Big Endian DES subkey left and right parts
  * @param  value
  * @param  shiftValue
  * @retval buffer
  */
uint32_t DES_Subkey_BitShifter(uint32_t value, uint8_t shiftValue)
{
	uint32_t buffer = 0x00000000; // buffer value for circular left bitshifting process

	buffer = (value << shiftValue) | ((value >> (32 - shiftValue)) << 4); // circular left bitshifting

	return buffer;
} // DES_Subkey_BitShifter Function


/**
  * @brief  this function is used for encode the 64bits block of data
  * @param  plainData
  * @retval encodedData
  */
uint64_t DES_Encode_BlockData(uint64_t plainData)
{
	uint64_t encodedData = 0x0000000000000000; // 64 bit variable for return the encoded data
	uint64_t bitShift_Buffer = 0x0000000000000000; // buffer value
	uint64_t permutedData = 0x0000000000000000;
	uint64_t pre_PermutedData = 0x0000000000000000;
	uint32_t ln = 0x00000000; // 32 bit left part of permuted data
	uint32_t ln_Old = 0x00000000; // 32 bit left part of previous iteration of permuted data
	uint32_t rn = 0x00000000; // 32 bit right part of permuted data
	uint32_t rn_Old = 0x00000000; // 32 bit right part of previous iteration of permuted data
	uint8_t i = 0; // general purpose sentinel


	// initial plain data permutation with IP matrix (to get M+)
	for(i = 0; i < 64; i++)
	{
		bitShift_Buffer = 0x8000000000000000; // inititial value for big endian bit shifting
		bitShift_Buffer = (bitShift_Buffer >> (IP[i]-1)); // shift the buffer value according to PC_1 matrix
		bitShift_Buffer = bitShift_Buffer & (plainData); // find the related bit value of original key
		bitShift_Buffer = (bitShift_Buffer << (IP[i]-1)); // revoke the shifting process
		bitShift_Buffer = (bitShift_Buffer >> i);	// shift buffer value according to permuted key bit number

		encodedData = (encodedData | bitShift_Buffer); // add calculated bit value to related permuted key bit
	}

	//printf("M+ 0x%I64X\n", encodedData);

	// permuted data separation (left and right parts)
	ln_Old = (0xFFFFFFFF00000000 & encodedData) >> 32; // L0
	rn_Old = (0x00000000FFFFFFFF & encodedData); // R0

	//printf("L0 0x%I32X\n", ln_Old);
	//printf("R0 0x%I32X\n", rn_Old);

	// 16 times iteration of permuted data parts with F function
	for(i = 0; i < 16; i++)
	{
		ln = rn_Old;
		rn = ln_Old ^ DES_F_Function(rn_Old, i);

		// new values become old values for next iteration
		rn_Old = rn;
		ln_Old = ln;
	}


	pre_PermutedData = rn_Old; // copy Right part vaule to buffer
	pre_PermutedData = (pre_PermutedData << 32); // align right part to Left side of buffer (according to algorithm)
	pre_PermutedData = (pre_PermutedData | ln_Old); // add Left part of data to Right side of buffer

	//printf("F  0x%I64X\n", encodedData);

	// final permutation of DES with IP^-1 matrix
	for(i = 0; i < 64; i++)
	{
		bitShift_Buffer = 0x8000000000000000; // inititial value for big endian bit shifting
		bitShift_Buffer = (bitShift_Buffer >> (IP_[i]-1)); // shift the buffer value according to IP^-1 matrix
		bitShift_Buffer = bitShift_Buffer & (pre_PermutedData); // find the related bit value of original key
		bitShift_Buffer = (bitShift_Buffer << (IP_[i]-1)); // revoke the shifting process
		bitShift_Buffer = (bitShift_Buffer >> i); // shift buffer value according to permuted key bit number

		permutedData = (permutedData | bitShift_Buffer); // add calculated bit value to related permuted key bit
	}

	encodedData = permutedData; // copy buffer value to

	//printf("Encrypted Data  0x%I64X\n", encodedData);

	return encodedData;
} // DES_Encode_BlockData function


/**
  * @brief  this function is used for decode the 64bits block of data
  * @param  plainData
  * @retval encodedData
  */
uint64_t DES_Decode_BlockData(uint64_t plainData)
{
	uint64_t decodedData = 0x0000000000000000; // 64 bit variable for return the decoded data
	uint64_t bitShift_Buffer = 0x0000000000000000; // buffer value
	uint64_t pre_PermutedData = 0x0000000000000000;
	uint64_t permutedData = 0x0000000000000000;
	uint32_t ln = 0x00000000;	// 32 bit left part of permuted data
	uint32_t ln_Old = 0x00000000; // 32 bit left part of previous iteration of permuted data
	uint32_t rn = 0x00000000;	// 32 bit right part of permuted data
	uint32_t rn_Old = 0x00000000; // 32 bit right part of previous iteration of permuted data
	uint8_t i = 0; // general purpose sentinel


	// initial plain data permutation with IP matrix (to get M+)
	for(i = 0; i < 64; i++)
	{
		bitShift_Buffer = 0x8000000000000000; // inititial value for big endian bit shifting
		bitShift_Buffer = (bitShift_Buffer >> (IP[i]-1)); // shift the buffer value according to IP matrix
		bitShift_Buffer = bitShift_Buffer & (plainData); // find the related bit value of original key
		bitShift_Buffer = (bitShift_Buffer << (IP[i]-1)); // revoke the shifting process
		bitShift_Buffer = (bitShift_Buffer >> i); // shift buffer value according to permuted key bit number

		decodedData = (decodedData | bitShift_Buffer); // add calculated bit value to related permuted key bit
	}

	//printf("M+ 0x%I64X\n", encodedData);

	// permuted data separation (left and right parts)
	ln_Old = (0xFFFFFFFF00000000 & decodedData) >> 32; // L0
	rn_Old = (0x00000000FFFFFFFF & decodedData); // R0

	//printf("L0 0x%I32X\n", ln_Old);
	//printf("R0 0x%I32X\n", rn_Old);

	DES_F_Function(rn_Old, 0);

	// 16 times iteration of permuted data parts with F function
	for(i = 0; i < 16; i++)
	{
		ln = rn_Old;
		rn = ln_Old ^ DES_F_Function(rn_Old, (15-i));

		rn_Old = rn;
		ln_Old = ln;
	}


	pre_PermutedData = rn_Old; // copy Right part vaule to buffer
	pre_PermutedData = (pre_PermutedData << 32); // align right part to Left side of buffer (according to algorithm)
	pre_PermutedData = (pre_PermutedData | ln_Old); // aff Left part of data to Right side of buffer

	decodedData = pre_PermutedData; // copy buffer to encoded data

	//printf("F  0x%I64X\n", encodedData);

	// final permutation of DES
	for(i = 0; i < 64; i++)
	{
		bitShift_Buffer = 0x8000000000000000; // inititial value for big endian bit shifting
		bitShift_Buffer = (bitShift_Buffer >> (IP_[i]-1)); // shift the buffer value according to IP^-1 matrix
		bitShift_Buffer = bitShift_Buffer & (decodedData); // find the related bit value of original key
		bitShift_Buffer = (bitShift_Buffer << (IP_[i]-1)); // revoke the shifting process
		bitShift_Buffer = (bitShift_Buffer >> i); // shift buffer value according to permuted key bit number

		permutedData = (permutedData | bitShift_Buffer); // add calculated bit value to related permuted key bit
	}

	decodedData = permutedData; // copy buffer value to

	//printf("Decoded Data  0x%I64X\n", decodedData);

	return decodedData;
}

/**
  * @brief  DES f function calculation routine
  * @param  input
  * @param  iterationNumber
  * @retval result
  */
uint32_t DES_F_Function(uint32_t input, uint8_t iterationNumber)
{
	uint32_t result = 0x00000000;
	uint32_t resultBuffer = 0x00000000;
	uint32_t bitShift_Buffer32 = 0x00000000;
	uint64_t expandedInput = 0x0000000000000000;
	uint64_t inputBuffer = 0x0000000000000000;
	uint64_t bitShift_Buffer = 0x0000000000000000;
	uint64_t B_Buffer = 0x0000000000000000;

	uint8_t i = 0;

	uint8_t S_Row = 0;
	uint8_t S_Column = 0;

	// 32bits to 48bits Expansion routine
	for(i = 0; i < 48; i++)
	{
		bitShift_Buffer = 0x8000000000000000; // inititial value for big endian bit shifting
		inputBuffer = input; // copy input value to 64bit input buffer for expand process
		inputBuffer = (inputBuffer << 32); // align input data to left side of input buffer
		bitShift_Buffer = (bitShift_Buffer >> (E_Bit_Selection_Table[i]-1)); // shift the buffer value according to E_Bit_Selection_Table
		bitShift_Buffer = (bitShift_Buffer & inputBuffer); // find the related bit value of original key
		bitShift_Buffer = (bitShift_Buffer << (E_Bit_Selection_Table[i]-1)); // revoke the shifting process
		bitShift_Buffer = (bitShift_Buffer >> i);	// shift buffer value according to permuted key bit number

		expandedInput = (expandedInput | bitShift_Buffer); // add calculated bit value to related expanded key bit
	} // (i = 0; i < 48; i++)

	//printf("E 0x%I64X\n", expandedInput);

	expandedInput = (expandedInput ^ Sub_Keys[iterationNumber]); // XOR function with 48bit expanded input and Kn

	//printf("E^Kn 0x%I64X\n", buffer);


	/* 8x6 bit B variable separation, 6bits to 4bits S variable transformation with S-Boxes
	 * and get 32 bit pre-permuted f function output */
	for(i = 0; i < 8; i++)
	{
		B_Buffer = 0xFC; // buffer initialization for bit calculations (0b11111100)
		B_Buffer = (B_Buffer << 56); // align buffer data to left (Big Endian)

		B_Buffer = (B_Buffer >> (i*6)); // align buffer data according to iteration number of 6 bit values
		B_Buffer = ((expandedInput & B_Buffer) >> (56 - (i*6))); // get related 6 bit value and align it to last 8 bit according to (Big Endian)

		// S-Box row adress calculating routine with first and last bits of 6 bits related B value
		switch(B_Buffer & 0x84) // 0b10000100
		{
			case 0x00: // 0b00000000
					S_Row = 0;
				break;

			case 0x04: // 0b00000100
					S_Row = 1;
				break;

			case 0x80: // 0b10000000
					S_Row = 2;
				break;

			case 0x84: // 0b10000100
					S_Row = 3;
				break;

			default:
					// this line intentionally left blank
				break;
		}

		// S-Box column adress calculating routine with middle 4bits of 6bit related B value
		S_Column = ((B_Buffer & 0x78) >> 3); // 0b01111000

		resultBuffer = 0x00000000; // clear result buffer
		resultBuffer = SBox[i][S_Row][S_Column]; // get related S-Box value
		resultBuffer = (resultBuffer << (28 - (4*i))); // shift bits to proper 4bit S value position on result

		result = (result | resultBuffer); // add related 4bit S value to result parameter

	} // for(i = 0; i < 8; i++)

	//printf("Result 0x%I32X\n", result);

	resultBuffer = result; // copy result value to buffer value
	result = 0x00000000; // clear result value

	// final permutation of F function result with P matrix
	for(i = 0; i < 32; i++)
	{
		bitShift_Buffer32 = 0x80000000;	// initialize the value to big endian bit shifting
		bitShift_Buffer32 = (bitShift_Buffer32 >> (P[i]-1)); // align bit according to P matrix
		bitShift_Buffer32 = (bitShift_Buffer32 & resultBuffer); // get related bit value from pre permuted data
		bitShift_Buffer32 = (bitShift_Buffer32 << (P[i]-1)); // revoke shifting process
		bitShift_Buffer32 = (bitShift_Buffer32 >> i); // align the bit value according to related position of result data

		result = (result | bitShift_Buffer32); // add value to result data
	}

	//printf("Result 0x%I32X\n", result);

	return result;
}




