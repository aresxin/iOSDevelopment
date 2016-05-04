/*!	\file		config.h
 *	\brief		debug configuration
 *	\author		YOKOSE Taro, T&D/SPD/22G,
 *			mailto:yokose.taro@fujixerox.co.jp
 *	\version	2.0.1
 *	\date		2004.05.31
 *	\warning	Copyright(C) 2004 by Fuji Xerox Co., Ltd.
 *			All rights reserved.<br>FUJIXEROX CONFIDENTIAL
 */
#ifndef _LIBALLA_CONFIG_H_
#define _LIBALLA_CONFIG_H_
#include "macro.h"
namespace alla {
/*---------------------------------------------------------------------------*/
#define	INLINE			inline
#undef	DBG

#ifdef	DBG
#define	DPRINT(X,Y,Z)		fprintf (X, Y, Z);
#define	DBGPRINT
#else
#define	DPRINT(X,Y,Z)
#undef	DBGPRINT
#endif
/*---------------------------------------------------------------------------*/
}
#endif //_LIBALLA_CONFIG_H_
