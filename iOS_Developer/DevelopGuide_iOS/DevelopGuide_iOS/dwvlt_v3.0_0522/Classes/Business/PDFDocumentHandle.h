/*
 *  PDFDocumentHandle.h
 *  DWViewer
 *
 *  Created by jonah on 10-10-30.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _PDF_DOCUMENT_HANDLE_H_
#define _PDF_DOCUMENT_HANDLE_H_

#import "DocumentHandle.h"
#import "PDFFileInfo.h"
#import "PDFAttributeParser.h"

#import <map>

class PDFDocumentHandle : public DocumentHandle {
public:
	PDFDocumentHandle();
	~PDFDocumentHandle();
	
	virtual bool IsOpened();
	
	// xuxinjun 2012.03.23 start
	// 保護文書の対応
	//virtual XdwErrorCode OpenDocument(const char* filePath);
	virtual XdwErrorCode OpenDocument(const char* filePath, const char* password);
	// xuxinjun 2012.03.23 end

	virtual AttributeParser* GetAttributePaser();
	
	virtual FileInfo* GetFileInfo();
	virtual LinkAnnotInfoList* GetLinkAnnotationList();
	
	virtual PageInfo* GetPageInfo(int pageIndex);
    
    // liuqw 20110801 start
    // ページ編集機能の追加
    
	// xuxinjun 2012.03.23 start
	// 保護文書の対応
    //virtual XdwErrorCode OpenDocumentForUpdate(const char* filePath);
	virtual XdwErrorCode OpenDocumentForUpdate(const char* filePath, const char* password);
	// xuxinjun 2012.03.23 end
	
    int  GetStorageVersion() { return 0; };
	virtual void UpdateLinkAnnotationList();
    virtual PageInfo* GetNewPageInfo(int pageIndex);
    // liuqw 20110801 end
    
	/* page scale */
	virtual long GetScale();
	virtual void SetScale(long scale);
	
	/* can change #cdl attribute */
	virtual bool CanEnableAnnotation() { return false; };
	
	/* Set Annotation Display or not Display */
	virtual bool SetDocAnnotationDispaly(ANNOT_DISPALY);
	
	// Draw PageObject
	virtual bool DrawPage(int nPageNum, CGContextRef ctx, int scale, CGRect rect);
	void BreakDrawing() { return; }// do nothing for PDF
    
    // 2011/10/05 M.Chikyu (AR18595) start
    
	void ResetDrawing() { return; };
	
	// 2011/10/05 M.Chikyu (AR18595) end
    
	/* Destroy Document handle */
	virtual void Destroy();
	
	// liuqw 20110801 start
    // ページ編集機能の追加
	virtual bool IsDocumentModified();
	virtual bool SaveDocumentModified();
	virtual bool CloseCurrentFile(); 
	// liuqw 20110801 end
	
	// 2012.02.01(Ver2.1 New) M.Chikyu M.Chikyu
	bool IsDrawingLockUsed() {return false;};
	// 2012.02.01(Ver2.1 New) M.Chikyu M.Chikyu
	
	// xuxinjun 2012.03.23 start
	// パーミッションの対応.
	virtual MP_Permission GetPermission();
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
							   MP_AnnoInfo* annoInfo = NULL);
	// xujj 2012.03.22 end
	
	// tongtx 2012.03.23 start
	// 選択機能の追加
	virtual LogicAnnoInfoList* GetLogicAnnotationList(int nPageNum, MP_ObjectType objectType);
	virtual bool SelectText(int nPageNum, int nAnnIndex, MP_Pos start, MP_Pos end, MP_TextInfo** textInfo = NULL);
	virtual bool GetText(int nPageNum, int nAnnIndex, MP_Text** text, MP_Integer length, MP_TextInfo* textInfo = NULL);
	// tongtx 2012.03.23 end
	
protected:
	virtual bool SetFileInfo(FileInfo* fileInfo);
	
private:
	bool m_bFileOpened;
	long m_pageScale;
	std::string m_FilePath;
	PDFFileInfo* m_FileInfo;
	PDFAttributeParser* m_AttrParser;
	/* PageInfo Map */
	std::map<int,PageInfo*> m_PageInfoMap;
};

#endif	// _XDW_DOCUMENT_HANDLE_H_