/*
 * Copyright(C) 2001 by Fuji Xerox Co.Ltd.All rights reserved.
 * 
 * File: IMG_Assert.h - Assertionマクロの定義
 * Yozo Kashima 10.Aug.2001
 *
 */

#ifndef INC_IMG_Assert_h
#define INC_IMG_Assert_h

#include "IMG_Context.h"

#ifdef NDEBUG

#define IMG_ASSERT(context,Expression,ret)
#define IMG_REQUIRE_VALID_OBJECT(className,obj,ret)

/* NDEBUG */
#else

#define IMG_ASSERT(context,Expression,ret)	\
		if (!(Expression)) { \
			IMG_Context_WriteLog( \
				context, \
				"REQUIRE(%s) failed\n" \
				" file = %s\n" \
				" line = %d\n", \
				#Expression, __FILE__, __LINE__); \
			IMG_Context_Fail(context);	\
			return ret; \
		}


#define IMG_REQUIRE_VALID_OBJECT(className,obj,ret)	\
		{ \
			IMG_ASSERT(IMG_NULL, (obj) != IMG_NULL && (obj)->context != IMG_NULL, ret); \
			IMG_ASSERT((obj)->context,className##_IsValid((obj)),ret); \
		}

/* NDEBUG */
#endif
 
/* INC_IMG_Assert_h */
#endif

/*
 * Log
 * 10.Aug.2001 Yozo Kashima Created
 * 17.Sep.2001 Yozo Kashima NDEBUGがdefineされている時はASSERTIONをはずす。
 */

/* end of IMG_Assert.h */
