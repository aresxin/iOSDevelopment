/*
 * Copyright (c) 2001-2002 by Fuji Xerox Co., Ltd. All rights reserved.
 *
 * $Id: jbf2_bitarray.h,v 1.4 2009/12/22 08:11:17 chikyu Exp $
 */

#ifndef JBF2_BITARRAY_H
#define JBF2_BITARRAY_H

#include "jbf2_error.h"
#include "jbf2_types.h"

#define JBF2_BIT_ARRAY(x) ((JBF2BitArray*)(x))
typedef struct _JBF2BitArray JBF2BitArray;


JBF2BitArray	*jbf2_bitarray_new		(JBF2Error	*error,
						 JBF2UInt32	 length);
void		 jbf2_bitarray_free		(JBF2BitArray	*array);
void		 jbf2_bitarray_resize		(JBF2BitArray	*array,
						 JBF2UInt32	 length);
JBF2UInt32	 jbf2_bitarray_length		(JBF2BitArray	*array);
JBF2Boolean	 jbf2_bitarray_get_nth		(JBF2BitArray	*array,
						 JBF2UInt32	 n);
void		 jbf2_bitarray_set_nth		(JBF2BitArray	*array,
                                        	 JBF2UInt32	 n,
                                        	 JBF2Boolean	 data);
JBF2UInt8	 jbf2_bitarray_get_nth_8	(JBF2BitArray	*array,
					 	 JBF2UInt32	 n);
void		 jbf2_bitarray_set_nth_8	(JBF2BitArray	*array,
                                        	 JBF2UInt32	 n,
                                        	 JBF2UInt8	 data);

#endif /* JBF2_BITARRAY_H */
