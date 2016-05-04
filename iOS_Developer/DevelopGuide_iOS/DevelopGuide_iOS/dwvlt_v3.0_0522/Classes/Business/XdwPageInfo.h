/*
 *  XdwPageInfo.h
 *  DWViewer
 *
 *  Created by jonah on 10-10-30.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#import "PageInfo.h"

class XdwPageInfo : public PageInfo {
public:
	XdwPageInfo();
	virtual ~XdwPageInfo() {};

	virtual long GetWidth(PAGE_MODE mode = kPaperMode);
	virtual long GetHeight(PAGE_MODE mode = kPaperMode);

	virtual MP_Pos GetPagePos(PAGE_MODE mode = kPaperMode);
	
	virtual PageObject GetPageObject();
	virtual void SetPageObject(PageObject pageObject);
	
	
private:
	void SetPageWidth(long width);
	void SetPageHeight(long height);
	void SetPageRectangle(RECT rect);
	void SetPageIndex(int index);
	RECT GetPageRectangle();

private:
	/*! Object of DocuWorks document page */
    MPCObject* m_PageObject;
	
	long m_PageLeft;
	long m_PageTop;
	long m_PageRight;
	long m_PageBottom;
	
	friend class XdwAttributeParser;
};
