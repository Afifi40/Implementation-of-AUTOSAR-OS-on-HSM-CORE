/*
 * bridgeHeader.h
 *
 *  Created on: May 12, 2023
 *  Author: Afifi, Kadry, Esraa
 */

#ifndef BRIDGE_MANAGEMENT_BRIDGEHEADER_H_
#define BRIDGE_MANAGEMENT_BRIDGEHEADER_H_

#include "../osek_kernel.h"
#include "../check.h"
#include "../Target/Bridge/Bridge.h"

#ifndef NULL
#define	NULL			((void *) 0)
#endif

void SendData(UINT32* p);
UINT32* GetData (void);

//void init_bridge_isr();
//void CallBridge(BridgeIntType);

#endif /* BRIDGE_MANAGEMENT_BRIDGEHEADER_H_ */
