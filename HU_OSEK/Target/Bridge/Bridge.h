/*
 * Bridge.h
 *
 *  Created on: May 12, 2023
 *  Author: Kadry, Esraa
 */





#ifndef TARGET_BRIDGE_BRIDGE_H_
#define TARGET_BRIDGE_BRIDGE_H_

#include "../../inc/kernel.h"
/** REGISTER SECTION **/
//TODO: #define different registers with their addresses

#define No_of_bytes 4

#define Bridge (*(volatile Bridge_strct*)0xF0040000)
UINT32* get_bridge_buffer (void);
void send_bridge_buffer(UINT32 *);
void init_bridge(void);

typedef struct {

    UINT32 res0[2];
    UINT32 HSM_ID;
    UINT32 res1[5];
    UINT32 HT2HSMF;
    UINT32 HT2HSMIE;
    UINT32 HSM2HTF;
    UINT32 HSM2HTIE;
    UINT32 HSM2HTIS;
    UINT32 HSM2HTS;
    UINT32 HT2HSMS;

}Bridge_strct;



//void set_bridge_Call( void (*fun_ptr)(UINT8));

#endif /* TARGET_BRIDGE_BRIDGE_H_ */
