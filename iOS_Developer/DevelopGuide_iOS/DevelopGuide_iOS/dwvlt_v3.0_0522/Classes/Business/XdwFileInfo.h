/*
 *  XdwFileInfo.h
 *  DWViewer
 *
 *  Created by jonah on 10-10-30.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _XDW_FILEINFO_H_
#define _XDW_FILEINFO_H_

#import "FileInfo.h"

//#import "XdwDocuWorks.h"

const int DOC_NAME_SIZE = 2048;

class XdwFileInfo;


#pragma mark -
#pragma mark DocInfoList Class
class DocInfoList
{
private:
	class DocInfo {
	public:
		DocInfo(const std::string& name, long count) 
		: docName(name)
		, pageCnt(count) 
		{
		}
		// char name[DOC_NAME_SIZE];
		std::string docName;
		long pageCnt;
	};
	typedef std::vector<DocInfo*> VecDocInfo;
	
private:
	VecDocInfo m_vecDocInfo;
	
private:
	DocInfoList();
	virtual ~DocInfoList();
	
	XdwErrorCode Add(const std::string& name, long count);
	
	void RemoveAll();
	
	long GetPageCount(long index) const;
	
	const char* GetDocName(long index) const;
	
	friend class XdwFileInfo;
};

#pragma mark -
#pragma mark XdwFileInfo Class
class XdwFileInfo : public FileInfo {
public:
	XdwFileInfo(const char* filePath);
	virtual ~XdwFileInfo();
	
	// Other interface for DocuWorks Document
	bool IsBinder() const { return m_bIsBinder; }
	
	bool HasSignature() const { return m_hasSignature; }
	
	ANNOT_DISPALY GetAnnotationDisplayMode();

	void SetAnnotationDisplay(bool isDisplay);

	long GetBinderCount() const { return m_DocCnt; }
	
	// Get page number of document in binder
	long GetPageCntOfBinderDoc(int docIndex) const;
	
	const char* GetNameOfBinderDoc(int docIndex) const;
	
private:
	void SetPageCount(int pageCnt) { m_PageCount = pageCnt; }
	void SetBinder(bool isBinder) { m_bIsBinder = isBinder; }
	void SetBinderCount(long docCnt) { m_DocCnt = docCnt; }
	void SetSignature(bool isSignature) { m_hasSignature = isSignature; }
	
	/**
	 * @brief Add a document info to XdwFileInfo DocInfoVector
	 *
	 * @param docName : document name
	 * @param size : 
	 * @param count : page number of document
	 *
	 * @retval XdwErrorCode
	 */
	// XdwErrorCode AddDocInfo(const char* docName, int size, long count);
	XdwErrorCode AddDocInfo(const std::string& docName, long pageCnt);
	
private:
	/* if DocuWorks Document is Binder or not */
	bool m_bIsBinder;
	/* Signature */
	bool m_hasSignature;
	/* DocuWorks document in binder */
	long m_DocCnt;
	/* List of XDW file info */
	DocInfoList m_DocInfoList;
	
	friend class XdwAttributeParser;
};

#endif
