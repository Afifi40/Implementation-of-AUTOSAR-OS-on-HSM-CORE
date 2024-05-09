/*
 * main.c
 *
 *  Created on: Feb 10, 2023
 *      Author: Ahmed Afifi
 */


#include "task.h"
#include "resource.h"


void main(void){
	resource_initialize();
	task_initialize();
	while(1){
		__nop();
		__nop();
		__nop();
		__nop();
		__nop();
		__nop();
		__nop();
		__nop();
	}
}