/*
 *  XdwFileInfo.cpp
 *  DWViewer
 *
 *  Created by jonah on 10-10-30.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "XdwFileInfo.h"

XdwFileInfo::XdwFileInfo(const char* filePath) 
: FileInfo(filePath)
, m_bIsBinder(false)
, m_hasSignature(false)
, m_DocCnt(-1)
{
	m_DocInfoList.RemoveAll();
}

XdwFileInfo::~XdwFileInfo()
{
	m_DocInfoList.RemoveAll();	
}

long XdwFileInfo::GetPageCntOfBinderDoc(int docIndex) const
{
	return m_DocInfoList.GetPageCount(docIndex);
}

const char* XdwFileInfo::GetNameOfBinderDoc(int docIndex) const
{
	if (docIndex < 0) {
		return NULL;
	}
	
	return m_DocInfoList.GetDocName(docIndex);	
}


XdwErrorCode XdwFileInfo::AddDocInfo(const std::string& docName, long pageCnt)
{
	return m_DocInfoList.Add(docName, pageCnt);
}

ANNOT_DISPALY XdwFileInfo::GetAnnotationDisplayMode()
{
	return (m_bAnnoDisplay == true) ? kShowAnnot : kHideAnnot;
}

void XdwFileInfo::SetAnnotationDisplay(bool isDisplay)
{
	m_bAnnoDisplay = isDisplay;
}

#pragma mark -
#pragma mark DocInfoList
DocInfoList::DocInfoList()
{
	m_vecDocInfo.clear();
}

DocInfoList::~DocInfoList()
{
	RemoveAll();
}

XdwErrorCode DocInfoList::Add(const std::string& name, long count)
{
	XdwErrorCode retCode = XDW_ERRORCODE_SUCCESS;
	
	DocInfo *docInfo = new DocInfo(name, count);
	if (docInfo == XdwNull) {
		retCode = XDW_ERRORCODE_INSUFFICIENT_MEMORY;
		return retCode;
	}
	
	m_vecDocInfo.push_back(docInfo);
	
	return retCode;
}

void DocInfoList::RemoveAll()
{
	// Memory Leak の対応 start
	int size = m_vecDocInfo.size();
	for (int i = 0; i < size; i++)
	{
		if (m_vecDocInfo[i] != XdwNull)
		{
			delete m_vecDocInfo[i];
		}
	}
	// Memory Leak の対応 end
	m_vecDocInfo.clear();
}

long DocInfoList::GetPageCount(long index) const
{
	return m_vecDocInfo[index]->pageCnt;
}

const char* DocInfoList::GetDocName(long index) const
{
	const char* docName = (m_vecDocInfo[index]->docName).c_str();
	return docName;
}

