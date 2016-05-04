//
//  mxd_original_define.h
//
//  Updater : $Author: marumo $
//  Version : $Revision: 1.1 $, $Date: 2006/08/23 03:10:14 $
//  Tag     : $Name: build15 $
//
//  Copyright (c) 2004 Fuji Xerox Co., Ltd. All rights reserved.
//

/*
 *  独自定義の構造体
 */

#ifndef MXD_ORIGINAL_DEFINE_H
#define MXD_ORIGINAL_DEFINE_H

//#import "buildenvironment.h"
//#import <Foundation/Foundation.h>

#ifdef _PF_IOS_
#import <CoreGraphics/CoreGraphics.h>
#endif

#ifdef _PF_OSX_
#include <ApplicationServices/ApplicationServices.h>
#endif

// リージョンデータヘッダ構造
typedef struct tagMXD_RegionDataHeader
{
	int			rectCount;			// 矩形の数
	int			rectCapacity;		// 矩形の容量
	CGRect		bound;				// 全ての矩形を囲む矩形
} MXD_RegionDataHeader;

// リージョンデータ構造
typedef struct tagMXD_RegionData
{
	MXD_RegionDataHeader	header;		// ヘッダ
	CGRect					rectArray[1];  // 矩形の配列
} MXD_RegionData;

#endif // MXD_ORIGINAL_DEFINE_H
