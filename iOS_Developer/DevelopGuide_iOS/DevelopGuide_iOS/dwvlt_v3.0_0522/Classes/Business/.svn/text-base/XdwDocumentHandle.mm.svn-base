/*
 *  XdwDocumentHandle.cpp
 *  DWViewer
 *
 *  Created by jonah on 10-10-30.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "XdwDocumentHandle.h"
#import "Utility.h"

XdwDocumentHandle::XdwDocumentHandle()
: m_bFileOpened(false)
, m_bBreakDrawing(false)
, m_pageScale(100)
, m_FilePath("")
, m_FileInfo(XdwNull)
, m_AttrParser(XdwNull)
, m_LinkAnnotList(XdwNull)

// tongtx 2012.03.23 start
// 選択機能の追加
, m_LogicAnnotList(XdwNull)
// tongtx 2012.03.23 end

{
}

XdwDocumentHandle::~XdwDocumentHandle()
{
	Destroy();
}

// xuxinjun 2012.03.23 start
// 保護文書の対応
//XdwErrorCode XdwDocumentHandle::OpenDocument(const char* filePath)
XdwErrorCode XdwDocumentHandle::OpenDocument(const char* filePath, const char* password)
// xuxinjun 2012.03.23 end

{
	XdwErrorCode retCode = XDW_ERRORCODE_SUCCESS;
	
	m_FilePath = filePath;
	
	// Create XdwFileInfo
	m_FileInfo = new XdwFileInfo(filePath);
	if (m_FileInfo == XdwNull) {
		retCode = XDW_ERRORCODE_INSUFFICIENT_MEMORY;
		goto ErrorEnd;
	}
	
	// Create XdwAttributeParser
	m_AttrParser = new XdwAttributeParser();
	if (m_AttrParser == XdwNull) {
		retCode = XDW_ERRORCODE_INSUFFICIENT_MEMORY;		
		goto ErrorEnd;
	}
	
	// Parser DocuWorks Document 
	// xuxinjun 2012.03.23 start
	// 保護文書の対応
	/*
	 retCode = m_AttrParser->SetFile(filePath);
	 */
	retCode = m_AttrParser->SetFile(filePath, password);
	// xuxinjun 2012.03.23 end
	if (retCode != XDW_ERRORCODE_SUCCESS) {
		#ifdef _DEBUG
		NSLog(@"XdwAttributeParser SetFile() failed.");
        #endif
		goto ErrorEnd;
	}

	// set file info
	if (!SetFileInfo(m_FileInfo)) {
		#ifdef _DEBUG
		NSLog(@"SetFileInfo() failed.");
		#endif
		goto ErrorEnd;
	}
	
	m_bFileOpened = true;

	return retCode;

ErrorEnd:
	m_FilePath = "";
	m_bFileOpened = false;

	if (m_FileInfo) {
		delete m_FileInfo;
		m_FileInfo = XdwNull;
	}
	
	if (m_AttrParser) {
		delete m_AttrParser;
		m_AttrParser = XdwNull;
	}

	return retCode;
}

AttributeParser* XdwDocumentHandle::GetAttributePaser()
{
	if (!m_bFileOpened) {
		return XdwNull;
	}

	return m_AttrParser;
}

FileInfo* XdwDocumentHandle::GetFileInfo()
{
	if (!m_bFileOpened) {
		return XdwNull;
	}

	return m_FileInfo;
}

PageInfo* XdwDocumentHandle::GetPageInfo(int pageIndex)
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
//XdwErrorCode XdwDocumentHandle::OpenDocumentForUpdate(const char* filePath)
XdwErrorCode XdwDocumentHandle::OpenDocumentForUpdate(const char* filePath, const char* password)
// xuxinjun 2012.03.23 end

{
    XdwErrorCode retCode = XDW_ERRORCODE_SUCCESS;
	
	m_FilePath = filePath;
	
	// Create XdwFileInfo
	m_FileInfo = new XdwFileInfo(filePath);
	if (m_FileInfo == XdwNull) {
		retCode = XDW_ERRORCODE_INSUFFICIENT_MEMORY;
		goto ErrorEnd;
	}
	
	// Create XdwAttributeParser
	m_AttrParser = new XdwAttributeParser();
	if (m_AttrParser == XdwNull) {
		retCode = XDW_ERRORCODE_INSUFFICIENT_MEMORY;		
		goto ErrorEnd;
	}
	
	// Parser DocuWorks Document 
	
	// xuxinjun 2012.03.23 start
	// 保護文書の対応
	//retCode = m_AttrParser->SetFileForUpdate(filePath);
	retCode = m_AttrParser->SetFileForUpdate(filePath, password);
	// xuxinjun 2012.03.23 end
	
	if (retCode != XDW_ERRORCODE_SUCCESS) {
		goto ErrorEnd;
	}
    
	// set file info
	if (!SetFileInfo(m_FileInfo)) {
		goto ErrorEnd;
	}
	
	m_bFileOpened = true;
    
	return retCode;
    
ErrorEnd:
	m_FilePath = "";
	m_bFileOpened = false;
    
	if (m_FileInfo) {
		delete m_FileInfo;
		m_FileInfo = XdwNull;
	}
	
	if (m_AttrParser) {
		delete m_AttrParser;
		m_AttrParser = XdwNull;
	}
    
	return retCode;
}

