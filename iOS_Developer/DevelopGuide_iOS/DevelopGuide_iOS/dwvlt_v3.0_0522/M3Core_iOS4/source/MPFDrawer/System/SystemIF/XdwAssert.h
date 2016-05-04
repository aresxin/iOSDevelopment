//    Copyright(C) 2002 by Fuji Xerox Co.Ltd. All rights reserved.

/**
 *   @file XdwAssert.h
 *   @brief XDW Assertマクロ定義
 *   @author	Yozo Kashima(DS&S-STD-T31G)
 *   @date	2002/04/11
 */

#ifndef XdwAssert_h
#define XdwAssert_h

/**
 * @def XdwAssert(exp)
 * 	expが真になることを表明する。expを評価した結果がfalseに
 *	なった場合の動作はプラットフォームに依存する。
 *	XdwAssertはNDEBUGがOFFの時のみ有効となる。
 */

# ifndef NDEBUG

# define XdwAssert(exp)

# else

// プラットフォーム毎に切り替える
// とりあえず普通のasssertを使うバージョン

#ifdef _PF_WINCE_

// WinCEではassertは規定されていない
# define XdwAssert(exp)

#else //_PF_WINCE_

#include <assert.h>
# define XdwAssert(exp)	assert(exp)

#endif //_PF_WINCE_

# endif	// NDEBUG

#endif // XdwAssert_h
