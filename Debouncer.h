/*
 * Debouncer.h
 *
 *  Created on: Mar 31, 2018
 *      Author: samir
 */

#ifndef DEBOUNCER_H_
#define DEBOUNCER_H_

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned long uint32;




//////////////////////////////////////////////
#define TOTAL_PIN_BUTTONS 					 4
#define TOTAL_STORE_VALUES                   4		
#define CHECK_TIME                    0x200000

#define PTB0						  (1 << 0)
#define PTB1						  (1 << 2)
#define PTB2						  (1 << 3)
#define PTB3						  (1 << 17)

#define   TABLE_MASKS_PINS                  \
	{PTB0,PTB1,PTB2,PTB3}					 \
		
uint32 vFun_Debouncer(uint32 u32_BtnsPort);
uint32 vFun_CheckStatePin(uint32 u32_Port_Debounced,uint8 u8_Pin);

#endif /* DEBOUNCER_H_ */
