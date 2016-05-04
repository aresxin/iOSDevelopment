/*
 *  PDFDocAttributePaser.h
 *  DWViewer
 *
 *  Created by jonah on 10-10-30.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _PDF_ATTRIBUTE_PARSER_H_
#define _PDF_ATTRIBUTE_PARSER_H_

#import "AttributeParser.h"

class PDFAttributeParser : public AttributeParser
{
public:
	PDFAttributeParser();
	~PDFAttributeParser();
	
	// xuxinjun 2012.03.23 start
	// 保護文書の対応
	//virtual XdwErrorCode SetFile(const char* filePath);
	virtual XdwErrorCode SetFile(const char* filePath, const char* password);
	// xuxinjun 2012.03.23 end

	virtual PageInfo* GetPageInfo(int pageIndex);
	
	virtual XdwErrorCode SetFileInfo(FileInfo* fileInfo);
	
	virtual HANDLE GetDocSession();
    
    // liuqw 20110801 start
    // ページ編集機能の追加
	
	// xuxinjun 2012.03.23 start
	// 保護文書の対応
    //virtual XdwErrorCode SetFileForUpdate(const char* filePath);
	virtual XdwErrorCode SetFileForUpdate(const char* filePath, const char* password);
	// xuxinjun 2012.03.23 end
	
    // liuqw 20110801 end
	
	// xuxinjun 2012.03.23 start
	// パーミッションの対応.
	MP_Permission GetPermission();
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
	virtual HRESULT GetLogicAnnotationList(int nPageNum, MP_ObjectType objectType, LogicAnnoInfoList* list);
	virtual bool SelectText(int nPageNum, int nAnnIndex, MP_Pos start, MP_Pos end, MP_TextInfo** textInfo = NULL);
	virtual bool GetText(int nPageNum, int nAnnIndex, MP_Text** text, MP_Integer length, MP_TextInfo* textInfo = NULL);
	// tongtx 2012.03.23 end
	
protected:
	virtual void Destroy();
	
private:
	CGPDFDocumentRef document;	
};

#endif	// _PDF_ATTRIBUTE_PARSER_H_
