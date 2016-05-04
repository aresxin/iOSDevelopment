/*
 * Copyright (C) Fuji Xerox Co; Ltd. 2002. All rights reserved.
 * Flib_Error.h
 *
 * log:
 * Created:        Sep 24, 2002 By Kunihiko Kobayashi (Porting from Globe FontServer)
 * Modified:
 *
 */



#ifndef _OL_ERROR_H_INCLUDED_
#define _OL_ERROR_H_INCLUDED_


#include "OL_Config.h"
#include "OL_Types.h"
#include "OL_TypesExt.h"


#define OL_ERROR_PREFIX		0xC1230000


#ifdef OL_DEBUG
#	define OL_MESSAGE(E)		fprintf(stderr, "%s(%d) : 0x%08x\n", __FILE__, __LINE__, E)
#else
#	define OL_MESSAGE(E)		
#endif //OL_DEBUG



// error category
#define OL_NOERROR		0x0000
#define OL_ERROR		0x0001
#define OL_NEW			0x0002
#define OL_MEMORY		OL_NEW
#define OL_DELETE		0x0003
#define OL_RESIZE		0x0004

#define OL_FS			0x2000
#define OL_OL_ERROR		0x2001
#define OL_OL_NEW		0x2002
#define OL_OL_RESIZE		0x2004
#define OL_OL_INVALIDMAP	0x2010
#define OL_OL_FONTNOTFOUND	0x2020
#define OL_OL_INVALIDFORMAT	0x2030
#define OL_OL_ILLEGALFONTID	0x2040

#define OL_PTN			0x6000
#define OL_PTN_ERROR		0x6001
#define OL_PTN_NEW		0x6002
#define OL_PTN_RESIZE		0x6004
#define OL_PTN_INVALIDDATA	0x6010
#define OL_PTN_INVALIDTYPE	0x6020		
#define OL_PTN_INVALID		0x6030
#define OL_PTN_NOTREADY		0x6040

#define OL_PATH			0x7000
#define OL_PATH_ERROR		0x7001
#define OL_PATH_NEW		0x7002
#define OL_PATH_RESIZE		0x7004
#define OL_PATH_OUTOFRANGE	0x7005
#define OL_PATH_ILLEGALOPERATOR	0x7006

#define OL_CMP			0x8000
#define OL_CMP_ERROR		0x8001
#define OL_CMP_NEW		0x8002
#define OL_CMP_RESIZE		0x8004
#define OL_CMP_ALLOC		0x8005

#endif //_OL_ERROR_H_INCLUDED_
