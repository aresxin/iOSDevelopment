//    Copyright(C) 2002 by Fuji Xerox Co.Ltd. All rights reserved.

/**
 *   @file XdwNew.h
 *   @brief XDW Newマクロ定義
 *   @author	Yozo Kashima(DS&S-STD-T31G)
 *   @date	2002/04/11
 */

#ifndef XdwNew_h
#define XdwNew_h

#include "XdwConfig.h"


// new/deleteはマクロ化する。
// malloc/freeも。
// 
// SIFのメモリ管理を使うが一部標準でないところがある。
// それはSif_Mallocがデフォルトでメモリ枯渇時にNULLを
// かえさず処理を終えてしまうところ。
// 標準に合わせるようにしておいた方がよいだろう。
//

/**
 * @def XdwNew(Type)
 * \a Type型のオブジェクトを動的メモリ上に構築する。
 */

/**
 * @def XdwDelete(p)
 * \a pで示される動的メモリ上のオブジェクトを削除する。
 */

/**
 * @def XdwANew(Type,n)
 * \a n個のType型のオブジェクトの配列を動的メモリ上に構築する。
 */

/**
 * @def XdwADelete(p)
 * \a pで示される動的メモリ上のオブジェクトの配列を削除する。
 */

/**
 * @def XdwMalloc(size)
 * \a size分のメモリを確保する。
 */

/**
 * @def XdwFree(p)
 * \a pで示されるメモリを解放する。
 */

#ifndef _WIN32_WCE
// WinCE上ではない
//#include <new.h>
#include <new>
#endif //_WIN32_WCE

#define XdwNew(Type)		new Type
#define XdwDelete(p)		delete p

#define XdwANew(Type,n)		new Type[n]
#define XdwADelete(p)		delete[] p

/*! 現在のメモリ空き容量を取得する */
#if defined _PF_WIN32_ || defined _PF_WINCE_

/* Windowsでは以下の関数で置き換える */
#include "System/WinCE/XdwWinCELib.h"
/*! 現在のメモリ空き容量を取得する */
#define XdwGetMemoryEmptySpaceSize() XdwWinCEGetGetMemoryEmptySpaceSize()

#else /* defined _PF_WIN32_ || defined _PF_WINCE_ */

/* Linux Zaurus */
#ifdef _USE_SHARP_LIB
#include "XdwLinuxZaurusLib.h"
/*! 現在のメモリ空き容量を取得する */
#define XdwGetMemoryEmptySpaceSize() XdwLinuxZaurusGetMemoryEmptySpaceSize();
#else
/* Other Platform*/
#define XdwGetMemoryEmptySpaceSize() 0x7FFFFFFF
#endif //_USE_SHARP_LIB 

#endif /* defined _PF_WIN32_ || defined _PF_WINCE_ */

#if !defined(SIF)
// SUN上ではデフォルトのnew
// プラットフォーム毎の切り替えはTBD
#define XdwMalloc(size)		malloc(size)
#define	XdwFree(p)			free(p)

#else // SIF

//#include "sif_memmgr.h"

#define XdwMalloc(size)		Sif_MallocWithNotify(size)
#define XdwFree(p)			Sif_Free(p)

#endif	//

#endif // XdwNew_h
