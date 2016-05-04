/*
 * Copyright (c) 2001-2002 by Fuji Xerox Co., Ltd. All rights reserved.
 *
 * $Id: jbf2_symbol.h,v 1.4 2009/12/22 08:11:18 chikyu Exp $
 */

#ifndef JBF2_SYMBOL_H
#define JBF2_SYMBOL_H

#include "jbf2_array.h"
#include "jbf2_bitmap.h"

#define JBF2_SYMBOL(x) ((JBF2Symbol*)(x))
typedef struct _JBF2Symbol JBF2Symbol;

JBF2Symbol	*jbf2_symbol_new	(JBF2Error	*error);
void		 jbf2_symbol_free	(JBF2Symbol	*symbol);
void		 jbf2_symbol_read	(JBF2Symbol	*symbol,
					 JBF2Array	*insyms,
					 JBF2Array	*tables,
					 JBF2Symbol	*lastsd,
					 JBF2IO		*io);
JBF2UInt32	 jbf2_symbol_count	(JBF2Symbol	*symbol);
JBF2Bitmap	*jbf2_symbol_nth	(JBF2Symbol	*symbol,
					 JBF2UInt32	 n);

#endif /* JBF2_SYMBOL_H */
