/*
 * Copyright (c) 2001-2002 by Fuji Xerox Co., Ltd. All rights reserved.
 *
 * $Id: jbf2_document.h,v 1.4 2009/12/22 08:11:17 chikyu Exp $
 */

#ifndef JBF2_DOCUMENT_H
#define JBF2_DOCUMENT_H

#include "jbf2_io.h"
#include "jbf2_list.h"
#include "jbf2_page.h"
#include "jbf2_segment.h"

#define JBF2_DOCUMENT(x) ((JBF2Document*)(x))
typedef struct _JBF2Document JBF2Document;

#define JBF2_ORGANISATION(x) ((JBF2Organisation*)(x))
typedef enum {
	JBF2_RANDOM_ACCESS,
	JBF2_SEQUENTIAL
} JBF2Organisation;

#define JBF2_DOCUMENT_CALLBACK_TYPE(x) ((JBF2DocumentCallbackType*)(x))
typedef enum {
	JBF2_FILE_START_CALLBACK,
	JBF2_FILE_END_CALLBACK,
	JBF2_PAGE_START_CALLBACK,
	JBF2_PAGE_END_CALLBACK,
	JBF2_STRIPE_START_CALLBACK,
	JBF2_STRIPE_END_CALLBACK,
	JBF2_SEGMENT_START_CALLBACK,
	JBF2_SEGMENT_END_CALLBACK
} JBF2DocumentCallbackType;

JBF2Document	*jbf2_document_new		(JBF2Error	*error);
JBF2Document	*jbf2_document_new_with		(JBF2Error	*error,
						 JBF2Boolean	 pages_unknown,
						 JBF2UInt32	 pages,
						 JBF2Organisation organisation);
void		 jbf2_document_free		(JBF2Document	*document);
JBF2Boolean	 jbf2_document_total_pages_unknown
						(JBF2Document	*document);
JBF2UInt32	 jbf2_document_total_pages	(JBF2Document	*document);
JBF2Organisation jbf2_document_organisation	(JBF2Document	*document);
void		 jbf2_document_read_header	(JBF2Document	*document,
						 JBF2IO		*io);
void		 jbf2_document_purge		(JBF2Document	*document);
void		 jbf2_document_parse		(JBF2Document	*document,
						 JBF2IO		*io);
void		 jbf2_document_set_callback	(JBF2Document	*document,
						 JBF2DocumentCallbackType type,
						 JBF2Func2	 func,
						 JBF2Pointer	 user_data);
JBF2List	*jbf2_document_page_list	(JBF2Document	*document);
JBF2List	*jbf2_document_segment_list	(JBF2Document	*document);

#endif /* JBF2_DOCUMENT_H */

