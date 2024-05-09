
#ifndef _CHECK_H_
#define _CHECK_H_

#include "inc/kernel_cfg.h"
extern UINT8 callevel;
/** \brief Get Context at Calling point
 **
 ** This macro returns the actual context
 **
 ** \returns the actual context
 **/
#define GetCallingLevel()   (callevel)

/** \brief Set Context
 **
 ** Set the context
 **
 ** \param[in] newcontext valid values are:
 **               - CONTEXT_INVALID
 **               - CONTEXT_TASK
 **               - CONTEXT_ISR1
 **               - CONTEXT_ISR2
 **/
#define SetCallingLevel(NEWCALL)	callevel = (NEWCALL);

#ifdef EXTENDED_STATUS

#define CHECK_ACCESS(exp) do {			\
	if (!(exp)) {						\
		ercd = E_OS_ACCESS;				\
		goto error_exit;				\
	}									\
} while (0)

#define CHECK_CALLEVEL(clmask) do {		\
	if ((callevel & (clmask)) == 0) {	\
		ercd = E_OS_CALLEVEL;			\
		goto error_exit;				\
	}									\
} while (0)

#define CHECK_TSKID(tskid) do {			\
	if (!(tskid < TASK_COUNT)) {			\
		ercd = E_OS_ID;					\
		goto error_exit;				\
	}									\
} while (0)

#define CHECK_RESID(resid) do {			\
	if (!(resid < RES_COUNT)) {		\
		ercd = E_OS_ID;					\
		goto error_exit;				\
	}									\
} while (0)

#define CHECK_CNTID(cntid) do {			\
	if (!(cntid < COUNTER_COUNT)) {		\
		ercd = E_OS_ID;					\
		goto error_exit;				\
	}									\
} while (0)

#define CHECK_ALMID(almid) do {			\
	if (!(almid < ALARMS_COUNT)) {		\
		ercd = E_OS_ID;					\
		goto error_exit;				\
	}									\
} while (0)

#define CHECK_NOFUNC(exp) do {			\
	if (!(exp)) {						\
		ercd = E_OS_NOFUNC;				\
		goto error_exit;				\
	}									\
} while (0)

#define CHECK_RESOURCE(exp) do {		\
	if (!(exp)) {						\
		ercd = E_OS_RESOURCE;			\
		goto error_exit;				\
	}									\
} while (0)

#define CHECK_STATE(exp) do {			\
	if (!(exp)) {						\
		ercd = E_OS_STATE;				\
		goto error_exit;				\
	}									\
} while (0)

#define CHECK_VALUE(exp) do {			\
	if (!(exp)) {						\
		ercd = E_OS_VALUE;				\
		goto error_exit;				\
	}									\
} while (0)

#else /* EXTENDED_STATUS */

#define CHECK_ACCESS(exp)		((void) 0)
#define CHECK_CALLEVEL(clmask)	((void) 0)
#define CHECK_TSKID(tskid)		((void) 0)
#define CHECK_RESID(resid)		((void) 0)
#define CHECK_CNTID(cntid)		((void) 0)
#define CHECK_ALMID(almid)		((void) 0)
#define CHECK_NOFUNC(exp)		((void) 0)
#define CHECK_RESOURCE(exp)		((void) 0)
#define CHECK_VALUE(exp)		((void) 0)

#endif /* EXTENDED_STATUS */
#endif /* _CHECK_H_ */
