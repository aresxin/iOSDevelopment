/*
 * Copyright (C) Fuji Xerox Co; Ltd. 2002. All rights reserved.
 * OL_Types.h
 *
 * log:
 * Created:        Sep 24, 2002 By Kunihiko Kobayashi (Porting from Globe FontServer)
 * Modified:
 *
 */


#ifndef _OL_TYPES_H_INCLUDED_
#define _OL_TYPES_H_INCLUDED_

#include	<float.h>

/************************************************************
  for configurations
  ************************************************************/
#ifdef ON
#	define OL_ON		ON
#else
#	define OL_ON		1
#endif //ON

#ifdef OFF
#	define OL_OFF		OFF
#else
#	define OL_OFF		0
#endif


/************************************************************
  Basic Types
  ************************************************************/

/*
 size based macros
*/
#define	OL_INT8			signed char		
#define OL_INT16		signed short		
#define OL_INT32		signed long
#define OL_UINT8		unsigned char	
#define OL_UINT16		unsigned short	
#define OL_UINT32		unsigned long	
/* #define OL_REAL		double */
#define OL_REAL			float
#define OL_REAL32		float
#define OL_REAL64		double
#define OL_VOID			void		

#define	OL_INT8_SIZE		(sizeof(OL_INT8))
#define OL_INT16_SIZE		(sizeof(OL_INT16))
#define OL_INT32_SIZE		(sizeof(OL_INT32))
#define OL_UINT8_SIZE		(sizeof(OL_UINT8))
#define OL_UINT16_SIZE		(sizeof(OL_UINT16))
#define OL_UINT32_SIZE		(sizeof(OL_UINT32))
#define OL_REAL_SIZE		(sizeof(OL_REAL))
#define OL_REAL32_SIZE		(sizeof(OL_REAL32))
#define OL_REAL64_SIZE		(sizeof(OL_REAL64))
#define OL_VOID_SIZE		(sizeof(OL_VOID))

#define OL_BYTE			unsigned char
#define OL_CHAR			signed char
#define OL_SHORT		signed short
#define OL_USHORT		unsigned short
#define OL_INT			signed int
#define OL_UINT			unsigned int
#define OL_LONG			signed long
#define OL_ULONG		unsigned long
#define OL_FLOAT		float
#define OL_DOUBLE		double

#define OL_BYTE_SIZE		(sizeof(OL_BYTE))
#define OL_CHAR_SIZE		(sizeof(OL_CHAR))
#define OL_SHORT_SIZE		(sizeof(OL_SHORT))
#define OL_USHORT_SIZE		(sizeof(OL_USHORT))
#define OL_INT_SIZE		(sizeof(OL_INT))
#define OL_UINT_SIZE		(sizeof(OL_UINT))
#define OL_LONG_SIZE		(sizeof(OL_LONG))
#define OL_ULONG_SIZE		(sizeof(OL_ULONG))
#define OL_FLOAT_SIZE		(sizeof(OL_FLOAT))
#define OL_DOUBLE_SIZE		(sizeof(OL_DOUBLE))				 

/* types */
#define OL_STATUS		int
#define OL_BOOL			int

#define OL_FONT_ID		unsigned short
#define OL_ENCODING_ID		unsigned short
#define	OL_PIXELUNIT		OL_INT16	
#define	OL_POINTUNIT		OL_REAL
#define OL_BITMAPUNIT		OL_INT8

#define OL_DEC_PATH		unsigned short
#define OL_DEC_TYPE		unsigned short

				 
/* constants */

#define OL_MAX_BYTE		0x7F
#define OL_MAX_SHORT		0x7FFF
#define OL_MAX_LONG		0x7FFFFFFF
#define OL_MAX_USHORT		0xFFFF
#define OL_MAX_ULONG		0xFFFFFFFF
#define OL_MAX_REAL		FLT_MAX

#define OL_MIN_BYTE		0x80
#define OL_MIN_SHORT		0x8000
#define OL_MIN_LONG		0x80000000
#define OL_MIN_USHORT		0x0000
#define OL_MIN_ULONG		0x00000000


#define OL_NEARZERO		0.00001
#define OL_HUNDREDTHS		0.01


#define OL_BOUNDARY_BYTE	sizeof(OL_BYTE)
#define OL_BOUNDARY_CHAR	sizeof(OL_CHAR)
#define OL_BOUNDARY_SHORT	sizeof(OL_SHORT)
#define OL_BOUNDARY_USHORT	sizeof(OL_USHORT)
#define OL_BOUNDARY_INT		sizeof(OL_INT)
#define OL_BOUNDARY_UINT	sizeof(OL_UINT)
#define OL_BOUNDARY_LONG	sizeof(OL_LONG)
#define OL_BOUNDARY_ULONG	sizeof(OL_ULONG)
#define OL_BOUNDARY_FLOAT	sizeof(OL_FLOAT)
#define OL_BOUNDARY_DOUBLE	sizeof(OL_DOUBLE)

#define OL_MEMCPY(S1, S2, N)   memcpy((void*)(S1), (const void*)(S2), (size_t)(N))
#define OL_MEMSET(S, C, N)     memset((void*)(S), (int)(C), (size_t)(N))


/************************************************************
  Macros
  ************************************************************/
#define OL_TRUE			1
#define OL_FALSE		0
#define OL_NULL			0


#endif //_OL_TYPES_H_INCLUDED_

