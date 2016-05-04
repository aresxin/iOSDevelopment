/*
 * Copyright (c) 2001-2002 by Fuji Xerox Co., Ltd. All rights reserved.
 *
 * $Id: jbf2_bitmap.h,v 1.4 2009/12/22 08:11:17 chikyu Exp $
 */

#ifndef JBF2_BITMAP_H
#define JBF2_BITMAP_H

#include "jbf2_arith.h"

#define JBF2_BITMAP(x) ((JBF2Bitmap*)(x))
typedef struct _JBF2Bitmap JBF2Bitmap;

#define JBF2_BITMAP_HEADER(x) ((JBF2BitmapHeader*)(x))
typedef struct _JBF2BitmapHeader JBF2BitmapHeader;

struct _JBF2BitmapHeader {
	JBF2UInt32	 width;
	JBF2UInt32	 height;
	JBF2UInt32	 xpos;
	JBF2UInt32	 ypos;
	JBF2Operator	 operator;
};

JBF2Bitmap	*jbf2_bitmap_new_with		(JBF2Error	*error,
						 JBF2UInt32	 width,
						 JBF2UInt32	 height,
						 JBF2UInt32	 xpos,
						 JBF2UInt32	 ypos,
						 JBF2Operator	 operator);
JBF2Bitmap	*jbf2_bitmap_new_with_header	(JBF2Error	*error,
						 JBF2BitmapHeader *header);
JBF2Bitmap	*jbf2_bitmap_new_with_read_header
						(JBF2Error	*error,
						 JBF2IO		*io);
void		 jbf2_bitmap_free		(JBF2Bitmap	*bitmap);
JBF2Bitmap	*jbf2_bitmap_duplicate		(JBF2Bitmap	*bitmap);
void		 jbf2_bitmap_resize		(JBF2Bitmap	*bitmap,
						 JBF2UInt32	 height,
						 JBF2Boolean	 color);
JBF2Operator	 jbf2_bitmap_operator		(JBF2Bitmap	*bitmap);
JBF2UInt32	 jbf2_bitmap_width		(JBF2Bitmap	*bitmap);
JBF2UInt32	 jbf2_bitmap_height		(JBF2Bitmap	*bitmap);
JBF2UInt32	 jbf2_bitmap_xpos		(JBF2Bitmap	*bitmap);
JBF2UInt32	 jbf2_bitmap_ypos		(JBF2Bitmap	*bitmap);
JBF2UInt8	*jbf2_bitmap_line		(JBF2Bitmap	*bitmap,
						 JBF2UInt32	 y);
JBF2Boolean	 jbf2_bitmap_get_pixel		(JBF2Bitmap	*bitmap,
						 JBF2UInt32	 x,
						 JBF2UInt32	 y);
void		 jbf2_bitmap_set_pixel		(JBF2Bitmap	*bitmap,
						 JBF2UInt32	 x,
						 JBF2UInt32	 y,
						 JBF2Boolean	 value);
void		 jbf2_bitmap_fill		(JBF2Bitmap	*bitmap,
						 JBF2Boolean	 value);
void		 jbf2_bitmap_copy		(JBF2Bitmap	*dst,
						 JBF2Bitmap	*src,
						 JBF2Int32	 xmin,
						 JBF2Int32	 ymin,
						 JBF2Int32	 xmax,
						 JBF2Int32	ymax,
						 JBF2Int32	 xpos,
						 JBF2Int32	 ypos,
						 JBF2Operator	 operator);
void		 jbf2_bitmap_get_header 	(JBF2Bitmap	*bitmap,
						 JBF2BitmapHeader *header);
void		 jbf2_bitmap_read_mmr		(JBF2Bitmap	*bitmap,
						 JBF2UInt32	 data_length,
						 JBF2IO		*io);
void		 jbf2_bitmap_read_arith		(JBF2Bitmap	*bitmap,
						 JBF2UInt8	 template,
						 JBF2Boolean	 tpgdon,
						 JBF2Int8	 at [8],
						 JBF2Bitmap	*skip,
						 JBF2Arith	*arith);
void		 jbf2_bitmap_read_refine	(JBF2Bitmap	*bitmap,
						 JBF2Boolean	 template,
						 JBF2Int32	 dx,
						 JBF2Int32	 dy,
						 JBF2Boolean	 tpgron,
						 JBF2Int8	 at [4],
						 JBF2Bitmap	*reference,
						 JBF2Arith	*arith);

#endif /* JBF2_BITMAP_H */

