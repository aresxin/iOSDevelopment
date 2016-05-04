//
//  DocumentSettingsManager.h
//  DWViewer
//
//  Created by FX Neusoft on 10-11-6.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

enum FileUpdateErrorCode {
	FILEUPDATE_ERRORCODE_SUCCESS = 0,
	FILEUPDATE_ERRORCODE_NOT_EXISTED,
	FILEUPDATE_ERRORCODE_FILENAME_EMPTY,
	FILEUPDATE_ERRORCODE_OVERLENGTH,
	FILEUPDATE_ERRORCODE_FILENAME_EXISTED,
	FILEUPDATE_ERRORCODE_INVALID_CHAR,
    FILEUPDATE_ERRORCODE_OTHERS,
};

@interface DocumentSettingsManager : NSObject {
	int		pageIndex;
	long	pageScale;
	float	pagePointX;
	float	pagePointY;
	int		facingMode;
	BOOL	fontOrientationH;
	BOOL	showAnnotation;
	int		pageStatus;
	
	// FileSort の対応 start
	BOOL	keepStatus;
	int		fileSortItemIndex;
	int		fileSortModeIndex;
	// FileSort の対応 end
    
    // 「拡大率指定の追加」の対応 start
    int     specifyScaleModeIndex;
    int     specifyScale;
    // 「拡大率指定の追加」の対応 end
	
	// tongtx 2011/08/22 start
	// Briefcaseと連携機能の追加
	NSString *targetFilename;
	// tongtx 2011/08/22 end
}
@property (readonly) int   pageIndex;
@property (readonly) long  pageScale;
@property (readonly) float pagePointX;
@property (readonly) float pagePointY;
@property (readonly) int   facingMode;
@property (readonly) BOOL fontOrientationH;
@property (readonly) BOOL showAnnotation;
@property (readonly) int  pageStatus;
// FileSort の対応 start
@property (readonly) BOOL keepStatus;
@property (readonly) int fileSortItemIndex;
@property (readonly) int fileSortModeIndex;
// FileSort の対応 end

// 「拡大率指定の追加」の対応 start
@property (readonly) int specifyScaleModeIndex;
@property (readonly) int specifyScale;
// 「拡大率指定の追加」の対応 end

// tongtx 2011/08/22 start
// Briefcaseと連携機能の追加
@property (nonatomic, copy, readonly) NSString *targetFilename;
// tongtx 2011/08/22 end

// read keep document status
// FileSort の対応 start
//- (BOOL) readKeepDocumentStatus;
- (BOOL) readDocumentSettings;

// write keep document status.
//- (void) writeKeepDocumentStatus:(BOOL)status;
// 「拡大率指定の追加」の対応 start
/*
- (void) writeDocumentSettingsWithKeepStatus:(BOOL)status
                       withFileSortItemIndex:(int)itemIndex
                       withFileSortModeIndex:(int)modeIndex;
*/
- (void) writeDocumentSettingsWithKeepStatus:(BOOL)status
					   withFileSortItemIndex:(int)itemIndex
					   withFileSortModeIndex:(int)modeIndex
                             withSpecifyMode:(int)specifyModeIndex
                            withSpecifyScale:(int)scale;
// 「拡大率指定の追加」の対応 end
// FileSort の対応 end

// AR NO.17560 の対応 start
- (void) createSettingsDirectory;
// AR NO.17560 の対応 end

// FileSort の対応 start
// create file settings dir.
- (void) createSettingsSubDirectory;
// FileSort の対応 end

// read doucment status.
- (BOOL) readDocumentStatusWithFileName:(NSString*)name 
					   withCreationDate:(NSString*)date 
					   withDocumentSize:(NSString*)size;

// write document status.
- (void) writeDocumentStatusWithFileName:(NSString *)name 
						   withPageIndex:(int)index
						   withPageScale:(long)scale
						  withPagePointX:(float)pointX
						  withPagePointY:(float)pointY
						  withFacingMode:(int)mode
					 withFontOrientation:(BOOL)orientation
					  withShowAnnotation:(BOOL)show
						  withPageStatus:(int)status
					 withFileCreatedDate:(NSString *)date
							withFileSize:(NSString *)size;

// delete settings file with file name.
- (void) deleteSettingsFileWithFileName:(NSString*)name;

// delete all settings file in documents directory.
- (void) deleteAllSettingsFileInDirectory;

// get Documents directory path.
- (NSString*) getDocumentDirectoryPath;

// AR NO.17560 の対応 start
// get Settings sub directory path.
- (NSString*) getSettingsSubDirectoryPath;
// AR NO.17560 の対応 end

// get settings file path with file name.
- (NSString*) getSettingsFilePathWithFileName:(NSString*)name;

//File Multiple Del by Yangjx 0613 start

// create trash directory
- (NSString *) createTrashDirectory;

// delete file move file from documentDir to trashDir
- (BOOL) moveDocumentFromSrcPath:(NSString*)src toDestPath:(NSString *)dest;

// move file from trashDir to doucmentDir
- (BOOL) moveFileFromTrashToDocument;

// delete  all files.
- (void) deleteAllFilesFromTrashDirectory;

// get file path
- (NSString*) getDocumentFilePathWithFileName:(NSString *)fileName;

// yangjx 20110622 start
// AR17848 sortの対応
- (void) writeDocumentSettingsWithFileSortItemIndex:(int)itemIndex
							  withFileSortModeIndex:(int)modeIndex;
// yangjx 20110622 end

// yangjx 20110622 start
// AR 17863
- (NSString *) checkFileNameInDocument:(NSString *)moveFileName;
- (NSString *) changeFileName:(NSString*)fileName withNum:(NSInteger)num;
// yangjx 20110622 end

//File Multiple Del by Yangjx 0613 end

//『文書情報画面』の追加 start
- (FileUpdateErrorCode)updateFileNameWithSrcName:(NSString *)srcName 
                                    withDestName:(NSString *)dstName;
//『文書情報画面』の追加 end

// liuqw 20110628 start
// AR NO.17871 の対応
- (BOOL) isDocumentCanSaveSettings:(NSString*)fileName;
// liuqw 20110628 end

// tongtx 2011/08/15 start
// Briefcaseと連携機能の追加
- (BOOL) createFileAtDirectoryPath:(NSString *)directoryPath 
                              file:(NSString *)filename 
                          contents:(NSData *)data
                       overwritten:(BOOL)canOverwritten;
- (BOOL) createDirectoryAtPath:(NSString *)path;
- (NSData*) fileContentsAtPath:(NSString *)path;
- (void) removeFilesAtPath:(NSString *)path;
- (BOOL) compareDataWithSrcPath:(NSString *)srcPath 
                    withDstPath:(NSString *)dstPath;
// tongtx 2011/08/15 end

// liuqw 2012/03/06 start
// AR NO.19019の対応
- (BOOL) copyEditedFileToDocuments:(NSString*)srcPath 
					  destFileName:(NSString *)dstFileName 
					   overwritten:(BOOL)overwrite;
// liuqw 2012/03/06 end

@end
