//
//  MXDConverterTypeC.h
//
//  Updater : $Author: marumo $
//  Version : $Revision: 1.1 $, $Date: 2006/08/23 03:10:12 $
//  Tag     : $Name: build15 $
//
//  Copyright (c) 2004 Fuji Xerox Co., Ltd. All rights reserved.
//

#import "MXDConverter.h"

#import "MXDBezierPath.h"

@interface MXDConverterTypeC : MXDConverter {
	// 描画図形
	MXDBezierPath**		_pathArray;				// n個のパスあり
	MXDImageData**		_ptnImgDataArray;		// パターンイメージ
	int*				_ptnAngleArray;			// パターン描画の角度
	unsigned long*		_ptnMaskColorArray;		// 変換色
	int					_pathCount;
}

@end
