#ifndef _PUB_MACRO_H
#define _PUB_MACRO_H

typedef unsigned char UINT8;
typedef char INT8;
typedef unsigned short UINT16;
typedef short INT16;
typedef unsigned int UINT32;
typedef int INT32;
typedef long long INT64;
typedef unsigned long long UINT64;
typedef void VOID;

#define true	1
#define false   0
#define PUB_PRINT		printf
#define RESULT_TRUE		true
#define RESULT_FALSE	false
#define PUB_PTR_IS_NULL(p)  ((p) == NULL ? RESULT_TRUE : RESULT_FALSE )

#endif

