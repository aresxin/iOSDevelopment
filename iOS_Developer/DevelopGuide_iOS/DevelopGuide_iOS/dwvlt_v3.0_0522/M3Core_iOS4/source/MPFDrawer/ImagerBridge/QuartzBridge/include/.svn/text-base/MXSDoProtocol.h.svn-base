//
//  MXSDoProtocol.h
//
//  Updater : $Author: marumo $
//  Version : $Revision: 1.1 $, $Date: 2006/08/23 03:10:14 $
//  Tag     : $Name: build15 $
//
//  Copyright (c) 2004 Fuji Xerox Co., Ltd. All rights reserved.
//

/*
 * MXSDoProtocol
 * DOに使用するメソッドの定義
 */
@protocol MXSDoProtocol

- (void) testDO : (in NSString *) send : (out NSString **) recv;	
- (int) GetCachedPswds: (inout StructForGetCachedPswd *) pData;		/** キャッシュされた暗号化パスワードの取得 */
- (int) CachePswd: (in StructForCachePswd *) pData;					/** 暗号化パスワードのキャッシング */
- (int) GetKey: (inout StructForGetKey *) pData;					/** パスワード鍵の取得 */
- (int) EndTransaction;												/** 排他制御解除 */
- (int) ready;														/** サーバのメソッドを呼ぶ事が出来ているかを判定する */

@end

