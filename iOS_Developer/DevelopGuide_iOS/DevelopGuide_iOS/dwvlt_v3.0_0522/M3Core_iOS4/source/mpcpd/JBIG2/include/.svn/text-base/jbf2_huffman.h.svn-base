/*
 * Copyright (c) 2001-2002 by Fuji Xerox Co., Ltd. All rights reserved.
 *
 * $Id: jbf2_huffman.h,v 1.4 2009/12/22 08:11:17 chikyu Exp $
 */

#ifndef JBF2_HUFFMAN_H
#define JBF2_HUFFMAN_H

#include "jbf2_io.h"

#define JBF2_TABLE(x) ((JBF2Table*)(x))
typedef struct _JBF2Table JBF2Table;

#define JBF2_TABLE_LINE(x) ((JBF2TableLine*)(x))
typedef struct _JBF2TableLine JBF2TableLine;

typedef enum {
	JBF2_TABLE_A, JBF2_TABLE_B, JBF2_TABLE_C, JBF2_TABLE_D,
	JBF2_TABLE_E, JBF2_TABLE_F, JBF2_TABLE_G, JBF2_TABLE_H,
	JBF2_TABLE_I, JBF2_TABLE_J, JBF2_TABLE_K, JBF2_TABLE_L,
	JBF2_TABLE_M, JBF2_TABLE_N, JBF2_TABLE_O, JBF2_TABLE_USER
} JBF2TableType;

struct _JBF2TableLine {
	JBF2Int32	rangelow;
	JBF2UInt32	codes;
	JBF2UInt8	preflen;
	JBF2UInt8	rangelen;
	JBF2Boolean	oob;
};

JBF2Table	*jbf2_table_new			(JBF2Error	*error);
void		 jbf2_table_free		(JBF2Table	*table);
void		 jbf2_table_resize		(JBF2Table	*table,
						 JBF2UInt32	 n);
JBF2Int32	 jbf2_table_decode		(JBF2Table	*table,
						 JBF2Error	*error,
						 JBF2Boolean	*oob,
						 JBF2IO		*io);
JBF2Table	*jbf2_table_get_standard	(JBF2TableType	 type);
void		 jbf2_table_read_user_defined	(JBF2Table	*table,
						 JBF2IO		*io);
void		 jbf2_table_read_symbol_id	(JBF2Table	*table,
						 JBF2UInt32	 symbols,
						 JBF2IO		*io);
void		 jbf2_table_assign_symbol_code	(JBF2Table	*table,
						 JBF2UInt32	 symbols);
JBF2Int32	 jbf2_table_low			(JBF2Table	*table);
JBF2Int32	 jbf2_table_high		(JBF2Table	*table);
JBF2UInt32	 jbf2_table_length		(JBF2Table	*table);
JBF2TableLine	*jbf2_table_get_nth		(JBF2Table	*table,
						 JBF2UInt32	 n);
JBF2Boolean	 jbf2_table_has_oob		(JBF2Table	*table);
JBF2TableType	 jbf2_table_type		(JBF2Table	*table);

#endif /* JBF2_HUFFMAN_H */

