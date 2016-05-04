/*
 *  LinkAnnotInfo.cpp
 *  DWViewer
 *
 *  Created by jonah on 10-10-31.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "LinkAnnotInfo.h"
#include "mpc_text.h"
#include "mpc_api.h"


////////////////////////////////////////////////////////////////////////////////////////////////
//LinkAnnotInfo
LinkAnnotInfo::LinkAnnotInfo()
:	m_LinkAnnotPos(0., 0.)
,	m_MPCObject(XdwNull)
,	m_Dim(0, 0)
,	m_PageNum(kLinkPageNoData)
,	m_PageCheck(kLinkPageNoData)
,	m_LinkTo(kLinkToNoData)
,	m_JumpType(kLinkToDwTypeNoData)
,   m_AnnotText(NULL)
,   m_isLinkAnnot(false)
{
	memset(m_LinkTitleString,	  0, sizeof(m_LinkTitleString));
	memset(m_UrlString,			  0, sizeof(m_UrlString));
	memset(m_MailAddressString,	  0, sizeof(m_MailAddressString));
	memset(m_SheafnameString,	  0, sizeof(m_SheafnameString));
	memset(m_LinkJumpTitleString, 0, sizeof(m_LinkJumpTitleString));
	
}

LinkAnnotInfo::~LinkAnnotInfo()
{
	if (m_AnnotText != NULL) {
		delete m_AnnotText;
	}
}

HRESULT LinkAnnotInfo::SetContent(MPCObject* const mpcObject)
{
	if (mpcObject == XdwNull)
	{
		return MP_E_INVALIDARG;
	}
	
	m_MPCObject = mpcObject;
	
	/* get attribute */
	OrganiseAttribute();
	SetXdwAnnotText(mpcObject);
	
	return MP_NOERROR;
}

const wchar_t* LinkAnnotInfo::GetAnnotText()
{
	if (m_AnnotText != NULL) {
		return m_AnnotText;
	} 
	else {
		return NULL;
	}

}

void LinkAnnotInfo::SetContentPos(MP_Pos pos)
{
	m_LinkAnnotPos.xF = pos.x;
	m_LinkAnnotPos.yF = pos.y;
}

void LinkAnnotInfo::SetContentDim(MP_Dim dim)
{
	m_Dim.xF = dim.cx;
	m_Dim.yF = dim.cy;
}

HRESULT LinkAnnotInfo::CalculateContentDim()
{
	m_Dim.xF = 0;
	m_Dim.yF = 0;
	HRESULT hres = MP_NOERROR;
	if (m_MPCObject != XdwNull)
	{
		//get dim
		MP_AValue value={sizeof(MP_Dim), MP_A_DIM, &m_Dim};
		hres = m_MPCObject->GetAttribute("#dim", &value);
	}

	return hres;
}

XdwRectangle LinkAnnotInfo::GetRectangle() const
{
	XdwRectangle rect;
	rect.LeftTopF.xF = m_LinkAnnotPos.xF;
	rect.LeftTopF.yF = m_LinkAnnotPos.yF;
	rect.RightBottomF.xF = m_LinkAnnotPos.xF + m_Dim.xF;
	rect.RightBottomF.yF = m_LinkAnnotPos.yF + m_Dim.yF;
	
	return rect;
}

void LinkAnnotInfo::OrganiseAttribute()
{
	SetLinkToPageNum();
	SetPageCheck();
	SetLinkTo();
	SetDwJumpType();
	SetLinkTitleString();
	SetUrlString();
	SetMailadressString();
	SetSheafnameString();
	SetLinkJumpTitleString();
	SetOtherFilePathString();
}

bool LinkAnnotInfo::IsLinkAnnotation()
{
	return m_isLinkAnnot;
}

