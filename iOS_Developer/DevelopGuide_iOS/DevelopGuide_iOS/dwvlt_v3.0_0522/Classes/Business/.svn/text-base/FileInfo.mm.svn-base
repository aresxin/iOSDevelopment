//
//  FileInfo.m
//  DWViewer
//
//  Created by dwcore_dev3 on 10/14/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//


#import "FileInfo.h"


FileInfo::FileInfo()
: m_PageCount(-1)
, m_bAnnoDisplay(true)
, m_FilePath("")
{
}

FileInfo::FileInfo(const char* filePath)
: m_PageCount(-1)
, m_bAnnoDisplay(true)
, m_FilePath(filePath)
{
}

long FileInfo::GetPageCount()
{
	return m_PageCount;
}

const char* FileInfo::GetDocName() const
{
	return m_FilePath.c_str();
}

ANNOT_DISPALY FileInfo::GetAnnotationDisplayMode()
{
	return (m_bAnnoDisplay) ? kShowAnnot :kHideAnnot;
}

void FileInfo::SetAnnotationDisplay(bool isDisplay)
{
	m_bAnnoDisplay = isDisplay;
}


