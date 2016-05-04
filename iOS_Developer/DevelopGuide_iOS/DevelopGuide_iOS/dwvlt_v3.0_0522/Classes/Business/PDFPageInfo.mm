/*
 *  PDFPageInfo.cpp
 *  DWViewer
 *
 *  Created by jonah on 10-10-30.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "PDFPageInfo.h"


PDFPageInfo::PDFPageInfo(CGPDFPageRef pageObject) 
:m_pageObject(pageObject)
{
	// get Rect of PDF page in units
	
	// liuqw 20120217 start
	// AR NO.17781の対応
	
	/*
	 CGRect rect = CGPDFPageGetBoxRect(pageObject, kCGPDFMediaBox);
	 */
	
	CGRect rect = CGPDFPageGetBoxRect(pageObject, kCGPDFCropBox);
	
	// liuqw 20120217 end
	
    // 「拡大操作の基準の変更」の対応 start
    
	// convert units to mm
	//m_pageWidth = (rect.size.width) / 75 * 25.4;
	//m_pageHeight = rect.size.height / 75 * 25.4;
    
    m_pageWidth = (rect.size.width) / 75 * 25.4 * 100;
	m_pageHeight = rect.size.height / 75 * 25.4 * 100;
    
    // 「拡大操作の基準の変更」の対応 end

	// 2011/03/23 PDF不具合チャートを修正 start
	int rotation = CGPDFPageGetRotationAngle(pageObject);
	if (rotation == 90 || rotation == 270) {
		long tmp = m_pageWidth;
		m_pageWidth = m_pageHeight;
		m_pageHeight = tmp;
	}
	// 2011/03/23 PDF不具合チャートを修正 end
}

PDFPageInfo::~PDFPageInfo()
{
}

CGPDFPageRef PDFPageInfo::GetPageRef()
{
	return m_pageObject;
}

long PDFPageInfo::GetWidth(PAGE_MODE mode) 
{
	return m_pageWidth;
}

long PDFPageInfo::GetHeight(PAGE_MODE mode) 
{
	return m_pageHeight;
}

