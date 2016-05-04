/*
 *  XdwDocumentHandle.h
 *  DWViewer
 *
 *  Created by jonah on 10-10-30.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef _XDW_DOCUMENT_HANDLE_H_
#define _XDW_DOCUMENT_HANDLE_H_

#import "DocumentHandle.h"
#import "XdwFileInfo.h"
#import "XdwAttributeParser.h"

#import <map>
class XdwDocumentHandle : public DocumentHandle {
public:
	XdwDocumentHandle();
	~XdwDocumentHandle();
	
	virtual bool IsOpened() { return m_bFileOpened; }
	
	// xuxinjun 2012.03.23 start
	// 保護文書の対応
	//virtual XdwErrorCode OpenDocument(const char* filePath);
	virtual XdwErrorCode OpenDocument(const char* filePath, const char* password);
	// xuxinjun 2012.03.23 end
	
	/* Docment Data */
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
	
    virtual int  GetStorageVersion();
	virtual void UpdateLinkAnnotationList();
    virtual PageInfo* GetNewPageInfo(int pageIndex);
    // liuqw 20110801 end
    
	/* page scale */
	virtual long GetScale();
	virtual void SetScale(long scale);
	
	/* can change #cdl attribute */
	virtual bool CanEnableAnnotation();
	
	/* Set Annotation Display or not Display */
	virtual bool SetDocAnnotationDispaly(ANNOT_DISPALY);
	
	/* Draw Page */
	virtual bool DrawPage(int nPageNum, CGContextRef ctx, int scale, CGRect rect);
	//virtual bool DrawPage(int nPageNum, Canvas* canvas);
	void BreakDrawing() { m_bBreakDrawing = true; };
    
    // 2011/10/05 M.Chikyu (AR18595) start
	void ResetDrawing() { m_bBreakDrawing = false; };
	// 2011/10/05 M.Chikyu (AR18595) end
	
	/* Destroy Document handle */
	virtual void Destroy();
	
	// liuqw 20110801 start
    // ページ編集機能の追加
	bool IsDocumentModified();
	bool SaveDocumentModified();
	bool CloseCurrentFile(); 
	// liuqw 20110801 end
	
	// 2012.02.01(Ver2.1 New) M.Chikyu M.Chikyu
	bool IsDrawingLockUsed() {return true;};
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
	bool m_bBreakDrawing;
	long m_pageScale;
	std::string m_FilePath;
	XdwFileInfo* m_FileInfo;
	XdwAttributeParser* m_AttrParser;
	LinkAnnotInfoList* m_LinkAnnotList;
	
	// tongtx 2012.03.23 start
	// 選択機能の追加
	LogicAnnoInfoList* m_LogicAnnotList;
	// tongtx 2012.03.23 end
	
	/* PageInfo Map */
	std::map<int,PageInfo*> m_PageInfoMap;
};

#endif	// _XDW_DOCUMENT_HANDLE_H_
