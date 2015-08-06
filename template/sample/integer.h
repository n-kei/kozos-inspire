/*-------------------------------------------*/
/* Integer type definitions for FatFs module */
/*-------------------------------------------*/

#ifndef _INTEGER
#define _INTEGER

#include "defines.h"

/* These types must be 16-bit, 32-bit or larger integer */
typedef int16       INT;
typedef uint16      UINT;

/* These types must be 8-bit integer */
typedef int8        CHAR;
typedef uint8       UCHAR;
typedef uint8       BYTE;

/* These types must be 16-bit integer */
typedef int16       SHORT;
typedef uint16      USHORT;
typedef uint16      WORD;
typedef uint16      WCHAR;

/* These types must be 32-bit integer */
typedef int32       LONG;
typedef uint32      ULONG;
typedef uint32      DWORD;

#endif
