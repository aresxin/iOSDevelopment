/*
 * Copyright (c) 2001-2002 by Fuji Xerox Co., Ltd. All rights reserved.
 *
 * $Id: jbf2_text.h,v 1.4 2009/12/22 08:11:17 chikyu Exp $
 */

#ifndef JBF2_TEXT_H
#define JBF2_TEXT_H

#include "jbf2_array.h"
#include "jbf2_bitmap.h"
#include "jbf2_huffman.h"

#define JBF2_TEXT(x) ((JBF2Text*)(x))
typedef struct _JBF2Text JBF2Text;

#define JBF2_TEXT_HEADER(x) ((JBF2TextHeader*)(x))
typedef struct _JBF2TextHeader JBF2TextHeader;

struct _JBF2TextHeader {
	JBF2BitmapHeader bitmap_header;
#ifndef JBF2_DISABLE_BITFIELD
	JBF2UInt	 huff       : 1;
	JBF2UInt	 refine     : 1;
	JBF2UInt	 logstrips  : 2;
	JBF2UInt	 transpose  : 1;
	JBF2UInt	 defpixel   : 1;
	JBF2UInt	 rtemplate  : 1;
	JBF2Int		 dsoffset   : 5;
#else
	JBF2UInt8	 huff;
	JBF2UInt8	 refine;
	JBF2UInt8	 logstrips;
	JBF2UInt8	 transpose;
	JBF2UInt8	 defpixel;
	JBF2UInt8	 rtemplate;
	JBF2Int8	 dsoffset;
#endif
	JBF2Corner	 refcorner;
	JBF2Operator	 operator;
	JBF2Table	*hufffs;
	JBF2Table	*huffds;
	JBF2Table	*huffdt;
	JBF2Table	*huffrdw;
	JBF2Table	*huffrdh;
	JBF2Table	*huffrdx;
	JBF2Table	*huffrdy;
	JBF2Table	*huffrsize;
	JBF2Int8	 ref_at [4];
	JBF2UInt32	 instances;
};

JBF2Text	*jbf2_text_new		(JBF2Error	*error);
JBF2Text	*jbf2_text_new_with_header
					(JBF2Error	*error,
					 JBF2TextHeader *header);
void		 jbf2_text_free		(JBF2Text	*text);
void		 jbf2_text_get_header	(JBF2Text	*text,
					 JBF2TextHeader *header);
void		 jbf2_text_read_header	(JBF2Text	*text,
					 JBF2Array	*tables,
					 JBF2IO		*io);
void		 jbf2_text_read_huffman	(JBF2Text	*text,
					 JBF2Array	*symbols,
					 JBF2Table	*symcodes,
					 JBF2Arith	*arith,
					 JBF2IO		*io);
void		 jbf2_text_read_arith	(JBF2Text	*text,
					 JBF2Array	*symbols,
					 JBF2Arith	*arith);
void		 jbf2_text_read_data	(JBF2Text	*text,
					 JBF2Array	*symbols,
					 JBF2IO		*io);
JBF2Bitmap	*jbf2_text_get_bitmap	(JBF2Text	*text);

#endif /* JBF2_TEXT_H */
