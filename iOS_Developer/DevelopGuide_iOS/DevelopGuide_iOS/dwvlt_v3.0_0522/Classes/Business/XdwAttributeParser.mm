//
//  XdwAttributeParser.m
//  DWViewer
//
//  Created by dwcore_dev1 on 10/14/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//


#include "hcntdoc.h"
#include "mppmodel.h"
#include <iostream>

// xuxinjun 2012.03.23 start
// 保護文書の対応
#include "mpcinc/dwspswdc.h"
// xuxinjun 2012.03.23 end

#import "DWViewerConst.h"
#import "XdwFileInfo.h"
#import "XdwPageInfo.h"
#import "XdwAttributeParser.h"

XdwAttributeParser::XdwAttributeParser()
: m_MPCDocSession(XdwNull)
, m_MPCDocObject(XdwNull)
, m_MPCPageRoot(XdwNull)
, m_MPCProfile(XdwNull)

// xujj 2012.03.26 start
// 検索機能の追加
, m_nPageChildNum(0)
// xujj 2012.03.26 end
{
}

XdwAttributeParser::~XdwAttributeParser()
{
	Destroy();
}


// xuxinjun 2012.03.23 start
// 保護文書の対応
//XdwErrorCode XdwAttributeParser::SetFile(const char* filePath)
XdwErrorCode XdwAttributeParser::SetFile(const char* filePath, const char* password)
// xuxinjun 2012.03.23 end

{
	HRESULT hres = MP_NOERROR;
	XdwErrorCode retCode = XDW_ERRORCODE_SUCCESS;
	
	MPCSession* mpcSession = XdwNull;
	MPCObject* mpcObject = XdwNull;
	MPCObject* mpcPageRoot = XdwNull;
	MPCProfile* mpcProfile = XdwNull;
	
	long totalPageNum = -1;
	
	// check file path
	if (filePath == XdwNull)
	{
		return XDW_ERRORCODE_INVALID_PARAMETER;
	}

	// create session
	mpcSession = ::MPCCreateMPCSession(&hres);
	if (hres != MP_NOERROR || mpcSession == XdwNull)
	{
		retCode = GetErrorCode(hres);
		goto end;
	}
	
	// Destroy old document info 
	Destroy();
	
	// open file
	mpcObject = mpcSession->OpenFile(filePath, &hres, MP_READONLY);
	if (mpcObject == XdwNull)
	{
		retCode = GetErrorCode(hres);
		goto end;
	}
	
	// get profile
	mpcProfile = (MPCProfile*)mpcObject->GetInterface(IID_MPCProfile, &hres);
	if (mpcProfile == XdwNull)
	{
		retCode = GetErrorCode(hres);
		goto end;
	}
	
	// open MP
	
	// xuxinjun 2012.03.23 start
	// 保護文書の対応
	/*
	 hres = mpcProfile->OpenMP();
	 */
	if (password == NULL)
	{
		hres = mpcProfile->OpenMP();
	}
	else
	{
		MP_AuthInfo authInfo;
		authInfo.mode = MP_AUTH_DIALOGUE;
		authInfo.perm = 0;
		
		PasswordSecurityAuthData authdata;
		authdata.size = sizeof(PasswordSecurityAuthData);
		authdata.type = 0;
		strcpy(authdata.password, password);
		
		hres = mpcProfile->OpenMP(&authInfo, &authdata);
	}
	// xuxinjun 2012.03.23 end
	
	if (hres != MP_NOERROR)
	{
		retCode = GetErrorCode(hres);
		goto end;
	}
	// AR45
	hres = mpcProfile->GetStorageVersion();
	// AR No.45
	if (hres < 7) {
		retCode = XDW_ERRORCODE_NOT_SUPPORTED_VERSION;
		goto end;
	}
	// AR45 end.
	
	// get page root
	mpcPageRoot = (MPCObject*)mpcObject->GetInterface(IID_MPCPageRoot, &hres);
	if (mpcPageRoot == XdwNull)
	{
		retCode = GetErrorCode(hres);
		goto end;
	}

	// set number of page
	totalPageNum = mpcPageRoot->GetNumberOfChildren();
	// set total page number to FileInfo
	if (totalPageNum < 0)
	{
		goto end;
	}
	else {
		// set object
		if(retCode == XDW_ERRORCODE_SUCCESS)
		{
			m_MPCDocSession = mpcSession;
			m_MPCDocObject = mpcObject;
			m_MPCPageRoot = mpcPageRoot;
			m_MPCProfile = mpcProfile;

			return retCode;
		}
	}
	// DocuWorks Document don't have page
	/*
	 else if (totalPageNum == 0)
	 {
	 // set object
	 m_MPCSession = mpcSession;
	 m_MPCObject = mpcObject;
	 m_MPCPageRoot = mpcPageRoot;
	 m_MPCProfile = mpcProfile;
	 m_FileInfo = fileInfo;

	 // return error
	 NSLog(@"m_MPCPageRoot->GetNumberOfChildren() == 0");
	 errCode = kXdwErrorCodePageNotExisted;
	 goto no_page;
	 }
	 */
	
end:
	// close file
	if (mpcSession != XdwNull)
	{
		if (mpcObject != XdwNull)
		{
			mpcSession->CloseFile(mpcObject, 0);
		}
		::MPCDestroyMPCSession(mpcSession);
		mpcSession = NULL;
	}

	return retCode;
}

PageInfo* XdwAttributeParser::GetPageInfo(const int pageIndex)
{
	XdwErrorCode retCode = XDW_ERRORCODE_SUCCESS;
	XdwPageInfo *xdwPageInfo = XdwNull;

	if (pageIndex < 0) {
		return XdwNull;
	}
	
	xdwPageInfo = new XdwPageInfo();
	if (xdwPageInfo == XdwNull) {
		return NULL;
	}
	
	// set page info
	retCode = EnumPageAttribute(m_MPCPageRoot, pageIndex, xdwPageInfo);
	if (retCode != XDW_ERRORCODE_SUCCESS) {
		delete xdwPageInfo;
		return XdwNull;
	}
	
	return xdwPageInfo;
}

XdwErrorCode XdwAttributeParser::SetFileInfo(FileInfo* fileInfo)
{
	XdwErrorCode retCode = XDW_ERRORCODE_SUCCESS;
	
	if (fileInfo == XdwNull) {
		return XDW_ERRORCODE_ERROR;
	}
	
	XdwFileInfo* xdwFileInfo = static_cast<XdwFileInfo*>(fileInfo);
	long pageCnt = m_MPCPageRoot->GetNumberOfChildren();
	if (pageCnt < 0) {
		retCode = XDW_ERRORCODE_INVALID_PAGE_NUM;
	}
	
	// set page count
	xdwFileInfo->SetPageCount(pageCnt);

	// set signature for fileinfo
	xdwFileInfo->SetSignature(HasSignature(m_MPCProfile));
	
	// check annotation can setting
	// modify by liuqw
	//xdwFileInfo->SetAnnotationDisplay(CanEnableAnnotation());
	xdwFileInfo->SetAnnotationDisplay(IsShowAnnotation());
		
	// check if DocuWorks document is Binder or not
	bool isBinder = IsBinderDoc(m_MPCProfile);
	xdwFileInfo->SetBinder(isBinder);
	
	// TODO: Jonah
	// set file doc attributes
	if (isBinder) {
		// set Binder info to fileinfo
		retCode = EnumBinderAttribute(m_MPCDocObject, xdwFileInfo);
	}
	
	return retCode;
}

