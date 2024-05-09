/*
 * File Name: resource.c
 * Date: 19/4/2023
 * author: Esraa Ahmed Taha
 */
 
/*
 *	Resource management features
 */

#include "osek_kernel.h"
#include "check.h"
#include "task.h"
#if RES_COUNT !=0 
//#include "interrupt.h"
#include "resource.h"

/*
 *  Initializing Resource Management Functions
 */
 
void
resource_initialize(void)
{
	ResourceType	resid;

	for (resid = 0; resid < RES_COUNT; resid++) {
		rescb_prevpri[resid] = TPRI_NULL;		
	}
}
#endif
//Handel Sch is being resource 