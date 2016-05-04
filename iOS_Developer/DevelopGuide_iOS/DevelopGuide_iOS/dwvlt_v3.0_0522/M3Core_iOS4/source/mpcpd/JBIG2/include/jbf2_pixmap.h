/*
 * Copyright (c) 2001-2002 by Fuji Xerox Co., Ltd. All rights reserved.
 *
 * $Id: jbf2_pixmap.h,v 1.4 2009/12/22 08:11:17 chikyu Exp $
 */

#ifndef JBF2_PIXMAP_H
#define JBF2_PIXMAP_H

#include "jbf2_bitmap.h"

#define JBF2_PIXMAP(x) ((JBF2Pixmap*)(x))
typedef struct _JBF2Pixmap JBF2Pixmap;

typedef struct _JBF2PixmapParam {
#ifndef JBF2_DISABLE_BITFIELD
	JBF2UInt	mmr	 : 1;
	JBF2UInt	template : 2;
#else
	JBF2UInt8	mmr;
	JBF2UInt8	template;
#endif
	JBF2Bitmap	*skip;
} JBF2PixmapParam;

JBF2Pixmap	*jbf2_pixmap_new_with	(JBF2Error		*error,
					 JBF2UInt32		 width,
					 JBF2UInt32		 height,
					 JBF2UInt8		 depth);
void		 jbf2_pixmap_free	(JBF2Pixmap		*pixmap);
JBF2UInt32	 jbf2_pixmap_width	(JBF2Pixmap		*pixmap);
JBF2UInt32	 jbf2_pixmap_height	(JBF2Pixmap		*pixmap);
JBF2UInt8	 jbf2_pixmap_depth	(JBF2Pixmap		*pixmap);
void		 jbf2_pixmap_read_mmr	(JBF2Pixmap		*pixmap,
					 JBF2IO			*io);
void		 jbf2_pixmap_read_arith	(JBF2Pixmap		*pixmap,
					 JBF2UInt8		 template,
					 JBF2Bitmap		*skip,
					 JBF2Arith		*arith);
JBF2UInt32	*jbf2_pixmap_line	(JBF2Pixmap		*pixmap,
					 JBF2UInt32		 y);
JBF2UInt32	 jbf2_pixmap_get_pixel	(JBF2Pixmap		*pixmap,
					 JBF2UInt32		 x,
					 JBF2UInt32		 y);
void		 jbf2_pixmap_set_pixel	(JBF2Pixmap		*pixmap,
					 JBF2UInt32		 x,
					 JBF2UInt32		 y,
					 JBF2UInt32		 value);

#endif /* JBF2_PIXMAP_H */

