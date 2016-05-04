/*
 * Copyright (c) 2001-2002 by Fuji Xerox Co., Ltd. All rights reserved.
 *
 * $Id: jbf2_memory.h,v 1.4 2009/12/22 08:11:17 chikyu Exp $
 */

#ifndef JBF2_MEMORY_H
#define JBF2_MEMORY_H

#include "jbf2_error.h"
#include "jbf2_types.h"

#define jbf2_new(error, type, count)	\
	((type*)jbf2_malloc  (error, (count) * sizeof (type)))
#define jbf2_new0(error, type, count)	\
	((type*)jbf2_malloc0 (error, (count) * sizeof (type)))
#define jbf2_renew(error, pointer, type, count)	\
	((type*)jbf2_realloc (error, pointer, (count) * sizeof (type)))
#define jbf2_renew0(error, pointer, type, old_count, new_count)	\
	((type*)jbf2_realloc0 (error, pointer, (old_count) * sizeof (type), (new_count) * sizeof (type)))

JBF2Pointer	jbf2_malloc	(JBF2Error	*error,
				 JBF2UInt32	 size);
JBF2Pointer	jbf2_malloc0	(JBF2Error	*error,
				 JBF2UInt32	 size);
JBF2Pointer	jbf2_realloc	(JBF2Error	*error,
				 JBF2Pointer	 pointer,
				 JBF2UInt32	 size);
JBF2Pointer	jbf2_realloc0	(JBF2Error	*error,
				 JBF2Pointer	 pointer,
				 JBF2UInt32	 old_size,
				 JBF2UInt32	 new_size);
void		jbf2_free	(JBF2Pointer	 pointer);

#endif /* JBF2_MEMORY_H */

