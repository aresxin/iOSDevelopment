//
//  PDFDocumentHandleTest.h
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
#import "PageInfo.h"
#import "FileInfo.h"
#import "AttributeParser.h"
#import "PDFFileInfo.h"
#import "PDFPageInfo.h"
#import "PDFDocumentHandle.h"
#import "LinkAnnotInfo.h"

//#import "application_headers" as required
@class PDFDocumenthandle;

@interface PDFDocumentHandleTest {
	DocumentHandle *documentHandler;
	PageInfo *pageInfo;
	FileInfo *fileInfo;
	AttributeParser *attr;
	PDFFileInfo *pdfFile;
	PDFPageInfo *pdfPage;
	PDFDocumentHandle *pdfDocument;
	LinkAnnotInfo *linkInfo;
	LinkAnnotInfoList *linkList;
	DOCUMENT_TYPE docuType;
	PageInfo::PAGE_MODE mode;
}

@property DocumentHandle *documentHandler;
@property PageInfo *pageInfo;
@property FileInfo *fileInfo;
@property AttributeParser *attr;
@property PDFFileInfo *pdfFile;
@property PDFPageInfo *pdfPage;
@property PDFDocumentHandle *pdfDocument;

- (void) setUp:(DocumentHandle *)document;
- (void) testData:(const char *)filePath;
- (void) testPDFFileInfo;
- (void) testPDFPageInfo;

@end
