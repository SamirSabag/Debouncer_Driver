/*
 * Debouncer.c
 *
 *  Created on: Mar 31, 2018
 *      Author: Samir Sabag Olague.
 *      email: robotsamir@gmail.com
 *      UAG
 */
#include "Debouncer.h"
#include "derivative.h"
uint8 u8_PinCounter          =		 TOTAL_PIN_BUTTONS;
uint8 u8_Cntr_StoreValues    =		 TOTAL_STORE_VALUES;
uint32 u32_CurrentState 		   = 									0;

static volatile uint32 u32_Cntr_Delay 		 =		 		   CHECK_TIME;

static uint32 u32_Port_Btns_Debounced	 = 					        	0;
static uint32 au32_GPIO_States[TOTAL_STORE_VALUES];
uint32 au32_MaskPins[] 		 = 		 TABLE_MASKS_PINS;
uint32 u32_DebouncedPin = 0;

//Note: first configure the pins you are going to use for Read inputs. Use vFun_Inputs_Init


uint32 vFun_Debouncer(uint32 u32_GPIO_Port)
{
		u32_Cntr_Delay--;
		if(!u32_Cntr_Delay)
		{
			u32_Cntr_Delay = CHECK_TIME; 						  	 //Reload  Debouncer time Counter
			au32_GPIO_States[u8_Cntr_StoreValues] =  u32_GPIO_Port;  //Store current Port values
			u8_Cntr_StoreValues--;								  	//Decrement StoreValuesCounter

			if(!u8_Cntr_StoreValues)
			{
				u8_Cntr_StoreValues = TOTAL_STORE_VALUES;     	   //Reload Fetcher Counter index

			  u32_CurrentState = au32_GPIO_States[u8_Cntr_StoreValues];
				while (u32_CurrentState  &&  (u8_Cntr_StoreValues > 0 )  )
				{
					u8_Cntr_StoreValues--;
					u32_CurrentState      &=  au32_GPIO_States[u8_Cntr_StoreValues];
					if(!u8_Cntr_StoreValues)
					{
						if (u32_CurrentState)
						{
								u32_Port_Btns_Debounced ^= u32_CurrentState;
						}
					}
				}
				u8_Cntr_StoreValues = TOTAL_STORE_VALUES;
			}

		}
		return(  u32_Port_Btns_Debounced  );
}

uint32 vFun_CheckStatePin(uint32 u32_Port_Debounced, uint8 u8_Pin)
{
	u32_DebouncedPin = u32_Port_Debounced & (1<<u8_Pin);
	u32_DebouncedPin >>= u8_Pin;
	
	return (u32_DebouncedPin);
}