HANDLE XdwAttributeParser::GetDocSession()
{
	return m_MPCDocSession;
}

XdwErrorCode XdwAttributeParser::SetLinkAnnotInfoList(LinkAnnotInfoList* annotInfoList)
{
	XdwErrorCode retCode = XDW_ERRORCODE_SUCCESS;
	
	// Get All annotation( link annotation and postit annotation)
	long pageCnt = m_MPCPageRoot->GetNumberOfChildren();
	if (pageCnt < 0) {
		retCode = GetErrorCode(pageCnt);
		return retCode;
	}
	
	retCode = EnumPageRootAttribute(m_MPCPageRoot, annotInfoList);
	
	return retCode;
}


void XdwAttributeParser::Destroy()
{	
	if (m_MPCDocSession != XdwNull)
	{
		if (m_MPCDocObject != XdwNull)
		{
			m_MPCDocSession->CloseFile(m_MPCDocObject, 0);
		}
		::MPCDestroyMPCSession(m_MPCDocSession);
		m_MPCDocSession = XdwNull;
	}
	
	m_MPCDocObject = XdwNull;
	m_MPCProfile = XdwNull;
	m_MPCPageRoot = XdwNull;
}


#pragma mark -
#pragma mark Private Methods

#pragma mark Check DocuWorks Document Specific Attribute
// Check DocuWorks Document is Binder
bool XdwAttributeParser::IsBinderDoc(MPCObject* const mpcProfile)
{
	// TOOD: Check binder type
	MP_ObjectType objType = mpcProfile->GetClassID();
	if (objType == CLSID_BINDER) {
		return true;
	}
	
	return false;
}

bool XdwAttributeParser::HasSignature(MPCProfile* const mpcProfile)
{
	HRESULT signCnt = mpcProfile->GetNumberOfSignatures();
	if (signCnt > 0) {
		return true;
	}
	else if (signCnt < 0) {
		GetErrorCode(signCnt);
	}
	
	return false;
}

bool XdwAttributeParser::IsLinkAnnotation(MPCObject* const mpcContentObject)
{
	// link annotation ID(0xC02F)
	if (mpcContentObject->GetClassID() == 0xC02F) {
		return true;
	}
	
	return false;
}

bool XdwAttributeParser::IsPostitAnnotation(int contentIndex, MPCObject* const mpcPageObject)
{
	MP_Integer intValue = 0;
	
	MP_AValue aValue = { sizeof(MP_Integer), MP_A_INT, &intValue };
	if (mpcPageObject->GetPartAttribute(contentIndex, "#bi", &aValue) == MP_NOERROR) {
		return true;
	}
	
	return false;
}

bool XdwAttributeParser::IsShowAnnotation()
{
	if (CanEnableAnnotation()) {
		const MP_AName *valName = "#cdl";
		MP_Integer cdlValue = 0;
		MP_AValue value = { sizeof(MP_Integer), MP_A_INT, &cdlValue };
		
		m_MPCProfile->GetAttribute(valName, &value);
		
		if (cdlValue == 0) {
			return true;
		}
	}
	return false;
}

bool XdwAttributeParser::CanEnableAnnotation()
{
	const MP_AName *valName = "#cdl";
	MP_Integer cdlValue = 0;
	MP_AValue value = { sizeof(MP_Integer), MP_A_INT, &cdlValue };
	
	HRESULT hres = m_MPCProfile->GetAttribute(valName, &value);
	if (hres == MP_NOERROR) {
		return true;
	}
	else if (hres == MP_E_INVALIDARG) {
		return false;
	}
	else {
		GetErrorCode(hres);
	}

	return false;
}

// Check DocuWorks Document enable or disable 
bool XdwAttributeParser::SetAnnotationDisplay(int mode)
{
	MP_Integer isDisplay = ((mode == 1) ? 0 : 1);

	HRESULT hres = MP_NOERROR;
	MP_AValue aValue = { sizeof(MP_Integer), MP_A_INT, &isDisplay };
	hres = m_MPCProfile->SetAttribute("#cdl", &aValue);
	if (hres == MP_NOERROR) {
		return true;
	} else if (hres == MP_E_INVALIDARG) {
		return false;
	} else {
		GetErrorCode(hres);
	}

	return false;
}

#pragma mark -
#pragma mark DocuWorks Document Parser
XdwErrorCode XdwAttributeParser::EnumBinderAttribute(MPCObject* const mpcDocObj, 
													 XdwFileInfo* fileInfo)
{
	HRESULT hres = MP_NOERROR;
	XdwErrorCode retCode = XDW_ERRORCODE_SUCCESS;
	
	// Get Document Root
	MPCObject* mpcDocRoot = (MPCObject*)mpcDocObj->GetInterface(IID_MPCDocRoot, &hres);
	if (hres != MP_NOERROR || mpcDocRoot == XdwNull) {
		retCode = GetErrorCode(hres);
		return retCode;
	}
	
	// Get number of document in Binder
	MP_Integer docCnt = mpcDocRoot->GetNumberOfChildren();
	if (docCnt < 0) {
		retCode = GetErrorCode(docCnt);
		return retCode;
	}

	fileInfo->SetBinderCount(docCnt);
	
	// add document name
	MPCObject *mpcPageRoot = XdwNull;
	MPCObject *mpcOocContent = XdwNull;
	for (int i = 0; i < docCnt; ++i) {
		mpcOocContent = mpcDocRoot->GetNthChild(i, &hres);
		if (hres != MP_NOERROR || mpcOocContent == XdwNull) {
			retCode = GetErrorCode(hres);
			return retCode;
		}

		// set pageCnt for every doc in binder
		int pageCnt = 0;
		mpcPageRoot = (MPCObject*)mpcOocContent->GetInterface(IID_MPCPageRoot);
		if (mpcPageRoot != XdwNull) {
			pageCnt = mpcPageRoot->GetNumberOfChildren();
			if (pageCnt < 0) {
				retCode = GetErrorCode(pageCnt);
				break;
			}
		}
		
		// page number and doc name
		std::string docName = GetAttributeName(mpcOocContent);
		
		// add current doc to fileinfo
		fileInfo->AddDocInfo(docName, pageCnt);
	}

	return retCode;
}

XdwErrorCode XdwAttributeParser::EnumPageRootAttribute(MPCObject* const mpcPageRoot, 
													   LinkAnnotInfoList* linkAnnoInfoList)
{
	XdwErrorCode retCode = XDW_ERRORCODE_SUCCESS;

	
	MP_Integer pageNum = mpcPageRoot->GetNumberOfChildren();
	if (pageNum < 0) {
		retCode = GetErrorCode(pageNum);
		
		return retCode;
	}
	
	for (int i = 0; i < pageNum; ++i) {
		XdwPageInfo pageInfo;
		retCode = EnumPageAttribute(mpcPageRoot, i, &pageInfo, linkAnnoInfoList);
		if (retCode != XDW_ERRORCODE_SUCCESS) {
			return retCode;
		}
	}

	return retCode;
}

