/*
 * Copyright (c) 2001-2002 by Fuji Xerox Co., Ltd. All rights reserved.
 *
 * $Id: jbf2_extension.h,v 1.4 2009/12/22 08:11:17 chikyu Exp $
 */

#ifndef JBF2_EXTENSION_H
#define JBF2_EXTENSION_H

#include "jbf2_io.h"

#define JBF2_EXTENSION(x) ((JBF2Extension*)(x))
typedef struct _JBF2Extension JBF2Extension;

typedef enum {
	JBF2_ASCII_COMMENT   = 0x20000000,
	JBF2_UNICODE_COMMENT = 0x20000002
} JBF2ExtensionType;

JBF2Extension	*jbf2_extension_new		(JBF2Error	*error);
void		 jbf2_extension_free		(JBF2Extension	*extension);
void		 jbf2_extension_read		(JBF2Extension	*extension,
						 JBF2UInt32	 length,
						 JBF2IO		*io);
JBF2UInt32	 jbf2_extension_type		(JBF2Extension	*extension);
JBF2Boolean	 jbf2_extension_is_reserved	(JBF2Extension	*extension);
JBF2Boolean	 jbf2_extension_is_dependent	(JBF2Extension	*extension);
JBF2Boolean	 jbf2_extension_is_necessary	(JBF2Extension	*extension);
JBF2UInt32	 jbf2_extension_length		(JBF2Extension	*extension);
JBF2Pointer	 jbf2_extension_get_data	(JBF2Extension	*extension);

#endif /* JBF2_EXTENSION_H */

