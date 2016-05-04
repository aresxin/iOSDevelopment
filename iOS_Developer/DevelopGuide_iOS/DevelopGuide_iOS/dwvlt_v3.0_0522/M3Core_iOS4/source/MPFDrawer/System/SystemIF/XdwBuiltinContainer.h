//    Copyright(C) 2002 by Fuji Xerox Co.Ltd. All rights reserved.

/**
 *   @file XdwBuiltinContainer.h
 *   @brief 基本型のコンテナクラスのマクロ定義
 *
 *   VxWorks対応のコンパイラ(g++2.7.2)は名前空間とテンプレートの
 *   デフォルトパラメータに対応していない。STLの記述がコンパイラに
 *   依存してしまうため、本ファイルでマクロを提供する。
 *
 *   @author	Tomohiro Yamada(DS&S-STD-T31G)
 *
 *   @date	2002/05/20
 */

#ifndef XdwBuiltinContainer_h
#define XdwBuiltinContainer_h

#include "XdwStl.h"

/**
 * @typedef XdwLongVector
 * @brief std::vector<long>の型定義
 */
typedef XdwStlVector(long) XdwLongVector;


#endif // XdwBuiltinContainer_h
