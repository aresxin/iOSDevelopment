/*
 * Copyright (c) 2001-2002 by Fuji Xerox Co., Ltd. All rights reserved.
 *
 * $Id: jbf2_array.h,v 1.4 2009/12/22 08:11:17 chikyu Exp $
 */

#ifndef JBF2_ARRAY_H
#define JBF2_ARRAY_H

#include "jbf2_error.h"
#include "jbf2_types.h"

#define JBF2_ARRAY(x) ((JBF2Array*)(x))
typedef struct _JBF2Array JBF2Array;


JBF2Array	*jbf2_array_new 		(JBF2Error	*error,
						 JBF2UInt32	 length);
void		 jbf2_array_free		(JBF2Array	*array);
void		 jbf2_array_resize		(JBF2Array	*array,
						 JBF2UInt32	 length);
void		 jbf2_array_foreach		(JBF2Array	*array,
						 JBF2Func1	 func);
void		 jbf2_array_foreach_with	(JBF2Array	*array,
						 JBF2Func2	 func,
						 JBF2Pointer	 user_data);
JBF2Pointer	 jbf2_array_find		(JBF2Array	*array,
						 JBF2Compare	 func,
						 JBF2Pointer	 user_data);
JBF2UInt32	 jbf2_array_length		(JBF2Array	*array);
JBF2Pointer	 jbf2_array_get_nth		(JBF2Array	*array,
						 JBF2UInt32	 n);
void		 jbf2_array_set_nth		(JBF2Array	*array,
						 JBF2UInt32	 n,
						 JBF2Pointer	 data);

#endif /* JBF2_ARRAY_H */
