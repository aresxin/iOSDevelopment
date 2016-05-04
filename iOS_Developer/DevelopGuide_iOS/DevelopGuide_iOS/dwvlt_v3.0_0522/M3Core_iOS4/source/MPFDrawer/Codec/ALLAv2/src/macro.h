/*!	\file		macro.h
 *	\brief		macroes definition
 *	\author		YOKOSE Taro, T&D/SPD/22G,
 *			mailto:yokose.taro@fujixerox.co.jp
 *	\version	2.0.2-woexception-0
 *	\date		2004.08.04
 *	\warning	Copyright(C) 2004 by Fuji Xerox Co., Ltd.
 *			All rights reserved.<br>FUJIXEROX CONFIDENTIAL
 */
#ifndef _LIBALLA_MACRO_H_
#define _LIBALLA_MACRO_H_
/*---------------------------------------------------------------------------*/
#define	ALLA_NAMESPACE_BEGIN	namespace alla_v2 {
#define ALLA_NAMESPACE_END	};
ALLA_NAMESPACE_BEGIN
#define IS_HIT(X)		((X) <= fifth)
#define IS_NOT_HIT(X)		((X) > fifth)
#define IS_DIFF(X)		((X) == diff)
#define IS_MARKER(X)		((X) == marker)

#define NULL_CHECK(T)		{ if ((T) == NULL) {			\
				    THROW (&status, "bad alloc", 220);	\
				    return; }}
#define IS_BAD(S)		((S).id)
#define MY_DELETE(X)		{ delete (X); (X) = NULL; }
#define MY_FREE(X)		{ if (X) { free (X); (X) = NULL; }} 
#define CLIP(X)			((X) < 0 ? 0 : ((X) > 0xff ? 0xff : (X)))
/*---------------------------------------------------------------------------*/
ALLA_NAMESPACE_END
#endif //_LIBALLA_MACRO_H_
