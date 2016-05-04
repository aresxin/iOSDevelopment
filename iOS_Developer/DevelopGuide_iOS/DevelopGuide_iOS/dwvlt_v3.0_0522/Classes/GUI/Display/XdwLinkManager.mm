/*
 *  XdwLinkManager.cpp
 *  DWViewer
 *
 *  Created by zhangshuai on 10-10-31.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "XdwLinkManager.h"


XdwLinkManager::XdwLinkManager(LinkAnnotInfoList* annotInfoList)
: m_annotInfoList(annotInfoList)
{
	if ((m_annotInfoList != NULL) && 
		(m_annotInfoList->Size() > ANNOTATION_COUNT_FOR_QUICK_SEARCH)) {
		constructSearchKeys();
	}
}

XdwLinkManager::~XdwLinkManager()
{
} 
int XdwLinkManager::GetLinkAnnotationIndexForPageIndex(int pageIndex,
													   std::vector<int>& linkAnnotIndex)
{
	if (m_annotInfoList == NULL) {
		return 0;
	}
	
	int start = -1;
	int end = -1;
	// get annotation index for giving pageIndex
	if (GetAnnotationIndexForPageIndex(pageIndex, &start, &end) == false)
	{
		return 0;
	}
	
	int count = 0;
	// caculate Link annotation counts for giving pageIndex
	for (int i = start; i <= end; ++i) {
		LinkAnnotInfo* annotInfo = m_annotInfoList->GetLinkAnnotInfo(i);
		if (annotInfo != NULL && annotInfo->IsLinkAnnotation()) {
			// find LinkAnnotation
			linkAnnotIndex.push_back(i);
			++count;
		}
	}
	
	return count;
}

bool XdwLinkManager::GetAnnotationIndexForPageIndex(int pageIndex, int* start, int* end)
{
	int annotListSize = m_annotInfoList->Size();
	if (annotListSize <= ANNOTATION_COUNT_FOR_QUICK_SEARCH) {
		for (int i = 0; i < annotListSize; ++i) {
			LinkAnnotInfo* annotInfo = m_annotInfoList->GetLinkAnnotInfo(i);
			if (annotInfo != NULL && annotInfo->GetXdwPageNum() == pageIndex) {
				if (*start == -1) {
					*start = i;
					*end = i;
				}
				else {
					*end = i;
				}
			}
		}
		if (*start == -1) {
			return false;
		}
		return true;
	}
	else {// for quick search
		std::vector<SearchKey>::iterator it = m_SearchKeys.begin();
		// find pageIndex in SeakchKeys
		for (; it < m_SearchKeys.end(); ++it) {
			if ((*it).pageIndex == pageIndex) {
				break;
			}
		}
		
		// find nothing
		if (it == m_SearchKeys.end()) {
			return false;
		}
		else if (it == (m_SearchKeys.end() - 1)) {// find last one
			*start = (*it).annotListIndex;
			*end = annotListSize - 1;
			return true;
		} 
		else {// find normal
			*start = (*it).annotListIndex;
			*end = (*(it + 1)).annotListIndex - 1;
			return true;
		}
	}
	
}

void XdwLinkManager::constructSearchKeys()
{
	long prePageIndex = -1;
	// construct a searchKeys
	// pageIndex and first annotation index for this pageIndex 
	for (int i = 0; i < m_annotInfoList->Size(); ++i) {
		LinkAnnotInfo* annotInfo = m_annotInfoList->GetLinkAnnotInfo(i);
		if (annotInfo == NULL) return;
		long index = annotInfo->GetXdwPageNum();
		if (index != prePageIndex) {
			SearchKey key;
			key.pageIndex = index;
			key.annotListIndex = i;
			m_SearchKeys.push_back(key);
		}
		prePageIndex = index;
	}
}

