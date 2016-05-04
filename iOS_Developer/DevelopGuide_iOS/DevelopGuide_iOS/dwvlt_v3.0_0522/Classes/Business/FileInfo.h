/*
 *  FileInfo.h
 *  DWViewer
 *
 *  Created by dwcore_dev3 on 10/14/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef _FILEINFO_H_
#define _FILEINFO_H_

#import "w2mpf_def.h"
#import "w2mpf_gdi_def.h"
#import "w2mpf_gdi_def2.h"
#import "mpc_api.h"

//#import "XdwDocuWorks.h"
#import "DWViewerConst.h"
#import <string>

class FileInfo {
	
public:
	FileInfo();
	FileInfo(const char* filePath);
	
	virtual ~FileInfo(void) {} ;

	long GetPageCount();
	const char* GetDocName() const;
	ANNOT_DISPALY GetAnnotationDisplayMode();
	void SetAnnotationDisplay(bool isDisplay);
	
protected:
	/* File total page number */
	long m_PageCount;
	/* if annotation need display or not */
	bool m_bAnnoDisplay;
	/* file path */
	std::string m_FilePath;
};

#endif	// _FILEINFO_H_
