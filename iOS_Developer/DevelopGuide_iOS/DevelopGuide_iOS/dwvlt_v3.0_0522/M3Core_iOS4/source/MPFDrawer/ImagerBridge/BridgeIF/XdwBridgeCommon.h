/**
 * @file  XdwBridgeCommon.h
 * @brief Bridge内パッケージで共通ヘッダファイル
 *
 * Bridge内で共通に使用される，型の宣言やグローバルな関数，ライブラリへのI/Fを提供する．<br>
 *
 * @author Toshio Yamazaki (Fuji Xelox Co., Ltd. DPC DS&S STD) <Toshi.Yamazaki@fujixerox.co.jp>
 * @date 2002-04-02
 * @version 0.1
 *
 * Copyright (C) Fuji Xerox Co., Ltd. DPC DS&S STD Toshio Yamazaki<br>
 * Created:	2002-04-02	Toshio Yamazaki<br>
 */
#ifndef XDWBRIDGECOMMON_H_INCLUDED
#define XDWBRIDGECOMMON_H_INCLUDED

#include "System/SystemIF/XdwStl.h"
#include <vector>

/* データサイズを厳密に指定する場合に使う */
typedef unsigned char	XdwTypeUInt08;		/*!< unsigned 1 byte		*/
typedef unsigned short	XdwTypeUInt16;		/*!< unsigned 2 byte		*/
typedef unsigned long	XdwTypeUInt32;		/*!< unsigned 4 byte		*/
typedef char		XdwTypeInt08;		/*!< 1 byte			*/
typedef short		XdwTypeInt16;		/*!< 2 byte			*/
typedef long		XdwTypeInt32;		/*!< 4 byte			*/
typedef float		XdwTypeFP32;		/*!< 32bit 浮動小数点(IEEE754)	*/
typedef double		XdwTypeFP64;		/*!< 64bit 浮動小数点(IEEE754)	*/

typedef XdwStlVector(short) XdwShortVector;

/*! std::vector<XdwTypeUInt32>の型定義 */
typedef XdwStlVector(XdwTypeUInt32) XdwUInt32Vector;

#endif /* XDWBRIDGECOMMON_H_INCLUDED */
