/*
 * Copyright(C) 2001 by Fuji Xerox Co.Ltd.All rights reserved.
 * 
 * File: IMG_Builtin.h - last edit
 * Yozo Kashima 02.Apr.2001
 *
 */

#ifndef INC_IMG_Builtin_h
#define INC_IMG_Builtin_h

/*
 * 組み込み型
 */
typedef signed char		IMG_INT8;	/* 符号ありの8ビット整数 */
typedef signed short	IMG_INT16;	/* 符号ありの16ビット整数 */
typedef signed int		IMG_INT32;	/* 符号ありの32ビット整数 */
typedef unsigned char	IMG_UINT8;	/* 符号なしの8ビット整数 */
typedef unsigned short	IMG_UINT16; /* 符号なしの16ビット整数 */
typedef unsigned int	IMG_UINT32; /* 符号なしの32ビット整数 */

typedef IMG_UINT8		IMG_BOOL;	/* ブール型 */
#define IMG_TRUE		1
#define IMG_FALSE		0

#define IMG_NULL		0			/* NULL値 */

#if !defined(HB_USE_FIXEDPOINT)
/* 浮動小数点使用(デフォルト)	*/
#include <float.h>
typedef float			IMG_FLOAT;  /* 32ビット浮動小数点型 */
typedef double			IMG_DOUBLE; /* 64ビット浮動小数点型 */
typedef float			IMG_REAL32; /* 32ビット実数型		*/
typedef double			IMG_REAL64; /* 64ビット実数型		*/
#if !defined(HB_WINDRAW_ADJUST)
typedef float			IMG_SHOULDBE_DOUBLE;	/* 今floatだけど本来doubleであるべき	*/
#else
typedef double			IMG_SHOULDBE_DOUBLE;
#endif

#define	IMG_FLT_EQ(a,b)		(fabs((a)-(b)) < FLT_EPSILON)
#define IMG_FLT_NE(a,b)		(fabs((a)-(b)) >= FLT_EPSILON)
#define IMG_FLT_EQ_ZERO(a)	(fabs(a) < FLT_EPSILON)
#define IMG_FLT_NE_ZERO(a)	(fabs(a) >= FLT_EPSILON)
#define IMG_FLT_IS_PLUS(a)	((a) > 0)
#define IMG_FLT_IS_MINUS(a)	((a) < 0)
#define IMG_FLT_GE_ZERO(a)	((a) >= FLT_EPSILON)
#define IMG_FLT_LE_ZERO(a)	((a) <= FLT_EPSILON)

#define IMG_FLT_MAX		FLT_MAX
#define IMG_REAL32_MAX		FLT_MAX
#define IMG_CONST_0_5		0.5

#else
/* 固定小数点使用	*/
#include "COM_HB_Fixed.h"
typedef float			IMG_FLOAT;  /* 32ビット浮動小数点型 */
typedef double			IMG_DOUBLE; /* 64ビット浮動小数点型 */
typedef HB_Fixed32		IMG_REAL32; /* 32ビット実数型		*/
typedef HB_Fixed64		IMG_REAL64; /* 64ビット実数型		*/
typedef HB_Fixed64		IMG_SHOULDBE_DOUBLE;	/* 今floatだけど本来doubleであるべき	*/

#define	IMG_FLT_EQ(a,b)		((a) == (b))
#define IMG_FLT_NE(a,b)		((a) != (b))
#define IMG_FLT_EQ_ZERO(a)	((a) == 0)
#define IMG_FLT_NE_ZERO(a)	((a) != 0)
#define IMG_FLT_IS_PLUS(a)	((a) > 0)
#define IMG_FLT_IS_MINUS(a)	((a) < 0)
#define IMG_FLT_GE_ZERO(a)	((a) >= 0)
#define IMG_FLT_LE_ZERO(a)	((a) <= 0)

#define IMG_FLT_MAX		FLT_MAX
#define IMG_REAL32_MAX		HB_FIXED32_CONST_MAX
#define IMG_CONST_0_5		HB_FIXED32_CONST_0_5

#endif	/* HB_USE_FIXEDPOINT	*/

#endif /* INC_IMG_Builtin_h */

/*
 * Log
 * 02.Apr.2001 Yozo Kashima Created
 */

/* end of IMG_Builtin.h */
