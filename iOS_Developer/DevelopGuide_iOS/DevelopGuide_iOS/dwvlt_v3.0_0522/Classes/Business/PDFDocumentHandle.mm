/*
 *  PDFDocumentHandle.cpp
 *  DWViewer
 *
 *  Created by jonah on 10-10-30.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "PDFDocumentHandle.h"
#include "PDFPageInfo.h"
#import "Utility.h"


PDFDocumentHandle::PDFDocumentHandle()
: m_bFileOpened(false)
, m_pageScale(100)
, m_FilePath("")
, m_FileInfo(XdwNull)
, m_AttrParser(XdwNull)
{
	
}

PDFDocumentHandle::~PDFDocumentHandle()
{
	Destroy();
}

bool PDFDocumentHandle::IsOpened()
{
	return m_bFileOpened;
}

// xuxinjun 2012.03.23 start
// 保護文書の対応
//XdwErrorCode PDFDocumentHandle::OpenDocument(const char* filePath)
XdwErrorCode PDFDocumentHandle::OpenDocument(const char* filePath, const char* password)
// xuxinjun 2012.03.23 end

{
	XdwErrorCode retCode = XDW_ERRORCODE_SUCCESS;
	
	m_FilePath = filePath;
	
	// Create PDFAttributeParser
	m_AttrParser = new PDFAttributeParser();
	if (m_AttrParser == XdwNull) {
		return XDW_ERRORCODE_INSUFFICIENT_MEMORY;
	}
	
	// Parser DocuWorks Document 
	
	// xuxinjun 2012.03.23 start
	// 保護文書の対応
	/*
	 retCode = m_AttrParser->SetFile(filePath);
	 */
	retCode = m_AttrParser->SetFile(filePath, password);
	// xuxinjun 2012.03.23 end
	
	if (retCode != XDW_ERRORCODE_SUCCESS)
	{
#ifdef _DEBUG
		NSLog(@"PDFAttributeParser SetFile() failed.");
#endif
		delete m_AttrParser;
		m_AttrParser = NULL;
		return retCode;
	}
	
	m_FileInfo = new PDFFileInfo(filePath);
	retCode = m_AttrParser->SetFileInfo(m_FileInfo);
	if (retCode != XDW_ERRORCODE_SUCCESS)
	{
#ifdef _DEBUG
		NSLog(@"PDFAttributeParser SetFileInfo() failed.");
#endif
		delete m_AttrParser;
		m_AttrParser = NULL;
		return retCode;
	}	
	m_bFileOpened = true;
	
	return retCode;
}

AttributeParser* PDFDocumentHandle::GetAttributePaser()
{
	if (!m_bFileOpened) {
		return XdwNull;
	}
	
	return m_AttrParser;
}

FileInfo* PDFDocumentHandle::GetFileInfo()
{
	if (!m_bFileOpened) {
		return XdwNull;
	}
	
	// return fileInfo 
	return m_FileInfo;
}


PageInfo* PDFDocumentHandle::GetPageInfo(int pageIndex)
{	
	if (!m_bFileOpened) {
		return XdwNull;
	}
	
	PageInfo* pageInfo = XdwNull;
	
	// find pageinfo in the map
	std::map<int, PageInfo*>::iterator iter;
	if ((iter = m_PageInfoMap.find(pageIndex)) != m_PageInfoMap.end()) {
		return iter->second;
	}
	
	pageInfo = m_AttrParser->GetPageInfo(pageIndex);
	if (pageInfo != XdwNull) {
		// inset pageinfo to map
		m_PageInfoMap.insert(std::make_pair(pageIndex, pageInfo));
	}
	
	return pageInfo;
}

// liuqw 20110801 start
// ページ編集機能の追加

// xuxinjun 2012.03.23 start
// 保護文書の対応
//XdwErrorCode PDFDocumentHandle::OpenDocumentForUpdate(const char* filePath)
XdwErrorCode PDFDocumentHandle::OpenDocumentForUpdate(const char* filePath, const char* password)
// xuxinjun 2012.03.23 end

{
    XdwErrorCode retCode = XDW_ERRORCODE_SUCCESS;
	
	return retCode;
}

void PDFDocumentHandle::UpdateLinkAnnotationList()
{
}

PageInfo* PDFDocumentHandle::GetNewPageInfo(int pageIndex)
{
    return nil;
}
// liuqw 20110801 end

