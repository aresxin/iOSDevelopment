//
//  DWFileInfo.h
//  DWViewer
//
//  Created by liuqw on 11-2-21.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface DWFileInfo : NSObject {
	NSString*	fileName;
	NSDate*		fileUpdateDate;
	NSNumber*	fileSize;
	//File Multiple Del by Yangjx 0603 start
	BOOL        isCheck;
	//File Multiple Del by Yangjx 0603 end
	
	//『文書情報画面』の追加 start
	NSString* fileTitle;
	NSString* fileSubtitle;
	NSString* fileAuthor;
	NSString* fileKeyword;
	NSString* fileRemark;
	//『文書情報画面』の追加 end
}
@property (nonatomic, retain) NSString* fileName;
@property (nonatomic, retain) NSDate* fileUpdateDate;
@property (nonatomic, retain) NSNumber* fileSize;
@property BOOL isCheck;

//『文書情報画面』の追加 start
@property (nonatomic, retain) NSString* fileTitle;
@property (nonatomic, retain) NSString* fileSubtitle;
@property (nonatomic, retain) NSString* fileAuthor;
@property (nonatomic, retain) NSString* fileKeyword;
@property (nonatomic, retain) NSString* fileRemark;

// xuxinjun 2012.03.27 start
// 保護文書の対応
@property BOOL fileProtected;
// xuxinjun 2012.03.27 end

// zhaijie 2012.03.30 start
// 『セキュリティ』の情報の対応
@property long filePermission;
// zhaijie 2012.03.30 end
//『文書情報画面』の追加 end

@end
