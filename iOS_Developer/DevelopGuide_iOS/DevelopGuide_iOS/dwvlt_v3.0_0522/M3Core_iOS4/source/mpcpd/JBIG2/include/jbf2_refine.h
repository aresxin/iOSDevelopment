/*
 * Copyright (c) 2001-2002 by Fuji Xerox Co., Ltd. All rights reserved.
 *
 * $Id: jbf2_refine.h,v 1.4 2009/12/22 08:11:17 chikyu Exp $
 */

#ifndef JBF2_REFINE_H
#define JBF2_REFINE_H

#include "jbf2_bitmap.h"

#define JBF2_REFINE(x) ((JBF2Refine*)(x))
typedef struct _JBF2Refine JBF2Refine;

JBF2Refine	*jbf2_refine_new		(JBF2Error	*error);
void		 jbf2_refine_free		(JBF2Refine	*refine);
void		 jbf2_refine_read_header	(JBF2Refine     *refine,
						 JBF2IO         *io);
void		 jbf2_refine_read_data		(JBF2Refine	*refine,
						 JBF2Bitmap	*reference,
						 JBF2IO		*io);
JBF2Bitmap	*jbf2_refine_get_bitmap		(JBF2Refine	*refine);

#endif /* JBF2_REFINE_H */