int  XdwDocumentHandle::GetStorageVersion()
{
    if (m_AttrParser) {
		return m_AttrParser->GetStorageVersion(); 
	}
	return false;
}

void XdwDocumentHandle::UpdateLinkAnnotationList()
{
	if (m_LinkAnnotList != XdwNull) {
		delete m_LinkAnnotList;
		m_LinkAnnotList = XdwNull;
		GetLinkAnnotationList();
	}
}

PageInfo* XdwDocumentHandle::GetNewPageInfo(int pageIndex)
{
    if (!m_bFileOpened) {
		return XdwNull;
	}
	
	PageInfo* pageInfo = XdwNull;
	
	// find pageinfo in the map
	std::map<int, PageInfo*>::iterator iter;
	if ((iter = m_PageInfoMap.find(pageIndex)) != m_PageInfoMap.end()) {
		m_PageInfoMap.erase(iter);
	}
	
	pageInfo = m_AttrParser->GetPageInfo(pageIndex);
	if (pageInfo != XdwNull) {
		// inset pageinfo to map
		m_PageInfoMap.insert(std::make_pair(pageIndex, pageInfo));
	}
	
	return pageInfo;
}
// liuqw 20110801 end

long XdwDocumentHandle::GetScale()
{
	return m_pageScale;
}

void XdwDocumentHandle::SetScale(long scale)
{
	if (scale > PAGE_SCALE_MAX ||  
		scale < PAGE_SCALE_MIN ) {
		return ;
	}

	m_pageScale = scale;
}

bool XdwDocumentHandle::CanEnableAnnotation()
{
	if (m_AttrParser) {
		return m_AttrParser->CanEnableAnnotation(); 
	}
	return false;
}

bool XdwDocumentHandle::SetDocAnnotationDispaly(ANNOT_DISPALY mode)
{
	/*
	ANNOT_DISPALY curMode;
	
	// Check now annotation settings 
	if (m_FileInfo != XdwNull) {
		curMode = m_FileInfo->GetAnnotationDisplayMode();
		if (curMode == mode) {
			return true;
		}
	}
	 */

	if (m_AttrParser) {
		if ((m_AttrParser->SetAnnotationDisplay((int)mode))) {
			m_FileInfo->SetAnnotationDisplay(mode == kShowAnnot ? true : false);
			return true;
		} 
	}
	
	return false;
}

