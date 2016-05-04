//
//  PDFDocumentHandleTest.mm
//  DWViewer
//
//  Created by wuwei on 10-11-24.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//
/*
 本段代码主要描述对PDF文件的测试部分
 setUp方法主要是接受一个参数 然后根据这个参数的值 展开测试
 值可以是确定值 可以是不定值 
*/
#import "PDFDocumentHandleTest.h"


@implementation PDFDocumentHandleTest

@synthesize documentHandler;
@synthesize pageInfo;
@synthesize fileInfo;
@synthesize attr;
@synthesize pdfFile;
@synthesize pdfPage;
@synthesize pdfDocument;

- (void)setUp:(DocumentHandle *)document
{	
	documentHandler = document;
	assert(documentHandler != nil);
	NSLog(@"20%");
}

- (void) testData:(const char *)filePath
{
	pdfDocument = dynamic_cast<PDFDocumentHandle*> (documentHandler);
	assert(pdfDocument != nil);
	NSLog(@"40%");
	assert(pdfDocument->OpenDocument(filePath));
	assert(pdfDocument->IsOpened());
	linkList = pdfDocument->GetLinkAnnotationList();
	fileInfo = pdfDocument->GetFileInfo();
	pageInfo = pdfDocument->GetPageInfo(1);
	int scale = pdfDocument->GetScale();
	linkInfo = linkList->GetLinkAnnotInfo(1);
	assert(linkInfo != nil && linkList != nil 
		   && fileInfo != nil
		   && pageInfo != nil 
		   && scale == 2);
	NSLog(@"60%");
}



- (void) testPDFFileInfo
{
	assert(fileInfo != nil);
	pdfFile = dynamic_cast<PDFFileInfo*> (fileInfo);
	const char *docName = pdfFile->GetDocName();
	long pageCount = pdfFile->GetPageCount();
	docuType = pdfFile->GetFileType();
	assert(docName =="" && pageCount ==100 && docuType == kPDF_DOC);
	NSLog(@"80%");
}

- (void) testPDFPageInfo
{
	assert(pageInfo != nil);
	pdfPage = dynamic_cast<PDFPageInfo*> (pageInfo);
	assert(pdfPage != nil);
	//mode = kFullMode;
	assert(mode);
	float height = pdfPage->GetHeight(mode);
	float width = pdfPage->GetWidth(mode);
	int pageIndex = pdfPage->GetPageIndex();
	
	assert(height==100 && width==100 && pageIndex==1 && pdfPage->GetPageObject()!=nil);
	NSLog(@"100%");
}


@end
