//
//  LogicAnnotationManager.m
//  DWViewer
//
//  Created by liuqw on 12-3-14.
//  Copyright (c) 2012年 Neusoft dalian. All rights reserved.
//

#include "LogicAnnotationManager.h"
#include "DocumentHandle.h"

////////////////////////////////////////////////////////////////////////////////////////////////
//LogicAnnoInfo
LogicAnnoInfo::LogicAnnoInfo()
:	m_nPageNum(0)
,	m_nAnnIndex(-1)
,	m_isNotpadAnn(false)
,	m_isTextAnn(false)
{
	
}

LogicAnnoInfo::~LogicAnnoInfo()
{
	
}

void LogicAnnoInfo::SetPageNum(int pageNum)
{
	m_nPageNum = pageNum;
}

int LogicAnnoInfo::GetPageNum()
{
	return m_nPageNum;
}

void LogicAnnoInfo::SetAnnoIndex(int index)
{
	m_nAnnIndex = index;
}

int LogicAnnoInfo::GetAnnoIndex()
{
	return m_nAnnIndex;
}

void LogicAnnoInfo::SetRectangle(MP_Pos pos, MP_Dim dim)
{
	m_rect.pos = pos;
	m_rect.dim = dim;
}

MP_Rect LogicAnnoInfo::GetRectangle()
{
	return m_rect;
}

void LogicAnnoInfo::SetNotepadAnnotation(bool isNotpad)
{
	m_isNotpadAnn = isNotpad;
}

bool LogicAnnoInfo::IsNotepadAnnotation()
{
	return m_isNotpadAnn;
}

void LogicAnnoInfo::SetTextAnnotation(bool isText)
{
	m_isTextAnn = isText;
}

bool LogicAnnoInfo::IsTextAnnotation()
{
	return m_isTextAnn;
}


////////////////////////////////////////////////////////////////////////////////////////////////
//LogicAnnoInfoList
LogicAnnoInfoList::LogicAnnoInfoList()
{
	m_vecLogicAnnoInfo.clear();
}

LogicAnnoInfoList::~LogicAnnoInfoList()
{
	RemoveAll();
}

void LogicAnnoInfoList::Add(LogicAnnoInfo* const info)
{
	if (info != XdwNull)
	{
		m_vecLogicAnnoInfo.push_back(info);
	}
}

void LogicAnnoInfoList::RemoveAll()
{
	int size = m_vecLogicAnnoInfo.size();
	for (int i = 0; i < size; i++)
	{
		if (m_vecLogicAnnoInfo[i] != XdwNull)
		{
			delete m_vecLogicAnnoInfo[i];
		}
	}
	m_vecLogicAnnoInfo.clear();
}

LogicAnnoInfo* LogicAnnoInfoList::GetLogicAnnInfo(int index) const
{
	int size = m_vecLogicAnnoInfo.size();
	if (index >= size || index < 0)
	{
		return XdwNull;
	}
	
	return m_vecLogicAnnoInfo[index];
}

int LogicAnnoInfoList::Size() const
{
	return m_vecLogicAnnoInfo.size();
}



////////////////////////////////////////////////////////////////////////////////////////////////
//LogicAnnotationManager
LogicAnnotationManager::LogicAnnotationManager(DocumentHandle* handle)
: m_documentHandle(handle)
, m_annotInfoList(NULL)
{
}

LogicAnnotationManager::~LogicAnnotationManager()
{
} 

void LogicAnnotationManager::GetLogicAnnotationList(int nPageNum)
{
	MP_ObjectType type = ANTYPE_TEXT | ANTYPE_NOTEPAD;
	m_annotInfoList = m_documentHandle->GetLogicAnnotationList(nPageNum, type);
}

int LogicAnnotationManager::GetLogicAnnotationIndex(int index)
{
	int annoIndex = -1;
	LogicAnnoInfo* info = m_annotInfoList->GetLogicAnnInfo(index);
	if (info != NULL)
	{
		annoIndex = info->GetAnnoIndex();
	}
	
	return annoIndex;
}

CGRect LogicAnnotationManager::GetLogicAnnotationRect(int index)
{
	CGRect rect;
	if (m_annotInfoList != NULL) 
	{
		for (int i = 0; i < m_annotInfoList->Size(); i++) 
		{
			LogicAnnoInfo* info = m_annotInfoList->GetLogicAnnInfo(index);
			if (info != NULL)
			{
				MP_Rect mpRect = info->GetRectangle();
				rect = CGRectMake(mpRect.pos.x, 
								  mpRect.pos.y, 
								  mpRect.dim.cx, 
								  mpRect.dim.cy);
			}
		}
	}
	
	return rect;
}

int LogicAnnotationManager::GetLogicAnnotationCount()
{
	if (m_annotInfoList != NULL) 
	{
		return m_annotInfoList->Size();
	}
	
	return 0;
}

LogicAnnoInfo* LogicAnnotationManager::GetLogicAnnoInfo(int index)
{
	return m_annotInfoList->GetLogicAnnInfo(index);
}
