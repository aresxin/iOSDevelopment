//
//  XdwAttributeParser.h
//  DWViewer
//
//  Created by dwcore_dev1 on 10/14/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#ifndef _XDW_ATTRIBUTE_PARSER_H
#define _XDW_ATTRIBUTE_PARSER_H

#import <Foundation/Foundation.h>

//#import "XdwDocuWorks.h"
#import <map>

#import "AttributeParser.h"
#import "XdwFileInfo.h"
#import "XdwPageInfo.h"
#import "LinkAnnotInfo.h"

//class declaration
struct MPCSession;
struct MPCObject;
struct MPCProfile;
struct MP_Dim;

#define CLSID_FUSEN		32794

class XdwAttributeParser : public AttributeParser {
public:
	XdwAttributeParser();
	virtual ~XdwAttributeParser();
	
	// xuxinjun 2012.03.23 start
	// 保護文書の対応
	//XdwErrorCode SetFile(const char* filePath);
	XdwErrorCode SetFile(const char* filePath, const char* password);
	// xuxinjun 2012.03.23 end

	PageInfo* GetPageInfo(const int pageIndex);
	XdwErrorCode SetFileInfo(FileInfo* fileInfo);
	
	/* can change #cdl attribute */
	bool CanEnableAnnotation();

	// set DocuWorks Document enable or disable 
	bool SetAnnotationDisplay(int mode);
	
	XdwErrorCode SetLinkAnnotInfoList(LinkAnnotInfoList* annotInfoList);
	HANDLE GetDocSession();
	//『文書情報画面』の追加 start
	MPCProfile* profile();
	//『文書情報画面』の追加 end
	
    // liuqw 20110801 start
    // ページ編集機能の追加
    
	// xuxinjun 2012.03.23 start
	// 保護文書の対応
    //virtual XdwErrorCode SetFileForUpdate(const char* filePath);
	virtual XdwErrorCode SetFileForUpdate(const char* filePath, const char* password);
	// xuxinjun 2012.03.23 end
	
    int GetStorageVersion();
	bool IsProfileDirty();
	XdwErrorCode SaveProfile();
	bool CloseFile();
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
	virtual HRESULT GetLogicAnnotationList(int nPageNum, 
										   MP_ObjectType objectType, 
										   LogicAnnoInfoList* list);
	
	virtual bool SelectText(int nPageNum, 
							int nAnnIndex,
							MP_Pos start, 
							MP_Pos end,
							MP_TextInfo** textInfo = NULL);
	
	virtual bool GetText(int nPageNum, 
						 int nAnnIndex, 
						 MP_Text** text, 
						 MP_Integer length,
						 MP_TextInfo* textInfo = NULL);
	// tongtx 2012.03.23 end
	
protected:
	virtual void Destroy();
	
private:
	/* Check DocuWorks Document is Binder */
	bool IsBinderDoc(MPCObject* const mpcProfile);
	
	/* has signature */
	bool HasSignature(MPCProfile* const mpcProfile);

	XdwErrorCode EnumBinderAttribute(MPCObject* const mpcDocObj, XdwFileInfo* fileInfo);
	// XdwErrorCode EnumPageRootAttribute(MPCObject* const mpcPageRoot);
	XdwErrorCode EnumPageRootAttribute(MPCObject* const mpcPageRoot, 
									   LinkAnnotInfoList* linkAnnoInfoList);
	// Get PageInfo
	XdwErrorCode EnumPageAttribute(MPCObject* const mpcPageRoot, 
								   const int pageIndex, 
								   XdwPageInfo *pageInfo = XdwNull,  
								   LinkAnnotInfoList* linkAnnoInfoList = XdwNull);
	
	XdwErrorCode EnumPageContent(int contentIndex, 
								 MPCObject* const mpcPageObject, 
								 XdwPageInfo* pageInfo  = XdwNull, 
								 LinkAnnotInfoList* linkAnnoInfoList = XdwNull);
	
	/* Set Info */
	XdwErrorCode SetContentInfo(int contentIndex, 
								MPCObject* const mpcIHeteroBodyCont, 
								MPCObject* const mpcPageObject, 
								XdwPageInfo* pageInfo  = XdwNull, 
								LinkAnnotInfoList* linkAnnoInfoList = XdwNull);
	
	
	/* Check Annotation */
	bool IsLinkAnnotation(MPCObject* const mpcContentObject);
	bool IsPostitAnnotation(int index, MPCObject* const mpcPageObject);
	
	/* #cdl attribute */
	bool IsShowAnnotation();
	
	/* MPCObject Attributes Methods */
	XdwErrorCode GetPostitAnnotationColor(MPCObject* const mpcIHeteroBodyCont, MP_Integer& color);
	XdwErrorCode GetAttributeDim(MPCObject* const mpcPageObject, MP_Dim& dim);
	XdwErrorCode GetAttributePosition(MPCObject* const mpcObject, 
									  int contentIndex, 
									  MP_Pos& pos);
	std::string GetAttributeName(MPCObject* const mpcObject);
	
	
	/* Error Code Process */
	XdwErrorCode GetErrorCode(const HRESULT hres) const;
	
	// tongtx 2012.03.23 start
	// 選択機能の追加
	NSString* GetTextAnnotationText(MPCObject* const annObj);
	NSString* GetNotepadAnnotationText(MPCObject* const annObj);
	// tongtx 2012.03.23 end
	
	// xujj 2012.03.22 start
	// 検索機能の追加
	bool SearchTextInHeteroBodyContent(MPCTextSearch *textSearch, 
									   MPCObject* const childObj,
									   MP_TextInfo* textInfoInput,
									   MP_TextInfo** textInfoResult);
	
	bool SearchTextInAllAnnotation(MPCTextSearch *textSearch, 
								   MPCObject* const pageObj,
								   MPCObject* const childObj,
								   MP_TextInfo** textInfoResult,
								   MP_AnnoInfo* annoInfo);
	
	bool SearchTextInNotePadAnnotation(MPCTextSearch *textSearch, 
									   MPCObject* const pageObj,
									   MPCObject* const childObj,
									   MP_TextInfo** textInfoResult,
									   MP_AnnoInfo* annoInfo);
	
	bool SearchTextInTextAnnotation(MPCTextSearch *textSearch, 
									MPCObject* const pageObj,
									MPCObject* const childObj,
									MP_TextInfo** textInfoResult,
									MP_AnnoInfo* annoInfo);

	bool SearchTextInStampAnnotation(MPCTextSearch *textSearch, 
									 MPCObject* const pageObj,
									 MPCObject* const childObj,
									 MP_TextInfo** textInfoResult,
									 MP_AnnoInfo* annoInfo);
	// xujj 2012.03.22 end
	
private:
	/* DocuWorks Document Session */
	MPCSession* m_MPCDocSession;
	/* MPCObject of DocuWorks document */
	MPCObject* m_MPCDocObject;
	/* MPCObject of page root */
	MPCObject* m_MPCPageRoot;
	/* MPCProfile Object */
	MPCProfile* m_MPCProfile;
	
	// xujj 2012.03.22 start
	// 検索機能の追加
	int			m_nPageChildNum;
	// xujj 2012.03.22 end
};

#endif	// _XDW_ATTRIBUTE_PARSER_H