// Draw PageObject
bool PDFDocumentHandle::DrawPage(int nPageNum, CGContextRef ctx, int scale, CGRect rect)
{
	// liuqw 20120217 start
	// AR NO.17781の対応
	
	/*
	 // get pageRef for drawing Page 
	 PDFPageInfo* pageinfo = dynamic_cast<PDFPageInfo*>(GetPageInfo(nPageNum));
	 if (pageinfo == NULL) {
	 return false;
	 }
	 CGPDFPageRef pageRef = pageinfo->GetPageRef();
	 
	 long pageWidth = 0;
	 long pageHeight  = 0;
	 
	 pageWidth = Utility::MMToPixelWithScale(pageinfo->GetWidth(), scale);
	 pageHeight = Utility::MMToPixelWithScale(pageinfo->GetHeight(), scale);
	 
	 if (pageWidth == 0 || pageHeight == 0) {
	 return false;
	 }
	 
	 CGRect destRect = CGRectMake(0, 0, pageWidth, pageHeight);
	 CGContextSetRGBFillColor(ctx, 1.0, 1.0, 1.0, 1.0);
	 CGContextTranslateCTM(ctx, CGRectGetMinX(destRect), CGRectGetMaxY(destRect));
	 */
	/* delete for V4
	 CGFloat posX = 0;
	 CGFloat posY = 0;
	 
	 if (!CGRectIsEmpty(rect)) {
	 posX = -rect.origin.x;
	 posY = -rect.origin.y;
	 }
	 CGContextSaveGState(ctx);
	 CGContextTranslateCTM(ctx, posX, posY);
	 CGContextRestoreGState(ctx);
	 */
	
	// 2011/03/23 PDF不具合チャートを修正 start
	/*
	 CGRect pageBox =  CGPDFPageGetBoxRect(pageRef, kCGPDFMediaBox);
	 CGContextScaleCTM(ctx, destRect.size.width/pageBox.size.width,
	 -destRect.size.height/pageBox.size.height);
	 */
	/*
	 CGRect pageBox =  CGPDFPageGetBoxRect(pageRef, kCGPDFMediaBox);
	 int rotation = CGPDFPageGetRotationAngle(pageRef);
	 switch (rotation) {
	 case 90:
	 CGContextRotateCTM(ctx, M_PI_2);
	 CGContextTranslateCTM(ctx, -CGRectGetMaxY(destRect), 0);
	 CGContextScaleCTM(ctx, destRect.size.height/pageBox.size.width,
	 -destRect.size.width/pageBox.size.height);
	 break;
	 case 180:
	 CGContextRotateCTM(ctx, M_PI);
	 CGContextTranslateCTM(ctx, -destRect.size.width, destRect.size.height);
	 CGContextScaleCTM(ctx, destRect.size.width/pageBox.size.width,
	 -destRect.size.height/pageBox.size.height);
	 break;
	 case 270:
	 CGContextRotateCTM(ctx, M_PI_2 * 3);
	 CGContextTranslateCTM(ctx, 0, destRect.size.width);
	 CGContextScaleCTM(ctx, destRect.size.height/pageBox.size.width,
	 -destRect.size.width/pageBox.size.height);
	 break;
	 default:
	 CGContextScaleCTM(ctx, destRect.size.width/pageBox.size.width,
	 -destRect.size.height/pageBox.size.height);
	 break;
	 }
	 // 2011/03/23 PDF不具合チャートを修正 end
	 
	 // draw a page
	 CGContextDrawPDFPage(ctx, pageRef);
	 return true;
	 */
	
	
	// 1. get pageRef for drawing Page 
	PDFPageInfo* pageinfo_ = dynamic_cast<PDFPageInfo*>(GetPageInfo(nPageNum));
	if (pageinfo_ == NULL) 
	{
		return false;
	}
	
	// 2. get page effective rect.
	CGPDFPageRef pageRef_	= pageinfo_->GetPageRef();
	CGRect destRect			= CGPDFPageGetBoxRect(pageRef_, kCGPDFCropBox);	
	
	// 3. get page scale for scale CTM.
	// 3.1. get scale x.
	long dstWidth	= Utility::MMToPixelWithScale(pageinfo_->GetWidth(), scale);
	long srcWidth	= destRect.size.width;
	
	// 3.1. get scale y.
	long dstHeight	= Utility::MMToPixelWithScale(pageinfo_->GetHeight(), scale);
	long srcHeight	= destRect.size.height;
	
	// 4. transform ctm for rotation.
	int rotation = CGPDFPageGetRotationAngle(pageRef_);
	switch (rotation) {
		case 90:
		{
			float scale_x = (float)dstHeight / (float)srcWidth;
			float scale_y = (float)dstWidth  / (float)srcHeight;
			CGContextScaleCTM(ctx, scale_x, scale_y);
			
			CGContextScaleCTM(ctx, 1.0f, -1.0f);
			CGContextRotateCTM(ctx, -M_PI_2);
			
			float translate_x = -destRect.origin.x;
			float translate_y = -destRect.origin.y;
			CGContextTranslateCTM(ctx, translate_x, translate_y);
			
			break;
		}
			
		case 180:
		{
			float scale_x = (float)dstWidth / (float)srcWidth;
			float scale_y = (float)dstHeight  / (float)srcHeight;
			CGContextScaleCTM(ctx, scale_x, scale_y);
			
			CGContextScaleCTM(ctx, 1.0f, -1.0f);
			CGContextRotateCTM(ctx, M_PI);
			
			float translate_x = -(destRect.origin.x + destRect.size.width);
			float translate_y = -(destRect.origin.y);
			CGContextTranslateCTM(ctx, translate_x, translate_y);
			
			break;
		}
			
		case 270:
		{
			float scale_x = (float)dstHeight / (float)srcWidth;
			float scale_y = (float)dstWidth  / (float)srcHeight;
			CGContextScaleCTM(ctx, scale_x, scale_y);
			
			CGContextScaleCTM(ctx, 1.0f, -1.0f);
			CGContextRotateCTM(ctx, M_PI_2);
			
			float translate_x = -(destRect.origin.x + destRect.size.width);
			float translate_y = -(destRect.origin.y + destRect.size.height);
			CGContextTranslateCTM(ctx, translate_x, translate_y);
			
			break;
		}
			
		default:
		{
			float scale_x = (float)dstWidth  / (float)srcWidth;
			float scale_y = (float)dstHeight / (float)srcHeight;
			CGContextScaleCTM(ctx, scale_x, scale_y);
			
			CGContextScaleCTM(ctx, 1.0f, -1.0f);
			
			float translate_x = -(destRect.origin.x);
			float translate_y = -(destRect.origin.y + destRect.size.height);
			CGContextTranslateCTM(ctx, translate_x, translate_y);
			
			break;
		}
	}
	
	// 5. draw pdf page.
	CGContextDrawPDFPage(ctx, pageRef_);
	
	return true;
	
	// liuqw 20120217 end
}