// Draw PageObject
bool XdwDocumentHandle::DrawPage(int nPageNum, CGContextRef ctx, int scale, CGRect rect)
{

	HRESULT hres  = MP_NOERROR;
	
	if (!m_bFileOpened)
	{
		return false;
	}

	//m_bBreakDrawing = false;
	if (m_bBreakDrawing)
	{
		return false;
	}

	MPCSession* mpcSession = (MPCSession*)m_AttrParser->GetDocSession();
	if (mpcSession == XdwNull)
	{
		return false;
	}
	
	// Get draw page info
	PageInfo* pageInfo = GetPageInfo(nPageNum);
	if (pageInfo == XdwNull)
	{
		return false;
	}
	
	if (m_FileInfo == XdwNull)
	{
		return false;
	}
	
	long pageWidth = 0;
	long pageHeight = 0;

	// V4 more page uses the  same drawer
	//m_pageScale = scale;
	
	// just draw a rect of the page
	if (!CGRectIsEmpty(rect))
	{
		pageWidth  = rect.size.width;
		pageHeight = rect.size.height;
	}
	else
	{ 
	// draw all page.
		if (m_FileInfo->GetAnnotationDisplayMode() == kShowAnnot)
		{
			pageWidth  = pageInfo->GetWidth( PageInfo::kFullMode);
			pageHeight = pageInfo->GetHeight(PageInfo::kFullMode);
		}
		else
		{
			pageWidth  = pageInfo->GetWidth( PageInfo::kPaperMode);
			pageHeight = pageInfo->GetHeight(PageInfo::kPaperMode);
		}
		
		pageWidth  = Utility::MMToPixelWithScaleAndScaleFactor(pageWidth,  scale);
		pageHeight = Utility::MMToPixelWithScaleAndScaleFactor(pageHeight, scale);
	}

	MPCObject* basicPage = (MPCObject*)pageInfo->GetPageObject();
	if (basicPage == XdwNull)
	{
		return false;
	}
	
	// Drawインターフェイス取得
	MPCMediaAdv *drawPage = (MPCMediaAdv*)basicPage->GetInterface(IID_MPCMediaAdv, &hres);
	if (drawPage == NULL || hres != MP_NOERROR)
	{
		return false;
	}
	// V4
	// no need page width and page height
	HDC_XD hdc = MPCCreateDCPixel(mpcSession, 0, 0, 75, &hres);
	//HDC_XD hdc = MPCCreateDCPixel(mpcSession, pageWidth, pageHeight, 75, &hres);
	if (hdc == XdwNull)
	{
		return false;
	}

	if (nil == ctx)
	{
		return false;
	}

	// デバイスコンテキストの設定
	hdc->offscreen->SetMemoryDC(ctx);
	hdc->bridge->SetOffScreen(hdc->offscreen);
	
	// キャンバス作成
    // liuqw 20110622 start
    // AR NO.17847 の対応
    
    //MP_Canvas* pageCanvas = ::MPCreateCRTCanvas(mpcSession, hdc, &hres);
    MP_Dim dim;
    float dpi = Utility::GetDeviceDPI();
    MP_Canvas* pageCanvas = ::MPCreatePRTCanvasFloatDPI(mpcSession, hdc, dpi, dim, &hres);

    // liuqw 20110622 end
    
	if (hres != MP_NOERROR)
	{
		return false;
	}
	
	// 拡大
	pageCanvas->Magnify(scale, scale);
	
	/* delete for V4
	// just move context 
	// 原点移動
	MP_Integer posX = 0;
	MP_Integer posY = 0;
	
	// V4	
	if (!CGRectIsEmpty(rect)) {
		//posX = -rect.origin.x * 254000 / m_pageScale / 75;
		//posY = -rect.origin.y * 254000 / m_pageScale / 75;
		//posX = -(Utility::PixelToMMWithScale(rect.origin.x, m_pageScale));
		//posY = -(Utility::PixelToMMWithScale(rect.origin.y, m_pageScale));
		posX = rect.origin.x;
		posY = rect.origin.y;
	}

	MP_Pos pos = {posX, posY};
	if (pageCanvas->MoveOrigin(pos) != MP_NOERROR)
	{
		return false;
	}
	*/
	// V4 end.
	
	// no rotate
	hdc->offscreen->Rotate(0);
	
	MPC_AdvDrawHandle drawHandle = 0;
	// draw page
	while (!m_bBreakDrawing) {
		hres = drawPage->OnDraw(pageCanvas, &drawHandle);
		//hres = drawPage->OnDraw(pageCanvas);
		
		if (hres != MP_S_DRAW_SUSPENDED)
		{
			break;
		}
		
		if (hres == MP_S_DRAW_FINISHED)
		{
			break;
		}
	}
	
	if (pageCanvas != XdwNull) {
		pageCanvas->Destroy();
	}

	if (hdc != XdwNull) {
		MPCDeleteDC(hdc);
	}
	
	if (m_bBreakDrawing == true) {
		#ifdef _DEBUG
		NSLog(@"DrawPage() break Drawing...");
		#endif
		return false;
	}

	return true;
}

bool XdwDocumentHandle::SetFileInfo(FileInfo* fileInfo)
{
	XdwErrorCode retCode = m_AttrParser->SetFileInfo(fileInfo);
	if (retCode != XDW_ERRORCODE_SUCCESS) {
		#ifdef _DEBUG
		NSLog(@"XdwAttributeParser SetFileInfo() failed.");
		#endif
		return false;
	}
	
	return true;
}

void XdwDocumentHandle::Destroy()
{
	// clear PageInfo
	std::map<int, PageInfo*>::iterator iter;
	for (iter = m_PageInfoMap.begin(); iter != m_PageInfoMap.end(); ++iter) {
		PageInfo *tmpPageInfo = iter->second;
		delete tmpPageInfo;
	}
	m_PageInfoMap.clear();
	
	// delete fileinfo
	if (m_FileInfo) {
		delete m_FileInfo;
        m_FileInfo = NULL;
	}
	
	// delete link annatation list
	if (m_LinkAnnotList) {
		delete m_LinkAnnotList;
        m_LinkAnnotList = NULL;
	}
	
	// delete document parser
	if (m_AttrParser) {
		delete m_AttrParser;
        m_AttrParser = NULL;
	}
	
	// tongtx 2012.03.23 start
	// 選択機能の追加
	if (m_LogicAnnotList) {
		delete m_LogicAnnotList;
        m_LogicAnnotList = NULL;
	}
	// tongtx 2012.03.23 end
	
	m_bFileOpened = false;
	
	return ;
}

