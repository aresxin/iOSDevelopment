/*
 *  PDFDocAttributePaser.cpp
 *  DWViewer
 *
 *  Created by jonah on 10-10-30.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "PDFAttributeParser.h"
#include "PDFFileInfo.h"
#include "PDFPageInfo.h"

PDFAttributeParser::PDFAttributeParser()
: document(NULL)
{
}

PDFAttributeParser::~PDFAttributeParser()
{	
}

// xuxinjun 2012.03.23 start
// 保護文書の対応
//XdwErrorCode PDFAttributeParser::SetFile(const char* filePath)
XdwErrorCode PDFAttributeParser::SetFile(const char* filePath, const char* password)
// xuxinjun 2012.03.23 end

{
	if (filePath == NULL) {
		return XDW_ERRORCODE_INVALID_PARAMETER;
	}
	
	// construct the url for PDFDocument
	CFStringRef path = CFStringCreateWithCString(NULL, filePath, kCFStringEncodingUTF8);   
	CFURLRef url = CFURLCreateWithFileSystemPath(NULL, path, kCFURLPOSIXPathStyle, 0);   
	CFRelease(path);
	
	// document hoding PDFDocument's information
	document = CGPDFDocumentCreateWithURL(url); 
	if (document == NULL) {
		// For Memory Leak!
		CFRelease(url);
		return XDW_ERRORCODE_FILE_ACCESS_FAULT;
	}
	CFRelease(url);
	
	return XDW_ERRORCODE_SUCCESS;
}

PageInfo* PDFAttributeParser::GetPageInfo(int pageIndex)
{
	if (pageIndex >= 0)
	{
		// pageIndex count from 0, while index count from 1
		long index = pageIndex + 1;
		CGPDFPageRef pageRef = CGPDFDocumentGetPage(document, index);
		PDFPageInfo* pageInfo = new PDFPageInfo(pageRef);
		return pageInfo;	
	}
	else
	{
		return NULL;
	}
}
 

XdwErrorCode PDFAttributeParser::SetFileInfo(FileInfo* fileInfo)
{
	PDFFileInfo* fInfo = dynamic_cast<PDFFileInfo*> (fileInfo);
	if (fInfo != NULL) {
		fInfo->SetPageCount(CGPDFDocumentGetNumberOfPages(document));
		return XDW_ERRORCODE_SUCCESS;
	} else {
		return XDW_ERRORCODE_INVALID_PARAMETER;
	}
}


HANDLE PDFAttributeParser::GetDocSession()
{
	return XdwNull;
}

void PDFAttributeParser::Destroy()
{
	CGPDFDocumentRelease(document);
	return ;
}

// liuqw 20110801 start
// ページ編集機能の追加

// xuxinjun 2012.03.23 start
// 保護文書の対応
//XdwErrorCode PDFAttributeParser::SetFileForUpdate(const char* filePath)
XdwErrorCode PDFAttributeParser::SetFileForUpdate(const char* filePath, const char* password)
// xuxinjun 2012.03.23 end

{
	return XDW_ERRORCODE_SUCCESS;
}
// liuqw 20110801 end

// xuxinjun 2012.03.23 start
// パーミッションの対応.
MP_Permission PDFAttributeParser::GetPermission()
{
	return 0;
}
// xuxinjun 2012.03.23 end

// xujj 2012.03.22 start
// 検索機能の追加
HRESULT PDFAttributeParser::SearchText(int& nPageNum,
									   int  startPageIndex,
									   int  endPageIndex,
									   unsigned short* text, 
									   bool next, 
									   bool display,
									   MP_TextInfo*  textInfoInput,
									   MP_TextInfo** textInfoResult, 
									   MP_AnnoInfo* annoInfo)
{
	return MP_S_NO_RES;
}
// xujj 2012.03.22 end

// tongtx 2012.03.23 start
// 選択機能の追加
HRESULT PDFAttributeParser::GetLogicAnnotationList(int nPageNum, MP_ObjectType objectType, LogicAnnoInfoList* list)
{
	return NULL;
}

bool PDFAttributeParser::SelectText(int nPageNum, int nAnnIndex, MP_Pos start, MP_Pos end, MP_TextInfo** textInfo)
{
	return false;
}

bool PDFAttributeParser::GetText(int nPageNum, int nAnnIndex, MP_Text** text, MP_Integer length, MP_TextInfo* textInfo)
{
	return false;
}
// tongtx 2012.03.23 end