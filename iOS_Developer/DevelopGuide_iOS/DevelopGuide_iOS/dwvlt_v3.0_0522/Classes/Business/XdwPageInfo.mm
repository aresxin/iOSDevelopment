/*
 *  XdwPageInfo.cpp
 *  DWViewer
 *
 *  Created by jonah on 10-10-30.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "XdwPageInfo.h"

XdwPageInfo::XdwPageInfo()
	: PageInfo()
	, m_PageLeft(0)
	, m_PageTop(0)
	, m_PageRight(0)
	, m_PageBottom(0)
{
}

long XdwPageInfo::GetWidth(PAGE_MODE mode)
{
	if (mode == kFullMode) {
		return m_PageRight - m_PageLeft;
	}

	return m_pageWidth;
}

long XdwPageInfo::GetHeight(PAGE_MODE mode)
{
	if (mode == kFullMode) {
		return m_PageBottom - m_PageTop;
	}
	
	return m_pageHeight;
}

void XdwPageInfo::SetPageIndex(int index)
{
	m_pageIndex = index;
}

void XdwPageInfo::SetPageWidth(long width)
{
	m_pageWidth = width;
}

void XdwPageInfo::SetPageHeight(long height)
{
	m_pageHeight = height;
}

void XdwPageInfo::SetPageRectangle(RECT rect)
{
	m_PageLeft = rect.left;
	m_PageTop = rect.top;
	m_PageRight = rect.right;
	m_PageBottom = rect.bottom;
}

MP_Pos XdwPageInfo::GetPagePos(PAGE_MODE mode)
{
	if (mode == kFullMode) {
		m_PageOrigin.x = m_PageLeft;
		m_PageOrigin.y = m_PageTop;
	}

	return m_PageOrigin;
}

RECT XdwPageInfo::GetPageRectangle()
{
	//RECT rect = { m_PageTop, m_PageLeft, 
	RECT rect = { m_PageLeft, m_PageTop,	
		m_PageRight, m_PageBottom };

	return rect;
}

PageObject XdwPageInfo::GetPageObject()
{
	return m_pageObject;
}

void XdwPageInfo::SetPageObject(PageObject pageObject)
{
	if (pageObject == XdwNull) {
		return ;
	}

	m_pageObject = pageObject;
}
