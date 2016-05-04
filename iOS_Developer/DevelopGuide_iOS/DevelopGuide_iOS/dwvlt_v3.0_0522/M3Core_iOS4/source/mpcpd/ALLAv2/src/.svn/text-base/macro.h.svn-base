/*!	\file		macro.h
 *	\brief		macroes definition
 *	\author		YOKOSE Taro, T&D/SPD/22G,
 *			mailto:yokose.taro@fujixerox.co.jp
 *	\version	2.0.0
 *	\date		2004.05.14
 *	\warning	Copyright(C) 2004 by Fuji Xerox Co., Ltd.
 *			All rights reserved.<br>FUJIXEROX CONFIDENTIAL
 */
#ifndef _LIBALLA_MACRO_H_
#define _LIBALLA_MACRO_H_
/*---------------------------------------------------------------------------*/
//#define	ALLA_NAMESPACE_BEGIN	namespace alla {
//#define ALLA_NAMESPACE_END	};
namespace alla {
#define IS_HIT(X)		((X) <= fifth)
#define IS_NOT_HIT(X)		((X) > fifth)
#define IS_DIFF(X)		((X) == diff)
#define IS_MARKER(X)		((X) == marker)

// 09.07.14 - M.Chikyu WindowsMobile対応
#ifdef _M3CORE_MP_
#undef DELETE
#endif

#define DELETE(X)		{ delete (X); (X) = NULL; }
#define FREE(X)			{ if (X) { free (X); (X) = NULL; }} 
#define CLIP(X)			((X) < 0 ? 0 : ((X) > 0xff ? 0xff : (X)))
/*---------------------------------------------------------------------------*/
}
#endif //_LIBALLA_MACRO_H_
