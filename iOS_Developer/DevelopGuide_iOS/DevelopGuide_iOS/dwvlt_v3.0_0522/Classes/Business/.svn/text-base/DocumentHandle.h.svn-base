/*
 *  DocumentHandle.h
 *  DWViewer
 *
 *  Created by tongjo on 10-10-30.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef _DOCUMENT_HANDLE_H_
#define _DOCUMENT_HANDLE_H_

#import <string>

#import "FileInfo.h"
#import "PageInfo.h"
#import "AttributeParser.h"
#import "LinkAnnotInfo.h"
#import "DWViewerConst.h"

#define PAGE_SCALE_MAX		17
#define PAGE_SCALE_MIN		400

class DocumentHandle
{
public:
	
	DocumentHandle() {};
	virtual ~DocumentHandle() {};
	
	/* Document Open */
	virtual bool IsOpened() = 0;
	
	// xuxinjun 2012.03.23 start
	// 保護文書の対応
	//virtual XdwErrorCode OpenDocument(const char* filePath) = 0;
	virtual XdwErrorCode OpenDocument(const char* filePath, const char* password) = 0;
	// xuxinjun 2012.03.23 end
	
	/* Docment Data */
	virtual AttributeParser* GetAttributePaser() = 0;
	virtual FileInfo* GetFileInfo() = 0;
	virtual LinkAnnotInfoList* GetLinkAnnotationList() = 0;
	virtual PageInfo* GetPageInfo(int pageIndex) = 0;
	
    // liuqw 20110801 start
    // ページ編集機能の追加
	
	// xuxinjun 2012.03.23 start
	// 保護文書の対応
    //virtual XdwErrorCode OpenDocumentForUpdate(const char* filePath) = 0;
	virtual XdwErrorCode OpenDocumentForUpdate(const char* filePath, const char* password) = 0;
	// xuxinjun 2012.03.23 end
	
    virtual int  GetStorageVersion() = 0;
	virtual void UpdateLinkAnnotationList() = 0;
    virtual PageInfo* GetNewPageInfo(int pageIndex) = 0;
    // liuqw 20110801 end
    
	/* page scale */
	virtual long GetScale() = 0;
	virtual void SetScale(long scale) = 0;
	
	/* can change #cdl attribute */
	virtual bool CanEnableAnnotation() = 0;
	
	/* Set Annotation Display or not Display */
	virtual bool SetDocAnnotationDispaly(ANNOT_DISPALY) = 0;
	
	/* Draw Page */
	virtual bool DrawPage(int nPageNum, CGContextRef ctx, int scale, CGRect rect) = 0;
	
	// if document support is method.
	virtual void BreakDrawing() = 0;
    
    // 2011/10/05 M.Chikyu (AR18595) start
	virtual void ResetDrawing() = 0;
	// 2011/10/05 M.Chikyu (AR18595) end
	
	/* Destroy Document handle */
	virtual void Destroy() = 0;
	
	// liuqw 20110801 start
    // ページ編集機能の追加
	virtual bool IsDocumentModified() = 0;
	virtual bool SaveDocumentModified() = 0;
	virtual bool CloseCurrentFile() = 0;
	// liuqw 20110801 end
	
	// 2012.02.01(Ver2.1 New) M.Chikyu M.Chikyu
	virtual bool IsDrawingLockUsed() = 0;
	// 2012.02.01(Ver2.1 New) M.Chikyu M.Chikyu
	
	// xuxinjun 2012.03.23 start
	// パーミッションの対応.
	
	virtual MP_Permission GetPermission() = 0;
	
	// xuxinjun 2012.03.23 end
	
	// xujj 2012.03.22 start
	// 検索機能の追加
	virtual HRESULT SearchText(int& nPageNum, 
							   int  startPageIndex,
							   int  endPageIndex,
							   unsigned short* text, 
							   bool next = true, 
							   bool display = true, 
							   MP_TextInfo*  textInfoInput = NULL,
							   MP_TextInfo** textInfoResult = NULL,
							   MP_AnnoInfo* annoInfo = NULL) = 0;
	// xujj 2012.03.22 end
	
	// tongtx 2012.03.23 start
	// 選択機能の追加
	virtual LogicAnnoInfoList* GetLogicAnnotationList(int nPageNum, MP_ObjectType objectType) = 0;
	virtual bool SelectText(int nPageNum, int nAnnIndex, MP_Pos start, MP_Pos end, MP_TextInfo** textInfo = NULL) = 0;
	virtual bool GetText(int nPageNum, int nAnnIndex, MP_Text** text, MP_Integer length, MP_TextInfo* textInfo = NULL) = 0;
	// tongtx 2012.03.23 end
	
	
protected:
	virtual bool SetFileInfo(FileInfo* fileInfo) = 0;
};

#endif	// _DOCUMENT_HANDLE_H_
