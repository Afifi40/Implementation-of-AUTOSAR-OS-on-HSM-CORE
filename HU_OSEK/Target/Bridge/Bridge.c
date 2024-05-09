/*
 * Bridge.c
 *
 *  Created on: May 12, 2023
 *  Author: Kadry, Esraa
 */


#include "Bridge.h"

UINT32 buffer [10][No_of_bytes];
int front=0;
int rear=0;

/*void (*isr_handler)(UINT8); //Function pointer to a function that returns void and takes UINT8 as a parameter
void set_bridge_Call( void (*fun_ptr)(UINT8)){
	isr_handler = fun_ptr;
}*/

void init_bridge(){
	Bridge.HT2HSMIE = 1;
}

/**BRIDGE ERROR HANDLERS**/

//TODO: Implement Bridge Error Handlers

/**BRIDGE Handler**/

UINT32* get_bridge_buffer (void){
	if (front != rear)
	{
		UINT32* temp = buffer[front];
		front = ++front % 10;
		return temp;
	}
		return 0;
}

void send_bridge_buffer (UINT32 * data){
	Bridge.HSM2HTS= (UINT32) data; 
	Bridge.HSM2HTF= 1;
}

void BridgeSV_Handler_ISR (void){
	 
	UINT32 *mem =(UINT32 *) Bridge.HT2HSMS;
	for (int i=0 ; i<No_of_bytes ;i++)
		buffer[rear][i]= mem[i];

	rear = ++rear % 10;
}


#if 0

Bridge_Handler{
	isr_handler(IRQ_Number);
}

#endif


