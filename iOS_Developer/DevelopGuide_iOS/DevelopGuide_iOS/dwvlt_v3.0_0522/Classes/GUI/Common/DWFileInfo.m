//
//  DWFileInfo.m
//  DWViewer
//
//  Created by liuqw on 11-2-21.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "DWFileInfo.h"


@implementation DWFileInfo
@synthesize fileName;
@synthesize fileUpdateDate;
@synthesize fileSize;
@synthesize isCheck;

//『文書情報画面』の追加 start
@synthesize fileTitle;
@synthesize fileSubtitle;
@synthesize fileKeyword;
@synthesize fileRemark;
@synthesize fileAuthor;
//『文書情報画面』の追加 end

// xuxinjun 2012.03.27 start
// 保護文書の対応
@synthesize fileProtected;
// xuxinjun 2012.03.27 end

// zhaijie 2012.03.30 start
// 『セキュリティ』の情報の対応
@synthesize filePermission;
// zhaijie 2012.03.30 end

-(void)dealloc{
	
	[fileName release];
	[fileUpdateDate release];
	[fileSize release];
	
	//『文書情報画面』の追加 start	
	[fileTitle release];
	[fileSubtitle release];
	[fileKeyword release];
	[fileRemark release];
	[fileAuthor release];
	//『文書情報画面』の追加 end
	[super dealloc];
}
@end