void LinkAnnotInfo::SetXdwAnnotText(MPCObject* const mpcObject)
{
	if (IsLinkAnnot(mpcObject)) {
		m_isLinkAnnot = true;
		return;
	}
	
	
	// 2012.02.13 M.Chikyu start. 
	/*
	MPCObject* obj = mpcObject->GetNthChild(0);
	// not text annotation
	if (obj == NULL) {
		return;
	}

	HRESULT hres = MP_NOERROR;
		
	// テキスト取得インタフェースを取得
	MPCText* pText = (MPCText*)obj->GetInterface(IID_MPCText);
	
	// add by tongjo
	if (NULL == pText) {
		return;
	}
	 */
	
	MPCObject*	obj;
	MPCText*	pText;
	HRESULT		hres;
	
	int index = 0;
	
	do
	{
		if (index >= mpcObject->GetNumberOfChildren())
		{
			return;
		}
		
		obj = mpcObject->GetNthChild(index++);
		if (obj != NULL)
		{
			// テキスト取得インタフェースを取得
			pText = (MPCText*)obj->GetInterface(IID_MPCText);
		}
		else
		{
			pText = NULL;
		}
		
	} while (pText == NULL);
	
	// 2012.02.13 M.Chikyu end. 
	

	int nLengthWC = pText->GetText(NULL, 0, NULL);	
	
	unsigned short* pwszTemp = new(std::nothrow) unsigned short [nLengthWC];
	// MemoryLeak by tongjo 20101205
	if (pwszTemp == NULL) {
		return;
	}
	//AR16336
	memset(pwszTemp, 0, nLengthWC * sizeof(unsigned short));
	
	hres = pText->GetText((MP_Text *)pwszTemp, nLengthWC, NULL);
	m_AnnotText = new wchar_t[nLengthWC];
	if (m_AnnotText == NULL) {
		// MemoryLeak by tongjo 20101205
		if (pwszTemp != NULL) {
			delete pwszTemp;
			pwszTemp = NULL;
		}
		return;
	}
	for (int i = 0; i < nLengthWC; ++i) {
		m_AnnotText[i] = pwszTemp[i];
	}
	
	// MemoryLeak by tongjo 20101205
	if (pwszTemp != NULL) {
		delete pwszTemp;
		pwszTemp = NULL;
	}
	//m_AnnotText = pwszTemp;	
}

void LinkAnnotInfo::SetXdwPageNum(long pageIndex)
{
	m_PageNum = pageIndex;
}

// modify by liuqw
void LinkAnnotInfo::SetLinkToPageNum()
{
	if (m_MPCObject != XdwNull)
	{
		m_LinkToPageNum = GetLinkPageNumAttr(m_MPCObject);
	}
}

void LinkAnnotInfo::SetPageCheck()
{
	if (m_MPCObject != XdwNull)
	{
		m_PageCheck = static_cast<LinkAnnotInfo::LinkPageAttribute>(GetLinkPageCheckAttr(m_MPCObject));
	}
}

void LinkAnnotInfo::SetLinkTo()
{
	if (m_MPCObject != XdwNull)
	{
		m_LinkTo = static_cast<LinkAnnotInfo::LinkTo>(GetLinkLinkToAttr(m_MPCObject));
	}
}

void LinkAnnotInfo::SetDwJumpType()
{
	if (m_MPCObject != XdwNull)
	{
		m_JumpType = static_cast<LinkAnnotInfo::LinkToDwType>(GetLinkDWLinkType(m_MPCObject));
	}
}

void LinkAnnotInfo::SetLinkTitleString()
{
	if (m_MPCObject != XdwNull)
	{
		/* get link title string */
		char title[kMaxLinkStrBuf] = {0};
		GetLinkTitleStrAttr(m_MPCObject, title);
		memset(m_LinkTitleString, 0, sizeof(m_LinkTitleString));
		
		memcpy(m_LinkTitleString, title, strlen(title));
	}
}

void LinkAnnotInfo::SetUrlString()
{
	if (m_MPCObject != XdwNull)
	{
		/* get size */
		int sizeURL = 0;
        GetLinkURLStrAttr(m_MPCObject, 0, &sizeURL);
		
		/* get url */
		char url[kMaxLinkStrBuf] = {0};
		GetLinkURLStrAttr(m_MPCObject, url, &sizeURL);
		memset(m_UrlString, 0, sizeof(m_UrlString));
		
		memcpy(m_UrlString, url, strlen(url));
		
		/* convert to wide char */
		//int sizeW = MultiByteToWideChar(CP_ACP, 0, url, -1, XdwNull, 0);
		//MultiByteToWideChar(CP_ACP, 0, url, -1, m_UrlString, sizeW);
	}
}

void LinkAnnotInfo::SetMailadressString()
{
	if (m_MPCObject != XdwNull)
	{
		
		/* get size */
		int sizeMail = 0;
		GetLinkMailAddress(m_MPCObject, 0, &sizeMail);
		
		/* get address */
		char mailAddr[kMaxLinkStrBuf] = {0};
		GetLinkMailAddress(m_MPCObject, mailAddr, &sizeMail);
		memset(m_MailAddressString, 0, sizeof(m_MailAddressString));
		
		memcpy(m_MailAddressString, mailAddr, strlen(mailAddr));
		/* convert to wide char */
		//int sizeW = MultiByteToWideChar(CP_ACP, 0, mailAddr, -1, XdwNull, 0);
		//MultiByteToWideChar(CP_ACP, 0, mailAddr, -1, m_MailAddressString, sizeW);
	}
}

