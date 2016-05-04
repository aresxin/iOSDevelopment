//
//  DWAuthenticationManager.h
//  DWViewer
//
//  Created by xinjun xu on 12-3-22.
//  Copyright (c) 2012年 Neusoft dalian. All rights reserved.
//

#import <Foundation/Foundation.h>
#include "mppmodel.h"
#include "mpcinc/dwspswdc.h"

enum DW_PROTECTED_TYPE
{
	kProtectTypePwd = 0,
	kProtectTypeNoPwd,
	kProtectTypeNull,
};

// xuxinjun 2012.03.23 start
// 保護文書の対応
enum CHECK_PROTECTED_TYPE
{
	kCheckSelectRowInTableView = 0,
	kCheckSettingsNameError,
	kCheckEditingFile,
	kCheckUTIAssociate,
	kCheckDownloadFinish,
	kCheckBrifecase,
	kCheckOpenAssociatedFile,
};
// xuxinjun 2012.03.23 end

@interface DWAuthenticationManager : NSObject
{
	MPCSession	*mpcSession_;
	MPCObject	*mpcDocObject_;
	MPCObject	*mpcPageRoot_;
	MPCProfile	*mpcProfile_;
}

- (DW_PROTECTED_TYPE) checkDocumentProtectedType:(NSString*)filepath;
- (BOOL) isDocumentProtected:(NSString*)filepath;
- (BOOL) canOpenProtectedDocument:(NSString*)filepath withPassword:(NSString*)pwd;
- (BOOL) openProtectedDocument:(MPCProfile*)mpcProfile andPassword:(NSString*)pwd;
@end

