/*
 * Copyright (c) 2001-2002 by Fuji Xerox Co., Ltd. All rights reserved.
 *
 * $Id: jbf2_segment.h,v 1.4 2009/12/22 08:11:18 chikyu Exp $
 */

#ifndef JBF2_SEGMENT_H
#define JBF2_SEGMENT_H

#include "jbf2_array.h"
#include "jbf2_bitarray.h"
#include "jbf2_list.h"
#include "jbf2_page.h"

#define JBF2_SEGMENT(x) ((JBF2Segment*)(x))
typedef struct _JBF2Segment JBF2Segment;

typedef enum {
	JBF2_SYMBOL_DICTIONARY_SEGMENT                          = 0x00,
	JBF2_INTERMEDIATE_TEXT_REGION_SEGMENT                   = 0x04,
	JBF2_IMMEDIATE_TEXT_REGION_SEGMENT                      = 0x06,
	JBF2_IMMEDIATE_LOSSLESS_TEXT_REGION_SEGMENT             = 0x07,

	JBF2_PATTERN_DICTIONARY_SEGMENT                         = 0x10,
	JBF2_INTERMEDIATE_HALFTONE_REGION_SEGMENT               = 0x14,
	JBF2_IMMEDIATE_HALFTONE_REGION_SEGMENT                  = 0x16,
	JBF2_IMMEDIATE_LOSSLESS_HALFTONE_REGION_SEGMENT         = 0x17,

	JBF2_INTERMEDIATE_GENERIC_REGION_SEGMENT                = 0x24,
	JBF2_IMMEDIATE_GENERIC_REGION_SEGMENT                   = 0x26,
	JBF2_IMMEDIATE_LOSSLESS_GENERIC_REGION_SEGMENT          = 0x27,

	JBF2_INTERMEDIATE_GENERIC_REFINEMENT_REGION_SEGMENT     = 0x28,
	JBF2_IMMEDIATE_GENERIC_REFINEMENT_REGION_SEGMENT        = 0x2a,
	JBF2_IMMEDIATE_LOSSLESS_REFINEMENT_REGION_SEGMENT       = 0x2b,

	JBF2_PAGE_INFORMATION_SEGMENT                           = 0x30,
	JBF2_END_OF_PAGE_SEGMENT                                = 0x31,
	JBF2_END_OF_STRIPE_SEGMENT                              = 0x32,
	JBF2_END_OF_FILE_SEGMENT                                = 0x33,
	JBF2_PROFILES_SEGMENT                                   = 0x34,
	JBF2_TABLES_SEGMENT                                     = 0x35,
	JBF2_EXTENSION_SEGMENT                                  = 0x3e
} JBF2SegmentType;

JBF2Segment	*jbf2_segment_new		(JBF2Error	*error);
void		 jbf2_segment_free		(JBF2Segment	*segment);
void		 jbf2_segment_read_header	(JBF2Segment	*segment,
						 JBF2List	*segments,
						 JBF2IO		*io);
JBF2SegmentType	 jbf2_segment_type		(JBF2Segment	*segment);
JBF2UInt32	 jbf2_segment_number		(JBF2Segment	*segment);
JBF2UInt32	 jbf2_segment_page_number	(JBF2Segment	*segment);
JBF2UInt32	 jbf2_segment_data_length	(JBF2Segment	*segment);
JBF2Pointer	 jbf2_segment_get_data		(JBF2Segment	*segment);
void		 jbf2_segment_read_data		(JBF2Segment	*segment,
						 JBF2Bitmap	*pagebuf,
						 JBF2IO		*io);
void		 jbf2_segment_skip_data		(JBF2Segment	*segment,
						 JBF2IO		*io);
JBF2UInt32	 jbf2_segment_refer_count	(JBF2Segment	*segment);
JBF2Segment	*jbf2_segment_refer_segment_nth	(JBF2Segment	*segment,
						 JBF2UInt32	 n);
JBF2Boolean	 jbf2_segment_refer_end_nth	(JBF2Segment	*segment,
						 JBF2UInt32	 n);
JBF2Boolean	 jbf2_segment_retain_self	(JBF2Segment	*segment);
JBF2Boolean	 jbf2_segment_can_purge		(JBF2Segment	*segment);
void		 jbf2_segment_set_purge		(JBF2Segment	*segment,
						 JBF2Boolean	 purge);
void		 jbf2_segment_draw_data		(JBF2Segment	*segment,
						 JBF2Bitmap	*pagebuf,
						 JBF2UInt32	 stripe_top,
						 JBF2Boolean	 allow_override);

#endif /* JBF2_SEGMENT_H */

