//
//  LogicAnnotationManager.h
//  DWViewer
//
//  Created by liuqw on 12-3-14.
//  Copyright (c) 2012年 Neusoft dalian. All rights reserved.
//

#ifndef LOGIC_ANN_MGR_H_
#define LOGIC_ANN_MGR_H_

#include "mpc_api.h"
#include "corecmmdef.h"

class LogicAnnoInfo
{
public:
	
    LogicAnnoInfo();
    virtual ~LogicAnnoInfo();
	
public:
	
	void	SetPageNum(int pageNum);
	int		GetPageNum();
	
	void	SetAnnoIndex(int index);
	int		GetAnnoIndex();
	
	void	SetRectangle(MP_Pos pos, MP_Dim dim);
	MP_Rect GetRectangle();
	
	void	SetNotepadAnnotation(bool isNotpad);
	bool    IsNotepadAnnotation();
	
	void	SetTextAnnotation(bool isText);
	bool    IsTextAnnotation();
	
private:
	
	int			m_nPageNum;
	int			m_nAnnIndex;
	MP_Rect		m_rect;
	bool		m_isNotpadAnn;
	bool		m_isTextAnn;
	
};


typedef std::vector< LogicAnnoInfo* > VecLogicAnnoInfo;
class LogicAnnoInfoList
{
public:
	
    LogicAnnoInfoList();
    virtual ~LogicAnnoInfoList();
	
public:
	
    void Add(LogicAnnoInfo* const info);
	
    void RemoveAll();
	
    LogicAnnoInfo* GetLogicAnnInfo(int index) const;
	
    int Size() const;
	
private:
	
    VecLogicAnnoInfo m_vecLogicAnnoInfo;
	
};

class DocumentHandle;
class LogicAnnotationManager
{
public:
	
	LogicAnnotationManager(DocumentHandle* handle);
	~LogicAnnotationManager();
	
	void GetLogicAnnotationList(int nPageNum);
	int  GetLogicAnnotationIndex(int index);
	CGRect GetLogicAnnotationRect(int index);
	int GetLogicAnnotationCount();
	
	LogicAnnoInfo* GetLogicAnnoInfo(int index);
	
private:
	
	DocumentHandle		*m_documentHandle;
	LogicAnnoInfoList	*m_annotInfoList;
	
};

#endif	// LOGIC_ANN_MGR_H_

