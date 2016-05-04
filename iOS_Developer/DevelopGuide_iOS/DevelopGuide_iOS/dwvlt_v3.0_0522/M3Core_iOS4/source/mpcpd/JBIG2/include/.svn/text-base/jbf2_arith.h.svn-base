/*
 * Copyright (c) 2001-2002 by Fuji Xerox Co., Ltd. All rights reserved.
 *
 * $Id: jbf2_arith.h,v 1.4 2009/12/22 08:11:17 chikyu Exp $
 */

#ifndef JBF2_ARITH_H
#define JBF2_ARITH_H

#include "jbf2_io.h"

typedef enum {
	JBF2_ARITH_GB,
	JBF2_ARITH_GR,
	JBF2_ARITH_IAAI,
	JBF2_ARITH_IADH,
	JBF2_ARITH_IADS,
	JBF2_ARITH_IADT,
	JBF2_ARITH_IADW,
	JBF2_ARITH_IAEX,
	JBF2_ARITH_IAFS,
	JBF2_ARITH_IAID,
	JBF2_ARITH_IAIT,
	JBF2_ARITH_IARDH,
	JBF2_ARITH_IARDW,
	JBF2_ARITH_IARDX,
	JBF2_ARITH_IARDY,
	JBF2_ARITH_IARI
} JBF2ArithType;

#define JBF2_ARITH_STAT(x) ((JBF2ArithStat*)(x))
typedef struct _JBF2ArithStat JBF2ArithStat;

#define JBF2_ARITH(x) ((JBF2Arith*)(x))
typedef struct _JBF2Arith JBF2Arith;

JBF2ArithStat	*jbf2_arith_stat_new		(JBF2Error	*error);
void		 jbf2_arith_stat_free		(JBF2ArithStat	*stat);
void		 jbf2_arith_stat_save		(JBF2ArithStat	*stat,
						 JBF2Arith	*arith);
void		 jbf2_arith_stat_restore	(JBF2ArithStat	*stat,
						 JBF2Arith	*arith);

JBF2Arith	*jbf2_arith_new			(JBF2Error	*error,
						 JBF2IO		*io);
void		 jbf2_arith_initdec		(JBF2Arith	*arith);
void		 jbf2_arith_free		(JBF2Arith	*arith);
JBF2Boolean	 jbf2_arith_decode		(JBF2Arith	*arith,
						 JBF2UInt16	 context,
						 JBF2ArithType	 type);
JBF2Int32	 jbf2_arith_decode_integer	(JBF2Arith	*arith,
						 JBF2Boolean	*oob,
						 JBF2ArithType	 type);
JBF2Int32	 jbf2_arith_decode_id		(JBF2Arith	*arith,
						 JBF2UInt32	 codelen);

#endif /* JBF2_ARITH_H */