XdwErrorCode XdwAttributeParser::EnumPageAttribute(MPCObject* const mpcPageRoot, 
												   const int pageIndex, 
												   XdwPageInfo *pageInfo, 
												   LinkAnnotInfoList* linkAnnoInfoList)
{
	HRESULT hres = MP_NOERROR;
	XdwErrorCode retCode = XDW_ERRORCODE_SUCCESS;
	

	MPCObject *mpcPageObject = mpcPageRoot->GetNthChild(pageIndex, &hres);
	if (hres != MP_NOERROR) {
		return XDW_ERRORCODE_ERROR;
	}

	// get page size
	MP_Dim pageDim = { 0, 0 };
	retCode = GetAttributeDim(mpcPageObject, pageDim);
	if (retCode != XDW_ERRORCODE_SUCCESS) {
		return retCode;
	}
	// add by liuqw
	RECT rect = {0, 0, pageDim.cx, pageDim.cy};
	
	// set page width and height
	if (pageInfo != XdwNull) {
		pageInfo->SetPageWidth(pageDim.cx);
		pageInfo->SetPageHeight(pageDim.cy);
		// add by liuqw
		pageInfo->SetPageRectangle(rect);
		
		pageInfo->SetPageIndex(pageIndex);
		pageInfo->SetPageObject(mpcPageObject);
	}

	// Get page content
	MP_Integer contentCnt = mpcPageObject->GetNumberOfChildren();
	if (contentCnt < 0) {
		return XDW_ERRORCODE_ERROR;
	}

	// only set page info, no need get link annotation info
	for (int i = 0; i < contentCnt; ++i) {
		retCode = EnumPageContent(i, mpcPageObject, pageInfo, linkAnnoInfoList);
		if (retCode != XDW_ERRORCODE_SUCCESS) {
			break;
		}
	}

	return retCode;
}

XdwErrorCode XdwAttributeParser::EnumPageContent(int contentIndex, 
												 MPCObject* const mpcPageObject, 
												 XdwPageInfo* pageInfo, 
												 LinkAnnotInfoList* linkAnnoInfoList)
{
	XdwErrorCode retCode = XDW_ERRORCODE_SUCCESS;

	if (contentIndex < 0) {
		return XDW_ERRORCODE_INVALID_PAGE_NUM;
	}
	
	int contentCnt = mpcPageObject->GetNumberOfChildren();
	if (contentCnt < 0) {
		return GetErrorCode(contentCnt);
	}
	
	// get content attribute
	HRESULT hres = MP_NOERROR;
	IHeteroBodyCont *mpcIHeteroBodyCont = XdwNull;
	mpcIHeteroBodyCont = (IHeteroBodyCont*)mpcPageObject->GetNthChild(contentIndex, &hres);
	if (hres != MP_NOERROR || mpcIHeteroBodyCont == XdwNull) {
		return GetErrorCode(hres);
	}
	
	// add content info to pageinfo and linkannotationinfo
	retCode = SetContentInfo(contentIndex, mpcIHeteroBodyCont, mpcPageObject, 
							 pageInfo, linkAnnoInfoList);
	if (retCode != XDW_ERRORCODE_SUCCESS) {
		return retCode;
	}
	
	return XDW_ERRORCODE_SUCCESS;
}

// annotation parser
XdwErrorCode XdwAttributeParser::SetContentInfo(int contentIndex, 
												MPCObject* const mpcIHeteroBodyCont, 
												MPCObject* const mpcPageObject, 
												XdwPageInfo* pageInfo, 
												LinkAnnotInfoList* linkAnnoInfoList)
{
	XdwErrorCode retCode = XDW_ERRORCODE_SUCCESS;

	// caculate content position
	MP_Pos contentPos = { 0, 0 };
	retCode = GetAttributePosition(mpcPageObject, contentIndex, contentPos);
	if (retCode != XDW_ERRORCODE_SUCCESS) {
		return retCode;
	}
	
	// Check content annotation
	if (IsPostitAnnotation(contentIndex, mpcPageObject)) {
		MP_Dim dim = { 0, 0 };
		retCode = GetAttributeDim(mpcIHeteroBodyCont, dim);
		if (retCode != XDW_ERRORCODE_SUCCESS) {
			return retCode;
		}
		
		long curContentRight = contentPos.x + dim.cx;
		long curContentBottom = contentPos.y + dim.cy;

		// set page information
		if (pageInfo) {
			RECT pageRect = pageInfo->GetPageRectangle();
			// set real size of page
			if (contentPos.x < pageRect.left) {
				pageRect.left = contentPos.x;
			}
			
			if (contentPos.y < pageRect.top) {
				pageRect.top = contentPos.y;
			}
			
			if (curContentRight > pageRect.right) {
				pageRect.right = curContentRight;
			}
			
			if (curContentBottom > pageRect.bottom) {
				pageRect.bottom = curContentBottom;
			}
			
			pageInfo->SetPageRectangle(pageRect);
		}
		
		// Jonah add get PostitAnnotation color
		long colorValue = 0;
		GetPostitAnnotationColor(mpcIHeteroBodyCont, colorValue);
		
		// set annotation to link list
		if (linkAnnoInfoList != XdwNull) {
			LinkAnnotInfo* contentInfo = new LinkAnnotInfo();
			if (contentInfo == XdwNull) {
				return XDW_ERRORCODE_INSUFFICIENT_MEMORY;
			}
			
			// set annotation info
			contentInfo->SetContentPos(contentPos);
			contentInfo->SetContentDim(dim);
			contentInfo->SetContent(mpcIHeteroBodyCont);
			contentInfo->SetXdwPageNum(pageInfo->GetPageIndex());
			// add by tongjo
			contentInfo->SetAnnotationColor(colorValue);
			linkAnnoInfoList->Add(contentInfo);
		}
	}
	else if (IsLinkAnnotation(mpcIHeteroBodyCont)) {
		if (linkAnnoInfoList != XdwNull) {
			LinkAnnotInfo* contentInfo = new LinkAnnotInfo();
			if (contentInfo == XdwNull) {
				return XDW_ERRORCODE_INSUFFICIENT_MEMORY;
			}
			MP_Dim dim = { 0, 0 };
			retCode = GetAttributeDim(mpcIHeteroBodyCont, dim);
			
			// Set information for content
			contentInfo->SetContentPos(contentPos);
			contentInfo->SetContentDim(dim);
			contentInfo->SetContent(mpcIHeteroBodyCont);
			contentInfo->SetXdwPageNum(pageInfo->GetPageIndex());
			linkAnnoInfoList->Add(contentInfo);
		}
	}
	else {
		// content object is other type
		//MP_ObjectType objType = mpcIHeteroBodyCont->GetClassID();
		//NSLog(@"Other Object(ID:0x%04x)", objType);
	}

	return retCode;
}

#pragma mark -
#pragma mark Get Attribute from MPCObject 
XdwErrorCode XdwAttributeParser::GetPostitAnnotationColor(MPCObject* const mpcIHeteroBodyCont,
														  MP_Integer& color)
{
	MP_ObjectType objType = mpcIHeteroBodyCont->GetClassID();
	if (objType == CLSID_FUSEN) {
		MP_AValue aValue = { sizeof(MP_Integer), MP_A_INT, &color };
		if (mpcIHeteroBodyCont->GetAttribute("FSN_COLOR", &aValue) == MP_NOERROR) {
			return XDW_ERRORCODE_SUCCESS;
		}
	}
	
	return XDW_ERRORCODE_ERROR;
}

