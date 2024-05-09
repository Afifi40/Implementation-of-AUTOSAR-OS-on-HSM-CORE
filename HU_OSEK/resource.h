/*
 * File Name: resource.h
 * Date: 19/4/2023
 * author: Esraa Ahmed Taha
 */

/*
 *	Resource management features
 */

#ifndef _RESOURCE_H_
#define _RESOURCE_H_
#include "inc/kernel_cfg.h"
#if (RES_COUNT != 0)
extern const Priority		resinib_ceilpri[];	/* Upper priority */
extern const ResourceType	resinib_mskres[];	/* Upper priority */
extern Priority				rescb_prevpri[];	/* Priority before resource acquisition */
extern ResourceType			rescb_prevres[];	/* Previously Acquired Resources */

void	resource_initialize(void);
#endif

#endif /* _RESOURCE_H_ */
