/*
 * Copyright (c) 2001-2002 by Fuji Xerox Co., Ltd. All rights reserved.
 *
 * $Id: jbf2_pattern.h,v 1.4 2009/12/22 08:11:18 chikyu Exp $
 */

#ifndef JBF2_PATTERN_H
#define JBF2_PATTERN_H

#include "jbf2_bitmap.h"

#define JBF2_PATTERN(x) ((JBF2Pattern*)(x))
typedef struct _JBF2Pattern JBF2Pattern;

JBF2Pattern	*jbf2_pattern_new	(JBF2Error	*error);
void		 jbf2_pattern_free	(JBF2Pattern	*pattern);
void		 jbf2_pattern_read	(JBF2Pattern	*pattern,
					 JBF2UInt32	 data_length,
					 JBF2IO		*io);
JBF2UInt32	 jbf2_pattern_count	(JBF2Pattern	*pattern);
JBF2Bitmap	*jbf2_pattern_nth	(JBF2Pattern	*pattern,
					 JBF2UInt32	 n);
JBF2UInt8	 jbf2_pattern_width	(JBF2Pattern	*pattern);
JBF2UInt8	 jbf2_pattern_height	(JBF2Pattern	*pattern);

#endif /* JBF2_PATTERN_H */
