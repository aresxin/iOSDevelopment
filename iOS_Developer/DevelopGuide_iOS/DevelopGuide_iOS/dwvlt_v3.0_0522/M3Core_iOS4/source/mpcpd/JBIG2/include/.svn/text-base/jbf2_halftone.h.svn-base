/*
 * Copyright (c) 2001-2002 by Fuji Xerox Co., Ltd. All rights reserved.
 *
 * $Id: jbf2_halftone.h,v 1.4 2009/12/22 08:11:17 chikyu Exp $
 */

#ifndef JBF2_HALFTONE_H
#define JBF2_HALFTONE_H

#include "jbf2_pattern.h"

#define JBF2_HALFTONE(x) ((JBF2Halftone*)(x))
typedef struct _JBF2Halftone JBF2Halftone;

JBF2Halftone	*jbf2_halftone_new		(JBF2Error	*error);
void		 jbf2_halftone_free		(JBF2Halftone	*halftone);
void		 jbf2_halftone_read		(JBF2Halftone	*halftone,
						 JBF2Pattern	*pattern,
						 JBF2IO		*io);
JBF2Bitmap	*jbf2_halftone_get_bitmap	(JBF2Halftone	*halftone);

#endif /* JBF2_HALFTONE_H */
