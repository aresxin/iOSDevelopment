/*
 * Copyright (c) 2001-2002 by Fuji Xerox Co., Ltd. All rights reserved.
 *
 * $Id: jbf2_io.h,v 1.4 2009/12/22 08:11:17 chikyu Exp $
 */

#ifndef JBF2_IO_H
#define JBF2_IO_H

#include "jbf2_error.h"
#include "jbf2_types.h"

#define JBF2_IO(x) ((JBF2IO*)(x))
typedef struct _JBF2IO JBF2IO;

#define JBF2_IO_READ_CALLBACK(x) ((JBF2IOReadCallback)(x))
typedef void (*JBF2IOReadCallback)	(JBF2Error	*error,
					 JBF2Pointer	 buffer,
					 JBF2UInt32	 count,
					 JBF2Pointer	 user_data);

JBF2IO		*jbf2_io_new		   (JBF2Error		*error);
void		 jbf2_io_free		   (JBF2IO		*io);
void		 jbf2_io_read		   (JBF2IO		*io,
					    JBF2Pointer		 buffer,
					    JBF2UInt32		 count);
void		 jbf2_io_putback	   (JBF2IO		*io,
					    JBF2UInt8		 c);
void		 jbf2_io_set_read_callback (JBF2IO		*io,
					    JBF2IOReadCallback	 callback,
					    JBF2Pointer		 user_data);
JBF2Boolean	 jbf2_io_is_eof		   (JBF2IO		*io);
JBF2UInt8	 jbf2_io_read_uint8	   (JBF2IO		*io);
JBF2UInt16	 jbf2_io_read_uint16	   (JBF2IO		*io);
JBF2UInt32	 jbf2_io_read_uint32	   (JBF2IO		*io);
JBF2Int16	 jbf2_io_read_int16	   (JBF2IO		*io);
JBF2Int32	 jbf2_io_read_int32	   (JBF2IO		*io);

void		 jbf2_io_reset_bits	   (JBF2IO		*io);
JBF2UInt32	 jbf2_io_read_bits	   (JBF2IO		*io,
					    JBF2UInt32		 length);
void		 jbf2_io_putback_bits	   (JBF2IO		*io,
					    JBF2UInt32		 bits,
					    JBF2UInt32		 length);

JBF2UInt32	 jbf2_io_read_count	   (JBF2IO		*io);
JBF2UInt32	 jbf2_io_putback_max	   (JBF2IO		*io);

#endif /* JBF2_IO_H */

