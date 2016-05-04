//
//  PageInfo.h
//  DWViewer
//
//  Created by dwcore_dev3 on 10/15/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#ifndef _PAGEINFO_H_
#define _PAGEINFO_H_

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>

#import "w2mpf_def.h"
#import "w2mpf_gdi_def.h"
#import "w2mpf_gdi_def2.h"
#import "mpc_pd.h"

struct MPCObject;
typedef void* PageObject;

class PageInfo {
public:
	
	enum PAGE_MODE {
		kFullMode = 0,
		kPaperMode,
	};

	PageInfo();
	virtual ~PageInfo() {} ;
	
	virtual long GetWidth(PAGE_MODE mode = kPaperMode);
	virtual long GetHeight(PAGE_MODE mode = kPaperMode);

	virtual MP_Pos GetPagePos(PAGE_MODE mode = kPaperMode);

	long GetPageIndex() const { return m_pageIndex; }
	
	// get PageObject
	virtual PageObject GetPageObject() { return m_pageObject; }
	virtual void SetPageObject(PageObject pageObject) { m_pageObject = pageObject; }

protected:
	/* Page Object */
	PageObject m_pageObject;
	/*! Width of the page */
    long m_pageWidth;
    /*! Height of the page */
    long m_pageHeight;
	// Current page index
	int m_pageIndex;
	/* Origin */
	MP_Pos m_PageOrigin;
};

#endif	// _PAGEINFO_H_