XdwErrorCode XdwAttributeParser::GetAttributeDim(MPCObject* const mpcObject, MP_Dim& dim)
{
	HRESULT hres = MP_NOERROR;
	
	const char* XDWDOC_ATTRIBUTE_DIM = "#dim";
	MP_AValue dimValue = { sizeof(MP_Dim), MP_A_DIM, &dim };
	hres = mpcObject->GetAttribute(XDWDOC_ATTRIBUTE_DIM, &dimValue);
	if (hres != MP_NOERROR) {
		return GetErrorCode(hres);
	}
	
	return XDW_ERRORCODE_SUCCESS;
}

// lixin 20110818 ページ編集機能の追加  DW_iPhoneViewer_20 start
bool XdwAttributeParser::CloseFile()
{
	if (m_MPCDocSession != NULL && m_MPCProfile != NULL) 
	{
		HRESULT hres = MP_NOERROR;
		hres = m_MPCDocSession->CloseFile(m_MPCDocObject, 0);
		
		if (hres == MP_S_OK) 
		{
			return true;
		}
	}
	return false;
}
// DW_iPhoneViewer_20 end

XdwErrorCode XdwAttributeParser::GetAttributePosition(MPCObject* const mpcObject, 
													  int contentIndex, MP_Pos& pos)
{
	HRESULT hres = MP_NOERROR;
	
	const char* XDWDOC_ATTRIBUTE_POS = "#pos";
	MP_AValue posValue = { sizeof(MP_Pos), MP_A_POS, &pos };
	hres = mpcObject->GetPartAttribute(contentIndex, XDWDOC_ATTRIBUTE_POS, &posValue);
	if (hres != MP_NOERROR) {
		return GetErrorCode(hres);
	}
	
	return XDW_ERRORCODE_SUCCESS;
}

std::string XdwAttributeParser::GetAttributeName(MPCObject* const mpcObject)
{
	if (mpcObject == NULL) {
		return NULL;
	}

	HRESULT hres = MP_NOERROR;
	//char* nameValue = XdwNull;
	std::string docName;
	
	NSAutoreleasePool * tmppool = [[NSAutoreleasePool alloc] init];

	// lixin 20110623 DW_iPhoneEnhance_12 start
	// AR.17858 の対応
	/*	
	 const char* XDWDOC_ATTRIBUTE_UNICODE = "#unicode";
	 MP_Integer val = 0;
	 MP_AValue uniCodeValue = { sizeof(MP_Integer), MP_A_INT, &val };
	 
	 hres = mpcObject->GetAttribute(XDWDOC_ATTRIBUTE_UNICODE, &uniCodeValue);
	 
     // val == 0 : UniCode 
     //if (hres == MP_NOERROR && val == 0) {
	 */
	MP_AValue aValue = { 0, MP_A_OCTS, (void*)NULL };
	mpcObject->GetAttribute("#name", &aValue);
	
	if (aValue.asize == 0) {
	// lixin 20110623 DW_iPhoneEnhance_12 end
		MP_AValue value = { 0 };
		mpcObject->GetAttribute("#name(w", &value);
		
		WCHAR* uniName = new WCHAR[value.asize + 1];
		memset(uniName, 0x00, (value.asize + 1) * sizeof(WCHAR));
		value.adata = uniName;
		
		if ((hres = mpcObject->GetAttribute("#name(w", &value)) != MP_NOERROR) {
			delete[] uniName;
			goto End;
		}
		
		// 2010/12/17 zhongchao modified this for AR17598 begin
		/*
		NSData* unicodeData = [NSData dataWithBytes:uniName length:value.asize];
		NSString* unicodeString = 
		[[NSString alloc] initWithData:unicodeData encoding:NSUnicodeStringEncoding];
		const char* chValue = [unicodeString UTF8String];
		nameValue = new char[strlen(chValue) + 1];
		memset(nameValue, 0x00, (strlen(chValue) + 1) * sizeof(char));
		memcpy(nameValue, chValue, strlen(chValue));
		[unicodeString release];
		 */
		
		NSString *unicodeString = [NSString stringWithCharacters:uniName length:(value.asize)];
        if (unicodeString != nil) {
            docName = [unicodeString UTF8String];
        }
		
		if (uniName != NULL) {
			delete[] uniName;
		}
		// 2010/12/17 zhongchao modified this for AR17598 end
	}
	else {
		char chValue[DOC_NAME_SIZE] = { 0 };
		MP_AValue value = { sizeof(chValue), MP_A_OCTS, &chValue };
		if ((hres = mpcObject->GetAttribute("#name", &value)) != MP_NOERROR) {
			goto End;
		}
		
		// 2010/12/17 zhongchao modified this for AR17598 begin
		/*
		nameValue = new char[strlen(chValue) + 1];
		memset(nameValue, 0x00, (strlen(chValue) + 1) * sizeof(char));
		memcpy(nameValue, chValue, strlen(chValue));
		*/
        
        // 20110701 M.Chikyu (AR17887,AR17889) start
		// マルチバイトでの文字コードを言語設定で決定する
		
		/*
        // 3.6 バインダ文書対応 の対応 start
        // change by lixin 20110608 DW_iPhoneEnhance_12
        NSString *shiftjisString = [NSString stringWithCString:chValue 
                                                      encoding:NSShiftJISStringEncoding];
        docName = [shiftjisString UTF8String];
        // 3.6 バインダ文書対応 の対応 end
        */
		
		NSString *encString = NSLocalizedString(@"LOCAL_ENCODING", nil);
		NSStringEncoding nsEnc;
		
		if      ([encString isEqualToString:@"SHIFTJIS_CHARSET"])
		{
			nsEnc = NSShiftJISStringEncoding;
		}
		else if ([encString isEqualToString:@"ANSI_CHARSET"])
		{
			nsEnc = NSWindowsCP1252StringEncoding;
		}
		else if ([encString isEqualToString:@"GB2312_CHARSET"])
		{
			nsEnc = CFStringConvertEncodingToNSStringEncoding(kCFStringEncodingDOSChineseSimplif);
		}
		else if ([encString isEqualToString:@"CHINESEBIG5_CHARSET"])
		{
			nsEnc = CFStringConvertEncodingToNSStringEncoding(kCFStringEncodingDOSChineseTrad);
		}
		else if ([encString isEqualToString:@"HANGEUL_CHARSET"])
		{
			nsEnc = CFStringConvertEncodingToNSStringEncoding(kCFStringEncodingDOSKorean);
		}
		else if ([encString isEqualToString:@"THAI_CHARSET"])
		{
			nsEnc = CFStringConvertEncodingToNSStringEncoding(kCFStringEncodingDOSThai);
		}
		else
		{
			nsEnc = NSWindowsCP1252StringEncoding;
		}
		
		
		NSString *localString = [NSString stringWithCString:chValue
												   encoding:nsEnc];
        
        if (localString != nil) {
            docName = [localString UTF8String];
        }
		
		// 20110701 M.Chikyu (AR17887,AR17889) end
        
		// 2010/12/17 zhongchao modified this for AR17598 end
	}

	// 2010/12/17 zhongchao modified this for AR17598 begin
	//docName = nameValue;
	//free(nameValue);
	// 2010/12/17 zhongchao modified this for AR17598 end
End:
	[tmppool release];
	
	return docName;
}

