//
//  DocumentHandlerTest.mm
//  DWViewer
//
//  Created by wuwei on 10-11-24.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

/*
 本段代码主要描述对PDF文件的测试部分
 testGetObjs方法主要是接受一个参数 然后根据这个参数的值 展开测试
 值可以是确定值 可以是不定值 
 */

#import "DocumentHandlerTest.h"



@implementation DocumentHandlerTest

- (void) testGetObjs:(DocumentHandle *)document
{
	assert(documentHandle!=nil);
	NSLog(@"8%");
}

- (void) testData:(const char *)filePath
{
	assert(documentHandle->OpenDocument(filePath));
	assert(documentHandle->IsOpened());
	NSLog(@"16%");
}

- (void) testXdwDocumentHandle
{
	xdwDocument = dynamic_cast<XdwDocumentHandle*> (documentHandle);
	assert(xdwDocument != nil);
	NSLog(@"24%");
	assert(xdwDocument->IsOpened());
	pageInfo =  xdwDocument->GetPageInfo(1);
	fileInfo = xdwDocument->GetFileInfo();
	attr = xdwDocument->GetAttributePaser();
	assert(pageInfo!= nil && fileInfo != nil && attr != nil);
	NSLog(@"32%");
	
}

- (void) testXdwPageInfo
{
	pageInfo = documentHandle->GetPageInfo(1);
	xdwPage = dynamic_cast<XdwPageInfo*> (pageInfo);
	assert(xdwPage != nil);
	NSLog(@"40%");
	/*assert(pageInfo::PAGE_MODE==0);
	 NSInteger height = xdwPage->GetHeight(pageInfo::PAGE_MODE);
	 NSInteger pageIndex = xdwPage->GetPageIndex();
	 NSInteger width = xdwPage->GetWidth(pageInfo::PAGE_MODE);
	 MP_POS pos = xdwPage->GetPagePos(pageInfo::PAGE_MODE);
	 xdwPage->GetPageRectangle();*/
	assert(mode);
	NSInteger height = xdwPage->GetHeight(mode);
	NSInteger pageIndex = xdwPage->GetPageIndex();
	NSInteger width = xdwPage->GetWidth(mode);
	
	assert(height == 200 && width ==200 && pageIndex==1);
	NSLog(@"48%");
}

- (void) testXdwFileInfo
{
	//fileInfo = documentHandle->GetFileInfo();
	assert(fileInfo != nil);
	xdwFileInfo = dynamic_cast<XdwFileInfo*> (fileInfo);
	
	assert(xdwFileInfo != nil);
	NSLog(@"56%");
	assert(xdwFileInfo->GetFileType()==1);
	NSLog(@"64%");
	if (xdwFileInfo->IsBinder()) {
		const char *name = xdwFileInfo->GetNameOfBinderDoc(1);
		//NSString *name =[NSString stringWithCString:xdwFileInfo->GetNameOfBinderDoc(1) encoding:NSShiftJISStringEncoding];
		long pageCount = xdwFileInfo->GetPageCntOfBinderDoc(1);
		assert(name=="" && pageCount==100);
		NSLog(@"72%");
	}
	else {
		
		const char *docName = xdwFileInfo->GetDocName();
		//NSString *docName =[NSString stringWithCString:xdwFileInfo->GetDocName() encoding:NSShiftJISStringEncoding];
		long pageCount = xdwFileInfo->GetPageCount();
		assert(docName == "" && pageCount ==100);
		NSLog(@"80%");
	}
	
}


- (void) testXdwAttrbuteParser
{
	assert(attr != nil);
	xdwAttr = dynamic_cast<XdwAttributeParser*> (attr);
	NSLog(@"90%");
	
	//assert(xdwAttr -> IsBinderDoc(mpc));
	pageInfo = xdwAttr->GetPageInfo(1);
	fileInfo = xdwAttr->GetFileInfo();
	//const char *name = xdwAttr->GetAttributeName(mpc);
	assert(pageInfo != nil && fileInfo != nil &&  xdwAttr->GetDocSession()!=nil);
	NSLog(@"100%");
	
}

@end