long PDFDocumentHandle::GetScale()
{
	return m_pageScale;
}

void PDFDocumentHandle::SetScale(long scale)
{
	if (scale > PAGE_SCALE_MAX ||  
		scale < PAGE_SCALE_MIN ) {
		return ;
	}
	
	m_pageScale = scale;
}

bool PDFDocumentHandle::SetDocAnnotationDispaly(ANNOT_DISPALY mode)
{
	return true;
}

bool PDFDocumentHandle::SetFileInfo(FileInfo* fileInfo)
{
	return true;
}

void PDFDocumentHandle::Destroy()
{
	// Memory Leak の対応 start
	// clear PageInfo
	std::map<int, PageInfo*>::iterator iter;
	for (iter = m_PageInfoMap.begin(); iter != m_PageInfoMap.end(); ++iter) {
		PageInfo *tmpPageInfo = iter->second;
		delete tmpPageInfo;
	}
	m_PageInfoMap.clear();
	// Memory Leak の対応 end
	
	if (m_FileInfo != NULL)
	{
		delete m_FileInfo;
	}
	m_FileInfo = NULL;
	
	if (m_AttrParser != NULL) 
	{
		delete m_AttrParser;
	}
	m_AttrParser = NULL;
	
	m_bFileOpened = false;
	
	return ;
}

// add by lixin 20110815 DW_iPhoneViewer_20 start
/* save annotation edit */
bool PDFDocumentHandle::IsDocumentModified()
{
	return true;
}

bool PDFDocumentHandle::SaveDocumentModified()
{
	return true;
}


bool PDFDocumentHandle::CloseCurrentFile()
{
	return true;
}
// DW_iPhoneViewer_20 end

LinkAnnotInfoList* PDFDocumentHandle::GetLinkAnnotationList()
{
	return XdwNull;
}

// xuxinjun 2012.03.23 start
// パーミッションの対応.
MP_Permission PDFDocumentHandle::GetPermission()
{
	return 0;
}
// xuxinjun 2012.03.23 end

// xujj 2012.03.22 start
// 検索機能の追加
HRESULT PDFDocumentHandle::SearchText(int& nPageNum,
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
LogicAnnoInfoList* PDFDocumentHandle::GetLogicAnnotationList(int nPageNum, MP_ObjectType objectType)
{
	return NULL;
}

bool PDFDocumentHandle::SelectText(int nPageNum, int nAnnIndex, MP_Pos start, MP_Pos end, MP_TextInfo** textInfo)
{
	return false;
}

bool PDFDocumentHandle::GetText(int nPageNum, int nAnnIndex, MP_Text** text, MP_Integer length, MP_TextInfo* textInfo)
{
	return false;
}
// tongtx 2012.03.23 end