/*
	Copyright (C) Fuji Xerox Co; Ltd. 2002. All rights reserved.
 
	FM_Define.h -- definition of Font Manager 

	Created:	Jun 28, 2002 By Kunihiko Kobayashi 
	Modified:	

*/

#ifndef _FM_DEFINE_H_INCLUDED_
#define _FM_DEFINE_H_INCLUDED_


/* config product type */

#ifdef DOCUWORKS_VIEWER

#if defined _PF_WIN32_ || defined _PF_WINCE_

#define FM_VIEW_WINCE

#else

#define FM_VIEW_LINUX

#endif

#else

#ifdef WIN32
#define FM_PRINT_WIN32
#endif

#endif

/* 
#define FM_VIEW_WIN32
#define FM_PRINT_WINCE
#define FM_PRINT_LINUX
*/



/* link objects by each product */

#ifdef FM_VIEW_WINCE
#define FM_LINK_FONTMANAGER
#define FM_LINK_PROCESSOR
#define FM_LINK_PROCESSORVIEWWINCE
#define FM_LINK_CODECONVERTER
#define FM_LINK_FONTREGISTER
#endif

#ifdef FM_VIEW_LINUX
#define FM_LINK_FONTMANAGER
#define FM_LINK_PROCESSOR
#define FM_LINK_PROCESSORVIEWLINUX
#define FM_LINK_BITMAPLIB
#define FM_LINK_CODECONVERTER
#define FM_LINK_FONTREGISTER
#endif

#ifdef FM_PRINT_WIN32
#define FM_LINK_FONTMANAGER
#define FM_LINK_PROCESSOR
#define FM_LINK_PROCESSORPRINTWIN32
#define FM_LINK_BITMAPLIB
#define FM_LINK_DATACACHE
#define FM_LINK_DATAFONTSUPPORT
#define FM_LINK_FONTCACHE
#define FM_LINK_FONTCONVERTER
#define FM_LINK_FONTREGISTER
#endif

#ifndef FM_LINK_FONTMANAGER
#define FM_LINK_FONTMANAGER
#endif

#ifndef FM_LINK_PROCESSOR
#define FM_LINK_PROCESSOR
#endif

#endif