void LinkAnnotInfo::SetSheafnameString()
{
	if (m_MPCObject != XdwNull)
	{
		/* get size */
		int sizeSheafName = 0;
		GetLinkInternalSheafNameAttr(m_MPCObject, 0, &sizeSheafName);
		
		/* get sheaf name string */
		char sheaf[kMaxLinkStrBuf] = {0};
		GetLinkInternalSheafNameAttr(m_MPCObject, sheaf, &sizeSheafName);
		memset(m_SheafnameString, 0, sizeof(m_SheafnameString));
		
		memcpy(m_SheafnameString, sheaf, strlen(sheaf));

	}
}

void LinkAnnotInfo::SetLinkJumpTitleString()
{
	if (m_MPCObject != XdwNull)
	{
		/* size */
		int sizeJumpTitle = 0;
		GetLinkJumpTitle(m_MPCObject, 0, &sizeJumpTitle);
		
		/* get jump title string */
		char title[kMaxLinkStrBuf] = {0};
		GetLinkJumpTitle(m_MPCObject, title, &sizeJumpTitle);
		memset(m_LinkJumpTitleString, 0, sizeof(m_LinkJumpTitleString));
		
		memcpy(m_LinkJumpTitleString, title, strlen(title));
	}
}

//added now
void LinkAnnotInfo::SetOtherFilePathString()
{
	int sizePath = 0;
	GetLinkOtherFilePath(m_MPCObject, 0, &sizePath);
	
	char pathString[kMaxLinkStrBuf] = {0};
	GetLinkOtherFilePath(m_MPCObject, pathString, &sizePath);
	memset(m_OtherFilePathString, 0, sizeof(m_OtherFilePathString));
	memcpy(m_OtherFilePathString, pathString, strlen(pathString));
}


void LinkAnnotInfo::SetAnnotationColor(long color)
{
	m_rgbColor = color;
}

const long LinkAnnotInfo::GetAnnotationColor() const
{
	return m_rgbColor;
}

long LinkAnnotInfo::GetXdwPageNum() const
{
	return m_PageNum;
}

LinkAnnotInfo::LinkPageAttribute LinkAnnotInfo::GetPageCheck() const
{
	return m_PageCheck;
}

LinkAnnotInfo::LinkTo LinkAnnotInfo::GetLinkTo() const
{
	return m_LinkTo;
}

LinkAnnotInfo::LinkToDwType LinkAnnotInfo::GetDwJumpType() const
{
	return m_JumpType;
}

const char* LinkAnnotInfo::GetLinkTitleString() const
{
	return m_LinkTitleString;
}

const char* LinkAnnotInfo::GetUrlString() const
{
	return m_UrlString;
}

const char* LinkAnnotInfo::GetMailadressString() const
{
	return m_MailAddressString;
}

const char* LinkAnnotInfo::GetSheafnameString() const
{
	return m_SheafnameString;
}

const char* LinkAnnotInfo::GetLinkJumpTitleString() const
{
	return m_LinkJumpTitleString;
}

bool LinkAnnotInfo::IsLinkAnnot(MPCObject* const mpcContentObject)
{
	// link annotation ID(0xC02F)
	if (mpcContentObject->GetClassID() == 0xC02F) {
		return true;
	}
	
	return false;
}

long  LinkAnnotInfo::GetLinkToPageNum() const
{
	return m_LinkToPageNum;
}

const char* LinkAnnotInfo::GetOtherFilePathString() const
{
	return m_OtherFilePathString;
}


////////////////////////////////////////////////////////////////////////////////////////////////
//LinkAnnotInfoList
LinkAnnotInfoList::LinkAnnotInfoList()
{
	m_vecLinkAnnotInfo.clear();
}

LinkAnnotInfoList::~LinkAnnotInfoList()
{
	RemoveAll();
}

void LinkAnnotInfoList::Add(LinkAnnotInfo* const content)
{
	if (content != XdwNull)
	{
		m_vecLinkAnnotInfo.push_back(content);
	}
}

void LinkAnnotInfoList::RemoveAll()
{
	int size = m_vecLinkAnnotInfo.size();
	for (int i = 0; i < size; i++)
	{
		if (m_vecLinkAnnotInfo[i] != XdwNull)
		{
			delete m_vecLinkAnnotInfo[i];
		}
	}
	m_vecLinkAnnotInfo.clear();
}

LinkAnnotInfo* LinkAnnotInfoList::GetLinkAnnotInfo(int index) const
{
	int size = m_vecLinkAnnotInfo.size();
	if (index >= size || index < 0)
	{
		return XdwNull;
	}
	
	return m_vecLinkAnnotInfo[index];
}

int LinkAnnotInfoList::Size() const
{
	return m_vecLinkAnnotInfo.size();
}




