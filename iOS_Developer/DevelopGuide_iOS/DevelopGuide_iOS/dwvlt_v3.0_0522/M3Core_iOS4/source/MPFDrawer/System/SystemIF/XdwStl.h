//    Copyright(C) 2002 by Fuji Xerox Co.Ltd. All rights reserved.

/**
 *   @file XdwStl.h
 *   @brief STLをWrapするマクロ定義
 *
 *   VxWorks対応のコンパイラ(g++2.7.2)は名前空間とテンプレートの
 *   デフォルトパラメータに対応していない。STLの記述がコンパイラに
 *   依存してしまうため、本ファイルでマクロを提供する。
 *
 *   @author	Yozo Kashima(DS&S-STD-T31G)
 *
 *   @date	2002/04/11
 */

#ifndef XdwStl_h
#define XdwStl_h

/**
 * @def XdwStlList(Type)
 * \a Type型の要素を保持するリスト
 */

/**
 * @def XdwStlMap(Key,Type)
 * \a Key型のキーと \a Type型の値をペアで保持するマップ
 */

/**
 * @def XdwStlSet(Type)
 * \a Type型の要素を保持するセット
 */


// gcc2.7以前はnamespace stdがサポートされていない。
// テンプレートのデフォルト引数がサポートされていない。
// よって、明示的にlessを第2引数にセットする。
//#if ( defined( __GNUC__ ) && ( __GNUC_MAJOR__ < 3 ) && ( __GNUC_MINOR__ < 8 ) )
#if 0
	#include <function.h> // less
	#define XdwStlFind		find
    #define XdwStlFindIf    find_if
    #define XdwStlForEach   for_each
    #define XdwStlStableSort    stable_sort

	#define XdwStlList(T)		list< T >
	#define XdwStlVector(T)		vector< T >
	#define XdwStlSet(T)		set< T, less< T > >
	#define XdwStlMap(Key, T)	map< Key, T, less< Key > >
	#define XdwStlQueue(T)		queue< list< T > >
	#define XdwStlPair(T1, T2)	pair< T1, T2 >

	#define XdwStlMin		min
	#define XdwStlMax		max
#else // 標準C++
	#define XdwStlFind		std::find
    #define XdwStlFindIf    std::find_if
    #define XdwStlForEach   std::for_each
    #define XdwStlStableSort    std::stable_sort

	#define XdwStlList(T)		std::list< T >
	#define XdwStlVector(T)		std::vector< T >
	#define XdwStlSet(T)		std::set< T >
	#define XdwStlMap(key, T)	std::map< key, T >
	#define XdwStlQueue(T)		std::queue< T >
	#define XdwStlPair(T1, T2)	std::pair< T1, T2 >

	// MSVCではalgorithmのmax, minは無くて、代わりに_MAX, _MINを使用しなくてはならない。
	#if defined( _MSC_VER ) // Microsoft Visual C++
		#define XdwStlMin std::_MIN
		#define XdwStlMax std::_MAX
	#else // 標準C++
		#define XdwStlMin std::min
		#define XdwStlMax std::max
	#endif
#endif

// namespace std
// gcc2.7以前はnamespace stdがサポートされていない。
//#if ( defined( __GNUC__ ) && ( __GNUC_MAJOR__ < 3 ) && ( __GNUC_MINOR__ < 8 ) ) 
#if 0
	#define std 
#endif

#endif // XdwStl_h
