/*
 * Copyright (c) 2001-2002 by Fuji Xerox Co., Ltd. All rights reserved.
 *
 * $Id: jbf2_pdf.h,v 1.4 2009/12/22 08:11:17 chikyu Exp $
 */

#ifndef JBF2_PDF_H
#define JBF2_PDF_H

#include <jbf2_error.h>
#include <jbf2_types.h>

#define JBF2_PDF(x) ((JBF2Pdf*)(x))
typedef struct JBF2Pdf JBF2Pdf;

#define JBF2_PDF_CALLBACK(x) ((JBF2PdfCallback)(x))
typedef void	 (*JBF2PdfCallback)		(JBF2Pdf	*jp,
						 JBF2Pointer	 buffer,
						 JBF2UInt32	 count,
						 JBF2Pointer	 user_data);

JBF2Pdf		*jbf2_pdf_new			(void);
void		 jbf2_pdf_free			(JBF2Pdf	*jp);
void		 jbf2_pdf_decode_global		(JBF2Pdf	*jp,
						 JBF2Pointer	*code,
						 JBF2UInt32	 bytes);
void		 jbf2_pdf_decode_bitmap		(JBF2Pdf	*jp,
						 JBF2Pointer	*code,
						 JBF2UInt32	 bytes);
void		 jbf2_pdf_decode_global_cb	(JBF2Pdf	*jp);
void		 jbf2_pdf_decode_bitmap_cb	(JBF2Pdf	*jp);
void		 jbf2_pdf_purge_global		(JBF2Pdf	*jp);
void		 jbf2_pdf_purge_bitmap		(JBF2Pdf	*jp);
void		 jbf2_pdf_set_callback		(JBF2Pdf	*jp,
						 JBF2PdfCallback func,
						 JBF2Pointer	 user_data);
JBF2UInt32	 jbf2_pdf_get_width		(JBF2Pdf	*jp);
JBF2UInt32	 jbf2_pdf_get_height		(JBF2Pdf	*jp);
JBF2UInt8	*jbf2_pdf_get_line		(JBF2Pdf	*jp,
						 JBF2UInt32	 n);
JBF2Errno	 jbf2_pdf_get_errno		(JBF2Pdf	*jp);
void		 jbf2_pdf_set_errno		(JBF2Pdf	*jp,
						 JBF2Errno	 errno);

#endif /* JBF2_PDF_H */

