/*
 * Copyright (C) Fuji Xerox Co; Ltd. 2002. All rights reserved.
 * OL_Common.h
 *
 * log:
 * Created:        Sep 24, 2002 By Kunihiko Kobayashi 
 * Modified:       
 *
 */


#ifndef _OL_COMMON_H_INCLUDED_
#define _OL_COMMON_H_INCLUDED_

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <float.h>
#include <math.h>

#include "OL_Config.h"
#include "OL_Types.h"
#include "OL_TypesExt.h"
#include "OL_Error.h"


#define OL_ABS(A)			(((A) > 0)? (A): -(A))
#define OL_MIN(A, B)			(((A) > (B))? (B): (A))
#define OL_MAX(A, B)			(((A) > (B))? (A): (B))
#define OL_ROUND(A)			((int)(((A) > 0)? ((A) + 0.5): ((A) - 0.5)))


#endif //_OL_COMMON_H_INCLUDED_