#pragma mark -
#pragma mark Error Code Process
XdwErrorCode XdwAttributeParser::GetErrorCode(const HRESULT hres) const
{
	XdwErrorCode errCode;
	
	switch (hres) {
		case MP_NOERROR:
			errCode = XDW_ERRORCODE_SUCCESS;
			break;
			
		case MP_E_BAD_FORMAT:
		case MP_E_BAD_FORMAT_ODOA:
		case MP_E_BAD_CHECKSUM:
			// i don't found bad format error code
			errCode = XDW_ERRORCODE_BAD_CHECKSUM;
			break;
			
		case MP_E_ACCESSDENIED:
		case MP_E_FILE_NOT_FOUND:
			/*! ファイルアクセス違反 */
			errCode = XDW_ERRORCODE_FILE_ACCESS_FAULT;
			break;
			
			/*
			 case MP_E_OLDFORMAT:
			 case MP_E_NEWFORMAT:
			 errorCode = kXdwErrorCodeNotSupportedVersion;
			 break;
			 */
			
		case MP_S_PROTECTED_BY_PSWD:
		case MP_S_PROTECTED_BY_DDSA:
		case MP_S_PROTECTED_BY_PSWD128:
		case MP_S_PROTECTED_BY_PKST:
		case MP_S_PROTECTED_BY_SDES:
		case MP_S_PROCESS_CANCELED:
		case MP_E_AUTH_FAILED:
		case MP_E_AUTH_FAILED_NOMESSAGE:
		case MP_E_INVALID_CALL:
			/*! 対応していない保護文書である*/
			errCode = XDW_ERRORCODE_CRYPT_ERROR;
			break;
			
			/* WinMobile memory card, file read failed */
		case MP_E_INVALID_NAME:
			errCode = XDW_ERRORCODE_FILE_OPEN_ERROR;
			break;
			
		case MP_E_INSUFFICIENT_BUFFER:
		case MP_E_DISK_FULL:
		case MP_E_OUTOFMEMORY:
			/*!< メモリの確保が不可能	*/
			errCode = XDW_ERRORCODE_INSUFFICIENT_MEMORY;
			break;
			
		default:
			if ( hres >= MP_S_OPEN_SECURITY_ID_START &&
				hres < MP_S_OPEN_SECURITY_ID_START + MP_S_OPEN_SECURITY_NUM ) {
				// 
				errCode = XDW_ERRORCODE_CRYPT_ERROR;
			} else {
				// file open error
				errCode = XDW_ERRORCODE_FILE_OPEN_ERROR;
			}
			break;			
	}
	
	return errCode;
}

//『文書情報画面』の追加 start
MPCProfile* XdwAttributeParser::profile()
{
	return m_MPCProfile;
}
//『文書情報画面』の追加 end

// liuqw 20110801 start
// ページ編集機能の追加

// xuxinjun 2012.03.23 start
// 保護文書の対応
//XdwErrorCode XdwAttributeParser::SetFileForUpdate(const char* filePath)
XdwErrorCode XdwAttributeParser::SetFileForUpdate(const char* filePath, const char* password)
// xuxinjun 2012.03.23 end

{
	HRESULT hres = MP_NOERROR;
	XdwErrorCode retCode = XDW_ERRORCODE_SUCCESS;
	
	MPCSession* mpcSession = XdwNull;
	MPCObject* mpcObject = XdwNull;
	MPCObject* mpcPageRoot = XdwNull;
	MPCProfile* mpcProfile = XdwNull;
	
	long totalPageNum = -1;
	
	// check file path
	if (filePath == XdwNull)
	{
		return XDW_ERRORCODE_INVALID_PARAMETER;
	}
    
	// create session
	mpcSession = ::MPCCreateMPCSession(&hres);
	if (hres != MP_NOERROR || mpcSession == XdwNull)
	{
		retCode = GetErrorCode(hres);
		goto end;
	}
	
	// Destroy old document info 
	Destroy();
	
	// open file
	mpcObject = mpcSession->OpenFile(filePath, &hres, MP_UPDATE);
	if (hres != MP_NOERROR || mpcObject == XdwNull)
	{
		mpcObject = mpcSession->OpenFile(filePath, &hres, MP_READONLY);
	}
    
	if (mpcObject == XdwNull)
	{
		retCode = GetErrorCode(hres);
		goto end;
	}
	
	// get profile
	mpcProfile = (MPCProfile*)mpcObject->GetInterface(IID_MPCProfile, &hres);
	if (mpcProfile == XdwNull)
	{
		retCode = GetErrorCode(hres);
		goto end;
	}
	
	// open MP
	// xuxinjun 2012.03.23 start
	// 保護文書の対応
	if (password == NULL)
	{
		hres = mpcProfile->OpenMP();
	}
	else
	{
		MP_AuthInfo authInfo;
		authInfo.mode = MP_AUTH_DIALOGUE;
		authInfo.perm = 0;
		
		PasswordSecurityAuthData authdata;
		authdata.size = sizeof(PasswordSecurityAuthData);
		authdata.type = 0;
		strcpy(authdata.password, password);
		
		hres = mpcProfile->OpenMP(&authInfo, &authdata);
	}
	// xuxinjun 2012.03.23 end
	
	if (hres != MP_NOERROR)
	{
		retCode = GetErrorCode(hres);
		goto end;
	}
	// AR45
	hres = mpcProfile->GetStorageVersion();
	// AR No.45
	if (hres < 7) {
		retCode = XDW_ERRORCODE_NOT_SUPPORTED_VERSION;
		goto end;
	}
	// AR45 end.
	
	// get page root
	mpcPageRoot = (MPCObject*)mpcObject->GetInterface(IID_MPCPageRoot, &hres);
	if (mpcPageRoot == XdwNull)
	{
		retCode = GetErrorCode(hres);
		goto end;
	}
    
	// set number of page
	totalPageNum = mpcPageRoot->GetNumberOfChildren();
	// set total page number to FileInfo
	if (totalPageNum < 0)
	{
		goto end;
	}
	else {
		// set object
		if(retCode == XDW_ERRORCODE_SUCCESS)
		{
			m_MPCDocSession = mpcSession;
			m_MPCDocObject = mpcObject;
			m_MPCPageRoot = mpcPageRoot;
			m_MPCProfile = mpcProfile;
            
			return retCode;
		}
	}
	// DocuWorks Document don't have page
	
end:
	// close file
	if (mpcSession != XdwNull)
	{
		if (mpcObject != XdwNull)
		{
			mpcSession->CloseFile(mpcObject, 0);
		}
		::MPCDestroyMPCSession(mpcSession);
		mpcSession = NULL;
	}
    
	return retCode;
    
}

int XdwAttributeParser::GetStorageVersion()
{
    int version = DW_FILEVERSION_V1;
    if(m_MPCProfile != NULL)
    {
        version = m_MPCProfile->GetStorageVersion();
    }
       
    return version;
}

