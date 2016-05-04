/*!	\file		alla-config.h
 *	\brief		compile configuration
 *	\author		YOKOSE Taro, T&D/SPD/22G,
 *			mailto:yokose.taro@fujixerox.co.jp
 *	\version	2.0.2-woexception-2
 *	\date		2004.09.06
 *	\warning	Copyright(C) 2004 by Fuji Xerox Co., Ltd.
 *			All rights reserved.<br>FUJIXEROX CONFIDENTIAL
 */
#ifndef _LIBALLA_ALLA_CONFIG_H_
#define _LIBALLA_ALLA_CONFIG_H_
namespace alla_v2 {
/*---------------------------------------------------------------------------*/
/* for Exception Warning */
#define DISABLE_EXCEPTION_WARNING

#ifdef DISABLE_EXCEPTION_WARNING
#define NO_THROW	
#else
#define NO_THROW	throw ()
#endif
/*---------------------------------------------------------------------------*/
/* for Visual Stduio */
#if 	(_MSC_VER > 0) && (_MSC_VER < 1300)
#define	VC6
#else
#undef	VC6
#endif

#ifndef _MSC_VER
typedef signed char		aint8;
typedef unsigned char		auint8;
typedef signed short		aint16;
typedef unsigned short		auint16;
typedef signed int		aint32;
typedef unsigned int		auint32;
typedef signed long long	aint64;
typedef unsigned long long	auint64;
#else
typedef signed _int8		aint8;
typedef unsigned _int8		auint8;
typedef signed _int16		aint16;
typedef unsigned _int16		auint16;
typedef signed _int32		aint32;
typedef unsigned _int32		auint32;
typedef signed _int64		aint64;
typedef unsigned _int64		auint64;
#endif
/*---------------------------------------------------------------------------*/
}
#endif //_LIBALLA_ALLA_CONFIG_H_
