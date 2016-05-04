/*
 *  XdwLinkManager.h
 *  DWViewer
 *
 *  Created by zhangshuai on 10-10-31.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */
#include "LinkAnnotInfo.h"
#include <vector>

#ifndef XDWLINKMANAGER_H
#define XDWLINKMANAGER_H 

#define ANNOTATION_COUNT_FOR_QUICK_SEARCH 10

struct SearchKey {
	int pageIndex;
	int annotListIndex;
};


class XdwLinkManager
{
public:
	XdwLinkManager(LinkAnnotInfoList* annotInfoList);
	~XdwLinkManager();

	// Get Link annotation index for giving page
	// return linkAnnotIndex's count
	int GetLinkAnnotationIndexForPageIndex(int pageIndex, std::vector<int>& linkAnnotIndex);
	
private:
	// get annotation index for giving pageIndex
	bool GetAnnotationIndexForPageIndex(int pageIndex, int* start, int* end);
	
	void constructSearchKeys();
private:
	std::vector<SearchKey> m_SearchKeys;
	LinkAnnotInfoList* m_annotInfoList;
};

#endif
