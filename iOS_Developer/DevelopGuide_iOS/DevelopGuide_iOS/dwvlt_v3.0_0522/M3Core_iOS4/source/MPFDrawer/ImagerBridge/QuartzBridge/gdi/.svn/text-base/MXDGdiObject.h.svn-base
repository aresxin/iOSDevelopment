//
//  MXDObject.h
//
//  Updater : $Author: marumo $
//  Version : $Revision: 1.1 $, $Date: 2006/08/23 03:10:14 $
//  Tag     : $Name: build15 $
//
//  Copyright (c) 2004 Fuji Xerox Co., Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

#if defined(TARGET_OS_IPHONE) && (TARGET_OS_IPHONE == 1)
#import "../buildenvironment.h"
#else
#import <ApplicationServices/ApplicationServices.h>
#endif


@interface MXDGdiObject : NSObject {

}

/*
 * GDI オブジェクトに関連付けられているすべてのシステム領域を解放することによって、
 * 結び付けられている GDI オブジェクトをメモリから削除します。
 *
 * @param MXDGdiObject* gdiObject ペン、ブラシ、フォント、ビットマップ、リージョン、パレットのいずれかの論理オブジェクトのハンドルを指定します。
 *
 * @return 関数が成功すると、0 以外の値が返ります。
 */
 + (BOOL)deleteObject:(MXDGdiObject*)gdiObject;
 
@end