bool XdwAttributeParser::IsProfileDirty()
{
	if (m_MPCDocSession != NULL && m_MPCProfile != NULL) 
	{
		HRESULT hres = MP_NOERROR;
		hres = m_MPCDocSession->IsDirty(m_MPCProfile);
		
		if (hres == MP_S_OK) 
		{
			return true;
		}
	}
	return false;
}

XdwErrorCode XdwAttributeParser::SaveProfile()
{
    XdwErrorCode errCode;
	
	if (m_MPCDocSession != NULL && m_MPCProfile != NULL) {
		HRESULT hres = MP_NOERROR;
		
		hres = m_MPCDocSession->Save(m_MPCProfile);
		
		if (hres == MP_NOERROR) 
		{
			errCode = XDW_ERRORCODE_SUCCESS;
		}
		else
		{
			errCode = XDW_ERRORCODE_INVALID_ATTRIBUTE;
		}
	}  
	return errCode;
}
// liuqw 20110801 end

// xuxinjun 2012.03.23 start
// パーミッションの対応.
MP_Permission XdwAttributeParser::GetPermission()
{
	return m_MPCProfile->GetPermission();
}
// xuxinjun 2012.03.23 end

// xujj 2012.03.22 start
// 選択機能の追加
#pragma mark -
#pragma mark mehtod search text.
HRESULT XdwAttributeParser::SearchText(int& nPageNum, 
									   int  startPageIndex,
									   int  endPageIndex,
									   unsigned short* text, 
									   bool next, 
									   bool display,
									   MP_TextInfo*  textInfoInput,
									   MP_TextInfo** textInfoResult, 
									   MP_AnnoInfo* annoInfo)
{
	long searchResult = MP_S_NO_RES;
	
	if (text == NULL) 
	{
		m_nPageChildNum = 0;
		return searchResult;
	}
	
	HRESULT hres = MP_NOERROR;
	MPCTextSearch *textSearch = MPCCreateTextSearch(m_MPCDocSession, &hres);
	if (NULL != textSearch && hres == MP_NOERROR)
	{
		MP_FindParam param = MP_FI_ZenHan | MP_FI_Case | MP_FI_HiraKata |
		                     MP_FT_ImgPage | MP_FT_AppPage;
		
		if (display == true)
		{
			param = param | MP_FT_TextAnnotation | MP_FT_StampAnnotation;
		}
		
		if (next == true) 
		{
			param = param | MP_FD_Forward;
		}
		else
		{
			param = param | MP_FD_Backward;
		}
		
		hres = textSearch->SetParam(param, text);
		if (hres != MP_NOERROR) 
		{
			textSearch->Destroy();
			return searchResult;
		}

		// init start page index.
		int totalPageNum  = m_MPCPageRoot->GetNumberOfChildren();
		int lastPageIndex = totalPageNum - 1; 
		if (startPageIndex == -1) 
		{
			if (next == true)
			{
				startPageIndex = 0;
				
				annoInfo->annoIndex = -1;
				
				m_nPageChildNum = 0;
				
				textInfoInput = NULL;
			}
			else
			{
				startPageIndex = lastPageIndex;
				
				MPCObject *pageObj = m_MPCPageRoot->GetNthChild(startPageIndex);
				if (pageObj != NULL)
				{
					annoInfo->annoIndex = pageObj->GetNumberOfChildren();
				}
				
				m_nPageChildNum = 0;
				
				textInfoInput = NULL;
			}
		}
		
		// init end page index.
		if (endPageIndex == -1) 
		{
			if (next == true) 
			{
				endPageIndex = lastPageIndex;
			}
			else
			{
				endPageIndex = 0;
			}
		}
		
		int index = startPageIndex;
		for (; ;) 
		{
			MPCObject *pageObj = m_MPCPageRoot->GetNthChild(index);
			if (pageObj != NULL)
			{
				// Forward
				if (next == true)
				{
					if (m_nPageChildNum < 0) m_nPageChildNum = 0; 
					
					int childObjCount = pageObj->GetNumberOfChildren();
					
					for (; m_nPageChildNum < childObjCount; m_nPageChildNum++)
					{
						MPCObject *childObj = pageObj->GetNthChild(m_nPageChildNum);
						
						// 1. find in page.
						if (childObj != NULL && childObj->GetClassID() == CLSID_HETEROCONT)
						{
							bool result = SearchTextInHeteroBodyContent(textSearch, 
																		childObj, 
																		textInfoInput, 
																		textInfoResult);
							
							if (result == true) 
							{
								nPageNum = index;
								annoInfo->annoIndex = -1;
								
								searchResult = MP_S_IN_PAGE;
								break;
							}
						}
						
						if (m_nPageChildNum <= annoInfo->annoIndex)
						{
							continue;
						}
						
						// 2. find in annotation
						if (childObj != NULL) 
						{
							bool result = SearchTextInAllAnnotation(textSearch, 
																	pageObj, 
																	childObj, 
																	textInfoResult, 
																	annoInfo);
							if (result == true)
							{
								nPageNum = index;
								
								searchResult = MP_S_IN_ANNO;
								break;
							}
						}
					}
					
					if (searchResult != MP_S_NO_RES)
					{
						break;
					}
				}
				// Backward
				else
				{
					if (m_nPageChildNum <= 0)
					{
						int annObjCount = pageObj->GetNumberOfChildren();
						m_nPageChildNum = annObjCount - 1;
					}
					
					for (; m_nPageChildNum >= 0; m_nPageChildNum--)
					{
						MPCObject *childObj = pageObj->GetNthChild(m_nPageChildNum);
						
						// 1. find in page.
						if (childObj != NULL && childObj->GetClassID() == CLSID_HETEROCONT)
						{
							bool result = SearchTextInHeteroBodyContent(textSearch, 
																		childObj, 
																		textInfoInput, 
																		textInfoResult);
							
							if (result == true) 
							{
								nPageNum = index;
								annoInfo->annoIndex = -1;
								
								searchResult = MP_S_IN_PAGE;
								break;
							}
						}
						
						if (m_nPageChildNum >= annoInfo->annoIndex)
						{
							continue;
						}
						
						// 2. find in annotation
						if (childObj != NULL) 
						{
							bool result = SearchTextInAllAnnotation(textSearch, 
																	pageObj, 
																	childObj, 
																	textInfoResult, 
																	annoInfo);
							if (result == true)
							{
								nPageNum = index;

								searchResult = MP_S_IN_ANNO;
								break;
							}
						}
					}
					
					if (searchResult != MP_S_NO_RES)
					{
						break;
					}
				}
			}

			if (next == true)
			{
				if(index == lastPageIndex)
				{
					m_nPageChildNum--;
					
					searchResult = MP_S_NO_RES;
					break;
				}
				
				if (index < endPageIndex) 
				{
					index++;
				}
				else
				{
					m_nPageChildNum--;
					
					searchResult = MP_S_NO_RES;
					break;
				}
				
				annoInfo->annoIndex = -1;
				m_nPageChildNum = 0;
				textInfoInput = NULL;
			}
			else
			{
				if(index == 0)
				{
					m_nPageChildNum--;
					
					searchResult = MP_S_NO_RES;
					break;
				}
				
				if (index > endPageIndex) 
				{
					index--;
				}
				else
				{
					m_nPageChildNum--;
					
					searchResult = MP_S_NO_RES;
					break;
				}
				
				MPCObject *pageObj = m_MPCPageRoot->GetNthChild(index);
				if (pageObj != NULL)
				{
					annoInfo->annoIndex = pageObj->GetNumberOfChildren();
				}
				
				m_nPageChildNum = 0;
				textInfoInput = NULL;
			}
		}
	}
	
	textSearch->Destroy();
	
	return searchResult;
}

