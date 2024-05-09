/*
 * bridge.c
 *
 *  Created on: May 12, 2023
 *  Author: Afifi, Kadry, Esraa
 */




#include "../Bridge_Management/bridgeHeader.h"
//#include "../Target/Timer_HW/std_macros.h "

UINT32* GetData (void){
	UINT32 *ptr = get_bridge_buffer();
	return ptr;
}

void SendData(UINT32* p)
{
	send_bridge_buffer(p);
}

/*void init_bridge_isr(){

	set_bridge_Call(CallBridge);
}
void bridge_init(void)
{



}
void CallBridge(BridgeIntType bridgeIntID)
{
	switch(brdgini_act[bridgeIntID]) check alarm actions for expire 
	{
		case INCREMENT:
			IncrementCounter(brdgini_actInfo[bridgeIntID].Counter);
			break;

		case ACTIVATETASK:
			ActivateTask(brdgini_actInfo[bridgeIntID].TaskID);
			break;

		case CALLBACK:
			if(brdgini_actInfo[bridgeIntID].CallbackFunction != NULL)
				brdgini_actInfo[bridgeIntID].CallbackFunction();
			break;

		case SETEVENT:
			SetEvent(brdgini_actInfo[bridgeIntID].Ev.TaskID, brdgini_actInfo[bridgeIntID].Ev.Event);
			break;

		default:
			 possibly TODO, report an error 
			break;

	}
}*/




