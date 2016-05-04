/*
 *  PDFPageInfo.h
 *  DWViewer
 *
 *  Created by jonah on 10-10-30.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _PDF_PAGEINFO_H_
#define _PDF_PAGEINFO_H_
#import "PageInfo.h"

class PDFPageInfo : public PageInfo {
public:
	PDFPageInfo(CGPDFPageRef pageObject);
	
	CGPDFPageRef GetPageRef();

	virtual ~PDFPageInfo();
	
	long GetWidth(PAGE_MODE mode = kPaperMode);
	long GetHeight(PAGE_MODE mode = kPaperMode);
	
	
private:
	/*! refrence of PDF document page */
    CGPDFPageRef m_pageObject;
	
};

#endif	// _PDF_PAGEINFO_H_