// liuqw 20110801 start
// ページ編集機能の追加
bool XdwDocumentHandle::IsDocumentModified()
{
	bool isDirty = false;
    if (m_AttrParser != NULL) {
		isDirty = m_AttrParser->IsProfileDirty();
    }
	return isDirty;
}

bool XdwDocumentHandle::SaveDocumentModified()
{
	XdwErrorCode errCode = XDW_ERRORCODE_INVALID_ATTRIBUTE;
    if (m_AttrParser != NULL) {
		errCode = m_AttrParser->SaveProfile();
    }
	
	if (errCode == XDW_ERRORCODE_SUCCESS)
	{
		return true;
	}
	else
	{
		return false;
	}

}

bool XdwDocumentHandle::CloseCurrentFile()
{
	bool result = false;
	if (m_AttrParser != NULL) {
		result = m_AttrParser->CloseFile();
    }
	return result;
}
// liuqw 20110801 end

LinkAnnotInfoList* XdwDocumentHandle::GetLinkAnnotationList()
{
	// Get Link annotations
	if (m_LinkAnnotList == XdwNull) {
		m_LinkAnnotList = new LinkAnnotInfoList();
		if (m_LinkAnnotList == XdwNull) {
			#ifdef _DEBUG
			NSLog(@"Create LinkAnnotInfoList failed.");
			#endif
			return XdwNull;
		}
		
		// Parser DocuWorks Document Annotations
		XdwErrorCode errCode = m_AttrParser->SetLinkAnnotInfoList(m_LinkAnnotList);
		if (errCode != XDW_ERRORCODE_SUCCESS) {
			delete m_LinkAnnotList;
			m_LinkAnnotList = XdwNull;
		}
	}

	// clear old link annotation list
	//m_LinkAnnotList->RemoveAll();

	return m_LinkAnnotList;
}

// xuxinjun 2012.03.23 start
// パーミッションの対応.
MP_Permission XdwDocumentHandle::GetPermission()
{
	MP_Permission result = 0;
	
	if (m_AttrParser != NULL) 
	{
		result = m_AttrParser->GetPermission();
    }
	
	return result;
}
// xuxinjun 2012.03.23 end

// xujj 2012.03.22 start
// 検索機能の追加
HRESULT XdwDocumentHandle::SearchText(int& nPageNum, 
									  int  startPageIndex,
									  int  endPageIndex,
									  unsigned short* text,
									  bool next, 
									  bool display, 
									  MP_TextInfo*  textInfoInput,
									  MP_TextInfo** textInfoResult, 
									  MP_AnnoInfo* annoInfo)
{
	HRESULT result = MP_S_NO_RES;
	
	if (m_AttrParser != NULL) 
	{
		result = m_AttrParser->SearchText(nPageNum, startPageIndex, endPageIndex, text, next, display, textInfoInput, textInfoResult, annoInfo);
    }
	
	return result;
}
// xujj 2012.03.22 end

// tongtx 2012.03.23 start
// 選択機能の追加
LogicAnnoInfoList* XdwDocumentHandle::GetLogicAnnotationList(int nPageNum, MP_ObjectType objectType)
{
	if (m_LogicAnnotList == NULL) 
	{
		m_LogicAnnotList = new LogicAnnoInfoList();
		if (m_LogicAnnotList == NULL) 
		{
			return NULL;
		}
		
		HRESULT hres = m_AttrParser->GetLogicAnnotationList(nPageNum, objectType, m_LogicAnnotList);
		if (hres != MP_S_OK) 
		{
			delete m_LogicAnnotList;
			m_LogicAnnotList = NULL;
		}
	}
	else
	{
		m_LogicAnnotList->RemoveAll();
		m_AttrParser->GetLogicAnnotationList(nPageNum, objectType, m_LogicAnnotList);
	}
	
	return m_LogicAnnotList;
}

bool XdwDocumentHandle::SelectText(int nPageNum, int nAnnIndex, MP_Pos start, MP_Pos end, MP_TextInfo** textInfo)
{
	bool result = false;
	if (m_AttrParser != NULL)
	{
		result = m_AttrParser->SelectText(nPageNum, nAnnIndex, start, end, textInfo);
    }
	return result;
}

bool XdwDocumentHandle::GetText(int nPageNum, int nAnnIndex, MP_Text** text, MP_Integer length, MP_TextInfo* textInfo)
{
	bool result = false;
	if (m_AttrParser != NULL) 
	{
		result = m_AttrParser->GetText(nPageNum, nAnnIndex, text, length, textInfo);
    }
	return result;
}
// tongtx 2012.03.23 end