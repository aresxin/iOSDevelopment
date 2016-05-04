/*
 * Copyright (c) 2001-2002 by Fuji Xerox Co., Ltd. All rights reserved.
 *
 * $Id: jbf2_types.h,v 1.4 2009/12/22 08:11:17 chikyu Exp $
 */

#ifndef JBF2_TYPES_H
#define JBF2_TYPES_H

/* Some compiler seems to dislike bit-field. */
/* #define JBF2_DISABLE_BITFIELD */

enum {
	JBF2_FALSE,
	JBF2_TRUE
};

/* Type conversion macros */

#define JBF2_UINT(x)	((JBF2UInt*)(x))
#define JBF2_UINT8(x)	((JBF2UInt8*)(x))
#define JBF2_UINT16(x)	((JBF2UInt16*)(x))
#define JBF2_UINT32(x)	((JBF2UInt32*)(x))
#define JBF2_INT(x)	((JBF2Int*)(x))
#define JBF2_INT8(x)	((JBF2Int8*)(x))
#define JBF2_INT16(x)	((JBF2Int16*)(x))
#define JBF2_INT32(x)	((JBF2Int32*)(x))
#define JBF2_POINTER(x)	((JBF2Pointer)(x))
#define JBF2_BOOL_XDEAN(x)	((JBF2Boolean*)(x))
#define JBF2_FUNC1(x)	((JBF2Func1)(x))
#define JBF2_FUNC2(x)	((JBF2Func2)(x))
#define JBF2_COMPARE(x)	((JBF2Compare)(x))

/* Basic types */

typedef unsigned int	 JBF2UInt;	/* >= 16 bits */
typedef unsigned char	 JBF2UInt8;	/* ==  8 bits */
typedef unsigned short	 JBF2UInt16;	/* >= 16 bits */
typedef unsigned int	 JBF2UInt32;	/* >= 32 bits */
typedef signed int	 JBF2Int;	/* >= 16 bits */
typedef signed char	 JBF2Int8;	/* ==  8 bits */
typedef signed short	 JBF2Int16;	/* >= 16 bits */
typedef signed int	 JBF2Int32;	/* >= 32 bits */
typedef void		*JBF2Pointer;
typedef unsigned int	 JBF2Boolean;	/* 0 or !0    */
typedef void		(*JBF2Func1)	(JBF2Pointer data);
typedef void		(*JBF2Func2)	(JBF2Pointer data, JBF2Pointer user_data);
typedef JBF2Boolean	(*JBF2Compare)	(JBF2Pointer data, JBF2Pointer user_data);

typedef enum {
	JBF2_OR,
	JBF2_AND,
	JBF2_XOR,
	JBF2_XNOR,
	JBF2_REPLACE
} JBF2Operator;

typedef enum {
	JBF2_BOTTOMLEFT,
	JBF2_TOPLEFT,
	JBF2_BOTTOMRIGHT,
	JBF2_TOPRIGHT
} JBF2Corner;

#endif /* JBF2_TYPES_H */

