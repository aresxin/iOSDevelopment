//
//  DocumentHandlerTest.h
//  DWViewer
//
//  Created by wuwei on 10-11-24.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//
//  See Also: http://developer.apple.com/iphone/library/documentation/Xcode/Conceptual/iphone_development/135-Unit_Testing_Applications/unit_testing_applications.html

//  Application unit tests contain unit test code that must be injected into an application to run correctly.
//  Define USE_APPLICATION_UNIT_TEST to 0 if the unit test code is designed to be linked into an independent test executable.

#define USE_APPLICATION_UNIT_TEST 1


#import <UIKit/UIKit.h>
#import "DocumentHandle.h"
#import "FileInfo.h"
#import "PageInfo.h"
#import "XdwDocumentHandle.h"
#import "XdwPageInfo.h"
#import "XdwFileInfo.h"
#import "AttributeParser.h"
#import "XdwAttributeParser.h"
//#import "application_headers" as required


@interface DocumentHandlerTest {
	DocumentHandle *documentHandle;
	FileInfo *fileInfo;
	PageInfo *pageInfo;
	AttributeParser *attr;
	XdwDocumentHandle *xdwDocument;
	XdwFileInfo *xdwFileInfo;
	XdwPageInfo *xdwPage;
	XdwAttributeParser *xdwAttr;
	MPCObject *mpc;
	PageInfo::PAGE_MODE mode;
	
}

- (void) testGetObjs:(DocumentHandle *)document;
- (void) testData:(const char *)filePath;
- (void) testXdwDocumentHandle;
- (void) testXdwPageInfo;
- (void) testXdwFileInfo;
- (void) testXdwAttrbuteParser;


@end
