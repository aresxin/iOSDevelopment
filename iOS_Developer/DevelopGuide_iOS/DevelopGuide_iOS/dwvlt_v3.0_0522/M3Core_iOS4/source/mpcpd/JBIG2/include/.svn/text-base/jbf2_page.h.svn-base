/*
 * Copyright (c) 2001-2002 by Fuji Xerox Co., Ltd. All rights reserved.
 *
 * $Id: jbf2_page.h,v 1.4 2009/12/22 08:11:17 chikyu Exp $
 */

#ifndef JBF2_PAGE_H
#define JBF2_PAGE_H

#include "jbf2_bitmap.h"

#define JBF2_PAGE(x) ((JBF2Page*)(x))
typedef struct _JBF2Page JBF2Page;

#define JBF2_PAGEINFO(x) ((JBF2PageInfo*)(x))
typedef struct _JBF2PageInfo JBF2PageInfo;

JBF2PageInfo	*jbf2_pageinfo_new		(JBF2Error	*error);
void		 jbf2_pageinfo_free		(JBF2PageInfo	*info);
void		 jbf2_pageinfo_read		(JBF2PageInfo	*info,
						 JBF2IO		*io);

JBF2Page	*jbf2_page_new			(JBF2Error	*error,
						 JBF2UInt32	 number);
void		 jbf2_page_free			(JBF2Page	*page);
void		 jbf2_page_read_info		(JBF2Page	*page,
						 JBF2PageInfo	*info);
JBF2UInt32	 jbf2_page_number		(JBF2Page	*page);
JBF2Boolean	 jbf2_page_is_lossless		(JBF2Page	*page);
JBF2Boolean	 jbf2_page_may_refine		(JBF2Page	*page);
JBF2Boolean	 jbf2_page_default_pixel	(JBF2Page	*page);
JBF2Boolean	 jbf2_page_require_aux_buffer	(JBF2Page	*page);
JBF2Boolean	 jbf2_page_operator_override	(JBF2Page	*page);
JBF2Boolean	 jbf2_page_striped		(JBF2Page	*page);
JBF2UInt32	 jbf2_page_max_stripe_size	(JBF2Page	*page);
void		 jbf2_page_resize		(JBF2Page	*page,
						 JBF2UInt32	 height,
						 JBF2Boolean	 finish);
JBF2UInt32	 jbf2_page_get_height		(JBF2Page	*page);
JBF2Bitmap	*jbf2_page_get_bitmap		(JBF2Page	*page);
JBF2Boolean	 jbf2_page_can_purge		(JBF2Page	*page);
void		 jbf2_page_set_purge		(JBF2Page	*page,
						 JBF2Boolean	 purge);
#endif /* JBF2_PAGE_H */

