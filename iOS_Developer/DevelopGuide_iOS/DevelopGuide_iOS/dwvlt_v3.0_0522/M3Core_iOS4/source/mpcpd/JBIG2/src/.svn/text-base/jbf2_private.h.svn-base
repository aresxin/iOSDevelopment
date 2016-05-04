/*
 * Copyright (c) 2001-2002 by Fuji Xerox Co., Ltd. All rights reserved.
 *
 * $Id: jbf2_private.h,v 1.4 2009/12/22 08:11:16 chikyu Exp $
 */

#ifndef JBF2_PRIVATE_H
#define JBF2_PRIVATE_H

#define RETURN_IF(cond)			{ if (cond) return; }
#define RETURN_VALUE_IF(cond, value)	{ if (cond) return (value); }

#define MAX(x,y)	((x) > (y) ? (x) : (y))
#define MIN(x,y)	((x) < (y) ? (x) : (y))
#define CLAMP(x,l,h)	((x) < (l) ? (l) : (x) > (h) ? (h) : (x))

#define HI(x)		((x) >> 16)
#define LO(x)		((x) & 0xffff)

#define MASK(x)		((0xffffffff >> (31 - HI(x) + LO(x))) << LO (x))
#define BITFIELD(s, e)	(((e) << 16) | (s))
#define GET_BITFIELD(flags, bf) \
			(((flags) & MASK (bf)) >> LO (bf))
#define SET_BITFIELD(flags, bf, value) \
			(flags = ((flags) & ~MASK (bf)) | \
				 (((value) << LO (bf)) & MASK (bf)))

#endif /* JBF2_PRIVATE_H */