bool XdwAttributeParser::SearchTextInHeteroBodyContent(MPCTextSearch *textSearch,
													   MPCObject *const childObj,
													   MP_TextInfo* textInfoInput,
													   MP_TextInfo** textInfoResult)
{
	if (textSearch != NULL && childObj != NULL)
	{
		MPCFind6 *find6 = (MPCFind6*)childObj->GetInterface(IID_MPCFind6);
		if (find6 != NULL)
		{	
			MP_FindInfo findInfo  = { childObj, textInfoInput };
			MPCObject *findObject = find6->Find(textSearch, textInfoResult, &findInfo);
			if (findObject != NULL && textInfoResult != NULL) 
			{
				findObject->Destroy();
				return true;
			} 
		}
	}
	
	return false;
}

bool XdwAttributeParser::SearchTextInAllAnnotation(MPCTextSearch *textSearch, 
												   MPCObject *const pageObj, 
												   MPCObject *const childObj, 
												   MP_TextInfo **textInfoResult, 
												   MP_AnnoInfo *annoInfo)
{
	bool result = false;
	
	if (textSearch != NULL && pageObj != NULL && childObj != NULL)
	{
		// 1. find notepad
		if (childObj->GetClassID() == ANTYPE_NOTEPAD) 
		{
			result = SearchTextInNotePadAnnotation(textSearch, 
												   pageObj,
												   childObj,
												   textInfoResult,
												   annoInfo);
		}
		
		// 2. find textanno
		if (childObj->GetClassID() == ANTYPE_TEXT) 
		{
			result = SearchTextInTextAnnotation(textSearch, 
												pageObj, 
												childObj, 
												textInfoResult, 
												annoInfo);
		}
		
		// 3. find stamp
		if (childObj->GetClassID() == ANTYPE_STAMP || 
			childObj->GetClassID() == ANTYPE_STAMP_ENG || 
			childObj->GetClassID() == ANTYPE_STAMP_KOR) 
		{
			result = SearchTextInStampAnnotation(textSearch,
												 pageObj, 
												 childObj, 
												 textInfoResult, 
												 annoInfo);
		}
	}
	
	return result;
}

bool XdwAttributeParser::SearchTextInNotePadAnnotation(MPCTextSearch *textSearch, 
													   MPCObject *const pageObj, 
													   MPCObject *const childObj, 
													   MP_TextInfo **textInfoResult, 
													   MP_AnnoInfo *annoInfo)
{
	bool result = false;
	
	if (textSearch != NULL && pageObj != NULL && childObj != NULL)
	{
		int annObjCount = childObj->GetNumberOfChildren();
		for (int i = 0; i < annObjCount; i++) 
		{
			MPCObject *annObj = childObj->GetNthChild(i); 
			
			if (annObj != NULL && annObj->GetClassID() == ANTYPE_TEXT) 
			{
				result = SearchTextInTextAnnotation(textSearch, 
													pageObj, 
													annObj, 
													textInfoResult, 
													NULL);
			}
			
			if (annObj != NULL && (annObj->GetClassID() == ANTYPE_STAMP ||
								   annObj->GetClassID() == ANTYPE_STAMP_ENG ||
								   annObj->GetClassID() == ANTYPE_STAMP_KOR)) 
			{
				result = SearchTextInStampAnnotation(textSearch,
													 pageObj, 
													 annObj, 
													 textInfoResult, 
													 NULL);
			}
			
			if (annoInfo != NULL && result == true)
			{
				annoInfo->annoIndex = m_nPageChildNum;
				
				MP_Pos pos = { 0, 0 };
				GetAttributePosition(pageObj, m_nPageChildNum, pos);
				annoInfo->annoRect.pos = pos;
				
				MP_Dim dim = { 0, 0 };
				GetAttributeDim(childObj, dim);
				annoInfo->annoRect.dim = dim;
				
				break;
			}
		}
	}
	
	return result;
}

bool XdwAttributeParser::SearchTextInTextAnnotation(MPCTextSearch *textSearch,
													MPCObject *const pageObj, 
													MPCObject *const childObj, 
													MP_TextInfo **textInfoResult, 
													MP_AnnoInfo *annoInfo)
{
	if (textSearch != NULL && pageObj != NULL && childObj != NULL)
	{
		MPCFind6 *find6 = (MPCFind6*)childObj->GetInterface(IID_MPCFind6);
		if (find6 != NULL)
		{	
			MPCObject *findObject = find6->Find(textSearch, textInfoResult, NULL);
			if (findObject != NULL && textInfoResult != NULL) 
			{
				if (annoInfo != NULL)
				{
					annoInfo->annoIndex = m_nPageChildNum;
					
					MP_Pos pos = { 0, 0 };
					GetAttributePosition(pageObj, m_nPageChildNum, pos);
					annoInfo->annoRect.pos = pos;
					
					MP_Dim dim = { 0, 0 };
					GetAttributeDim(childObj, dim);
					annoInfo->annoRect.dim = dim;
				}
				
				findObject->Destroy();
				return true;
			} 
		}
	}
	
	return false;
}

bool XdwAttributeParser::SearchTextInStampAnnotation(MPCTextSearch *textSearch, 
													 MPCObject *const pageObj, 
													 MPCObject *const childObj, 
													 MP_TextInfo **textInfoResult, 
													 MP_AnnoInfo *annoInfo)
{
	if (textSearch != NULL && pageObj != NULL && childObj != NULL)
	{
		MPCFind6 *find6 = (MPCFind6*)childObj->GetInterface(IID_MPCFind6);
		if (find6 != NULL)
		{	
			MPCObject *findObject = find6->Find(textSearch, textInfoResult, NULL);
			if (findObject != NULL && textInfoResult != NULL) 
			{
				if (annoInfo != NULL)
				{
					annoInfo->annoIndex = m_nPageChildNum;
					
					MP_Pos pos = { 0, 0 };
					GetAttributePosition(pageObj, m_nPageChildNum, pos);
					annoInfo->annoRect.pos = pos;
					
					MP_Dim dim = { 0, 0 };
					GetAttributeDim(childObj, dim);
					annoInfo->annoRect.dim = dim;
				}
				
				findObject->Destroy();
				return true;
			} 
		}
	}
	
	return false;
}
// xujj 2012.03.22 end

