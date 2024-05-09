
#ifndef _OSEK_H_
#define _OSEK_H_
//#include <assert.h>

#define	Inline		static inline


typedef	signed char			INT8;
typedef	unsigned char		UINT8;
#define UINT8_INVALID		((UINT8)(~0u))

typedef unsigned char		BOOL;

typedef	signed short		INT16;
typedef	unsigned short		UINT16;
#define UINT16_INVALID		((UINT16)(~0u))


typedef	signed long			INT32;
typedef	unsigned long		UINT32;
#define UINT32_INVALID		((UINT32)(~0u))

typedef	signed long	long 	INT64;
typedef	unsigned long long	UINT64;
#define UINT64_INVALID		((UINT64)(~0u))

typedef UINT8		StatusType;
#define	E_OK		((StatusType) 0)

#define TRUE		((BOOL) 1)
#define FALSE		((BOOL) 0)

#endif /*_OSEK_H_*/
