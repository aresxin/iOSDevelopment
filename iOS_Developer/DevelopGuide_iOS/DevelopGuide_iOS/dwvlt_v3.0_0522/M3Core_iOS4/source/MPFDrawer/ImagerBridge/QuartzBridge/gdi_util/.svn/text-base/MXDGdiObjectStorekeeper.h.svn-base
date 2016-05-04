//
//  MXDGdiObjectStorekeeper.h
//
//  Updater : $Author: marumo $
//  Version : $Revision: 1.1 $, $Date: 2006/08/23 03:10:14 $
//  Tag     : $Name: build15 $
//
//  Copyright (c) 2004 Fuji Xerox Co., Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "MXDGdiObject.h"

/*
 *  MXDGDIObjectを管理するクラス
 *
 */

#define MXD_GDITABLE_MAXNUM  8192		// MXDGdiObjectの格納先であるメモリ領域を一度に確保する量

typedef struct LogGdiTableColumn
{
	BOOL				isUsed;		// このインデックスは使用されている
	MXDGdiObject*		gdiObject;  // 格納されているGdiObjectをさす
} MXD_GObjTableColumn;

@interface MXDGdiObjectStorekeeper : NSObject {
	unsigned int   _tableCapacity;		// 現在の最大格納数
	unsigned int   _currentObjNum;		// 現在の格納数
	
	MXD_GObjTableColumn _gdiTable[MXD_GDITABLE_MAXNUM];  // MXDGdiObjectを格納するメモリ領域を指す
}

- (BOOL)store_gdiObj:(MXDGdiObject*)gdiObj;
- (BOOL)storeAtIndex_gdiObj:(MXDGdiObject*)gdiObj
					index:(unsigned int)index;

- (BOOL)lockAtMinimumIndex;
- (BOOL)lockAtIndex_index:(unsigned int)index;

- (MXDGdiObject*)gdiObjectAtIndex_index:(unsigned int)index;

- (BOOL)deleteGdiObjectAtIndex_index:(unsigned int)index;

@end