// tongtx 2012.03.23 start
// 選択機能の追加
#pragma mark -
#pragma mark mehtod select text.
HRESULT XdwAttributeParser::GetLogicAnnotationList(int nPageNum, 
												   MP_ObjectType objectType, 
												   LogicAnnoInfoList* list)
{
	int totalPageNum = m_MPCPageRoot->GetNumberOfChildren();
	if (nPageNum < 0 || nPageNum > totalPageNum || list == NULL) 
	{
		return MP_S_FALSE;
	}
	
	MPCObject *pageObj = m_MPCPageRoot->GetNthChild(nPageNum);
	if (pageObj != NULL)
	{
		int annObjCount = pageObj->GetNumberOfChildren();
		for (int nth = 0; nth < annObjCount; nth++)
		{
			MPCObject *annObj = pageObj->GetNthChild(nth);
			if (annObj != NULL)
			{
				MP_ObjectType type = annObj->GetClassID();
				
				if (annObj->GetClassID() == CLSID_HETEROCONT)
				{
					continue;
				}
				
				if ((objectType & type) != objectType)
				{
					LogicAnnoInfo* annoInfo = new LogicAnnoInfo();
					
					annoInfo->SetPageNum(nPageNum);
					annoInfo->SetAnnoIndex(nth);
					
					MP_Pos pos = { 0, 0 };
					GetAttributePosition(pageObj, nth, pos);
					MP_Dim dim = { 0, 0 };
					GetAttributeDim(annObj, dim);
					annoInfo->SetRectangle(pos, dim);
					
					if (type == ANTYPE_TEXT) 
					{
						annoInfo->SetTextAnnotation(true);
					}

					if (type == ANTYPE_NOTEPAD) 
					{
						annoInfo->SetNotepadAnnotation(true);
					}
					
					list->Add(annoInfo);
				}
			}
		}
	}
	
	return MP_S_OK;
}


bool XdwAttributeParser::SelectText(int nPageNum, 
									int nAnnIndex, 
									MP_Pos start, 
									MP_Pos end, 
									MP_TextInfo** textInfo)
{
	int totalPageNum = m_MPCPageRoot->GetNumberOfChildren();
	if (nPageNum < 0 || nPageNum >= totalPageNum) 
		return false;
	
	MPCObject *pageObj = m_MPCPageRoot->GetNthChild(nPageNum);
	if (pageObj == NULL) 
		return false;
	
	int totalObjCount = pageObj->GetNumberOfChildren();
	if (nAnnIndex >= totalObjCount) 
		return false;
	
	if (nAnnIndex < 0)
	{
		MPCObject *bodyContent = pageObj->GetNthChild(0);
		if (bodyContent == NULL) 
			return false;
		
		if (bodyContent->GetClassID() == CLSID_HBODYCONT) 
		{
			MPCSelectText* selectText = (MPCSelectText*)bodyContent->GetInterface(IID_MPCSelectText);
			if (selectText != NULL) 
			{
				selectText->SelectText(start, end, textInfo);
				if (*textInfo != NULL)
				{
					return true;
				}
			}
		}
	}
	else
	{
		MPCObject *annObj = pageObj->GetNthChild(nAnnIndex);
		if (annObj->GetClassID() == ANTYPE_NOTEPAD) 
		{
			int annObjCount = annObj->GetNumberOfChildren();
			for (int nth = annObjCount - 1; nth >= 0; nth--)
			{
				MPCObject *obj = annObj->GetNthChild(nth);
				if (obj != NULL)
				{
					if (obj->GetClassID() == ANTYPE_TEXT) 
					{
						return true;
					}
				}
			}
		}
		else
		{
			return true;
		}
	}
	
	return false;
}

bool XdwAttributeParser::GetText(int nPageNum, 
								 int nAnnIndex,
								 MP_Text** text, 
								 MP_Integer length,
								 MP_TextInfo* textInfo)
{
	int totalPageNum = m_MPCPageRoot->GetNumberOfChildren();
	if (nPageNum < 0 || nPageNum >= totalPageNum) 
		return false;
	
	MPCObject *pageObj = m_MPCPageRoot->GetNthChild(nPageNum);
	if (pageObj == NULL) 
		return false;
	
	int totalObjCount = pageObj->GetNumberOfChildren();
	if (nAnnIndex >= totalObjCount) 
		return false;
	
	if (nAnnIndex < 0)
	{
		MPCObject *bodyContent = pageObj->GetNthChild(0);
		if (bodyContent == NULL) 
			return false;
		
		if (bodyContent->GetClassID() == CLSID_HBODYCONT) 
		{
			MPCText* mpcText = (MPCText*)bodyContent->GetInterface(IID_MPCText);
			if (mpcText != NULL)
			{
				HRESULT hres = mpcText->GetTextWithLF(*text, length, textInfo);
				if (hres == MP_S_OK) 
				{
					return true;
				}
			}
		}
	}
	else
	{
		MPCObject *annObj = pageObj->GetNthChild(nAnnIndex);
		if (annObj == NULL) 
			return false;
		
		NSString* text_string = nil;
		if (annObj->GetClassID() == ANTYPE_TEXT) 
		{
			text_string = GetTextAnnotationText(annObj);
		}
		
		if (annObj->GetClassID() == ANTYPE_NOTEPAD) 
		{
			text_string = GetNotepadAnnotationText(annObj);
		}
		
		if (text_string != nil && [text_string length] > 0) 
		{
			
			int count_ = [text_string length];
			MP_Text *src = (unsigned short*)[text_string cStringUsingEncoding:NSUTF16StringEncoding];
			*text = new MP_Text[count_ + 1];
			for (int i = 0; i < count_; i++)
			{
				(*text)[i] = src[i];
			}
			(*text)[count_] = '\0';
			
			return true;
		}
	}
	
	return false;
}

NSString* XdwAttributeParser::GetNotepadAnnotationText(MPCObject* const annObj)
{
	if (annObj == NULL)
	{
		return nil;
	}
	
	if (annObj->GetClassID() == ANTYPE_NOTEPAD) 
	{
		NSMutableString* text_string = [[[NSMutableString alloc] init] autorelease];
		
		int annObjCount = annObj->GetNumberOfChildren();
		for (int nth = 0; nth < annObjCount; nth++)
		{
			MPCObject *obj = annObj->GetNthChild(nth);
			if (obj != NULL && obj->GetClassID() == ANTYPE_TEXT)
			{
				NSString* tmp = GetTextAnnotationText(obj);
				if (tmp != nil) 
				{
					if ([text_string length] == 0)
					{
						[text_string appendString:tmp];
					}
					else
					{
						tmp = [NSString stringWithFormat:@"\n%@",tmp];
						[text_string appendString:tmp];
					}
				}
			}
			
			if (text_string.length != nil)
			{
				return text_string;
			}
		}
	}
	
	return nil;
}

NSString* XdwAttributeParser::GetTextAnnotationText(MPCObject* const annObj)
{
	if (annObj == NULL)
	{
		return nil;
	}
	
	if (annObj->GetClassID() == ANTYPE_TEXT) 
	{
		MPCText *pText = (MPCText *)annObj->GetInterface(IID_MPCText);
		if (pText != NULL) 
		{
			int nLen = pText->GetTextWithLF(NULL, 0, NULL);
			if (nLen < 0)
			{
				return nil;
			}
			
			MP_Text *text = new MP_Text[nLen];
			HRESULT hres = pText->GetTextWithLF(text, nLen, NULL);
			if (hres == MP_S_OK)
			{
				
				NSString *result = [NSString stringWithCharacters:(unichar*)text length:nLen - 1];
				delete [] text;
				return result;
			}
			if (text != NULL) 
			{
				delete [] text;
			}
		}
	}
	
	return nil;
}
// tongtx 2012.03.23 end