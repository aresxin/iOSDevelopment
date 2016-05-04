/*
 * Copyright (c) 2001-2002 by Fuji Xerox Co., Ltd. All rights reserved.
 *
 * $Id: jbf2_generic.h,v 1.4 2009/12/22 08:11:18 chikyu Exp $
 */

#ifndef JBF2_GENERIC_H
#define JBF2_GENERIC_H

#include "jbf2_bitmap.h"

#define JBF2_GENERIC(x) ((JBF2Generic*)(x))
typedef struct _JBF2Generic JBF2Generic;

JBF2Generic	*jbf2_generic_new		(JBF2Error	*error);
void		 jbf2_generic_free		(JBF2Generic	*generic);
void		 jbf2_generic_read_header	(JBF2Generic	*generic,
						 JBF2IO		*io);
void		 jbf2_generic_read_data		(JBF2Generic	*generic,
						 JBF2UInt32	 data_length,
						 JBF2IO		*io);
JBF2Bitmap	*jbf2_generic_get_bitmap	(JBF2Generic	*generic);

#endif /* JBF2_GENERIC_H */
