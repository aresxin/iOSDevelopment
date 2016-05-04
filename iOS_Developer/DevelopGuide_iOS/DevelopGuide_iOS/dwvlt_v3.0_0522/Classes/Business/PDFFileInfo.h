/*
 *  PDFFileInfo.h
 *  DWViewer
 *
 *  Created by jonah on 10-10-30.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _PDF_FILEINFO_H_
#define _PDF_FILEINFO_H_

#import "FileInfo.h"

class PDFFileInfo : public FileInfo {
public:
	PDFFileInfo(const char* filePath);

	void SetPageCount(long pageCount);

	virtual ~PDFFileInfo();
	
	DOCUMENT_TYPE GetFileType() const { return kPDF_DOC; }
};

#endif	// _PDF_FILEINFO_H
