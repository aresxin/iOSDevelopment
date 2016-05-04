//
//  DocumentSettingsManager.m
//  DWViewer
//
//  Created by FX Neusoft on 10-11-6.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "DocumentSettingsManager.h"
#import "DWViewerGUIConst.h"

// tongtx 2011/08/15 start
// Briefcaseと連携機能の追加
@interface DocumentSettingsManager (FilenameProcess)

- (void)changeExistedFilenameAtPath:(NSString *)path 
                           fromFile:(NSString *)srcFilename 
                             toFile:(NSString **)dstFilename;

@end

@implementation DocumentSettingsManager (FilenameProcess)

- (void)changeExistedFilenameAtPath:(NSString *)path 
                           fromFile:(NSString *)srcFilename 
                             toFile:(NSString **)dstFilename
{
	static int count = 0;
    
	NSFileManager *fileManager = [[NSFileManager alloc] init];
	NSString *documentFilePath = [path stringByAppendingPathComponent:*dstFilename];
	if ([fileManager fileExistsAtPath:documentFilePath]) {
		NSString *desFilenameByDeletingPathExtension = [NSString stringWithFormat:@"%@-%d",
                                                        [srcFilename stringByDeletingPathExtension], ++count];
		*dstFilename = [desFilenameByDeletingPathExtension stringByAppendingPathExtension:[srcFilename pathExtension]];
		[self changeExistedFilenameAtPath:path fromFile:srcFilename toFile:dstFilename];
	}
	[fileManager release];
}

@end
// tongtx 2011/08/15 end 


#pragma mark -
@implementation DocumentSettingsManager

@synthesize pageIndex;
@synthesize pageScale;
@synthesize pagePointX;
@synthesize pagePointY;
@synthesize facingMode;
@synthesize fontOrientationH;
@synthesize showAnnotation;
@synthesize pageStatus;
// FileSort の対応 start
@synthesize keepStatus;
@synthesize fileSortItemIndex;
@synthesize fileSortModeIndex;
// FileSort の対応 end

// 「拡大率指定の追加」の対応 start
@synthesize specifyScaleModeIndex;
@synthesize specifyScale;
// 「拡大率指定の追加」の対応 end

// tongtx 2011/08/22 start
// Briefcaseと連携機能の追加
@synthesize targetFilename;
// tongtx 2011/08/22 end
/*
static const NSString* KEY_KEEP_STATUS = @"KEY_KEEP_STATUS";
static const NSString* KEY_PAGE_INDEX = @"KEY_PAGE_INDEX";
static const NSString* KEY_PAGE_SCALE = @"KEY_PAGE_SCALE";
static const NSString* KEY_PAGE_POINT_X = @"KEY_PAGE_POINT_X";
static const NSString* KEY_PAGE_POINT_Y = @"KEY_PAGE_POINT_Y";
static const NSString* KEY_FACE_MODE = @"KEY_FACE_MODE";
static const NSString* KEY_FONT_ORIEN = @"KEY_FONT_ORIEN";
static const NSString* KEY_SHOW_ANNO = @"KEY_SHOW_ANNO";
static const NSString* KEY_PAGE_STATUS = @"KEY_PAGE_STATUS";
static const NSString* KEY_CREATION_DATE = @"KEY_CREATION_DATE";
static const NSString* KEY_DOCUMENT_SIZE = @"KEY_DOCUMENT_SIZE";
 */
static NSString* KEY_KEEP_STATUS = @"KEY_KEEP_STATUS";
static NSString* KEY_PAGE_INDEX = @"KEY_PAGE_INDEX";
static NSString* KEY_PAGE_SCALE = @"KEY_PAGE_SCALE";
static NSString* KEY_PAGE_POINT_X = @"KEY_PAGE_POINT_X";
static NSString* KEY_PAGE_POINT_Y = @"KEY_PAGE_POINT_Y";
static NSString* KEY_FACE_MODE = @"KEY_FACE_MODE";
static NSString* KEY_FONT_ORIEN = @"KEY_FONT_ORIEN";
static NSString* KEY_SHOW_ANNO = @"KEY_SHOW_ANNO";
static NSString* KEY_PAGE_STATUS = @"KEY_PAGE_STATUS";
static NSString* KEY_CREATION_DATE = @"KEY_CREATION_DATE";
static NSString* KEY_DOCUMENT_SIZE = @"KEY_DOCUMENT_SIZE";
// FileSort の対応 start
/*
static const NSString* KEY_SORT_ITEM_INDEX = @"KEY_SORT_ITEM_INDEX";
static const NSString* KEY_SORT_MODE_INDEX = @"KEY_SORT_MODE_INDEX";
 */
static NSString* KEY_SORT_ITEM_INDEX = @"KEY_SORT_ITEM_INDEX";
static NSString* KEY_SORT_MODE_INDEX = @"KEY_SORT_MODE_INDEX";
// FileSort の対応 end

// 「拡大率指定の追加」の対応 start
/*
static const NSString* KEY_SPECIFY_MODE_INDEX = @"KEY_SPECIFY_MODE_INDEX";
static const NSString* KEY_SPECIFY_SCALE_VALUE = @"KEY_SPECIFY_SCALE_VALUE";
 */
static NSString* KEY_SPECIFY_MODE_INDEX = @"KEY_SPECIFY_MODE_INDEX";
static NSString* KEY_SPECIFY_SCALE_VALUE = @"KEY_SPECIFY_SCALE_VALUE";
// 「拡大率指定の追加」の対応 end

#define SETTINGS_DIRECTORY_NAME @"/Settings"
// FileSort の対応 start
#define SETTINGS_SUB_DIRECTORY_NAME @"/FileSettings"
// FileSort の対応 end

//『文書情報画面』の追加 start
#define SETTINGS_FILE_SUFFIX @"plist"
//『文書情報画面』の追加 end

// FileSort の対応 start
//- (BOOL) readKeepDocumentStatus
- (BOOL) readDocumentSettings
{
	//BOOL keepDocumentStatus = NO;
	keepStatus = NO;
	fileSortItemIndex = 0;
	fileSortModeIndex = 0;
	
	NSString* dirPath = [[self getDocumentDirectoryPath] retain];
	if (dirPath == nil) {
		return NO;
	}
	NSString* filePath = [dirPath stringByAppendingPathComponent:DW_GLOBAL_SETTINGS_FILE];
	if (filePath == nil) {
		// Memory Leak の対応 start
		[dirPath release];
		// Memory Leak の対応 end
		return NO;
	}
	
	NSFileManager *fileManager = [NSFileManager defaultManager];
	if ([fileManager fileExistsAtPath:filePath]) {
		NSMutableDictionary *dic = [[NSMutableDictionary alloc] initWithContentsOfFile:filePath];
		
		NSNumber *keepStatusObj = [[dic objectForKey:KEY_KEEP_STATUS] retain];
		if (keepStatusObj != nil) {
			//keepDocumentStatus = [keepStatusObj boolValue];
			keepStatus = [keepStatusObj boolValue];
		}
		[keepStatusObj release];
		
		NSNumber *itemIndexObj = [[dic objectForKey:KEY_SORT_ITEM_INDEX] retain];
		if (itemIndexObj != nil) {
			fileSortItemIndex = [itemIndexObj intValue];
		}
		[itemIndexObj release];
		
		NSNumber *modeIndexObj = [[dic objectForKey:KEY_SORT_MODE_INDEX] retain];
		if (modeIndexObj != nil) {
			fileSortModeIndex = [modeIndexObj intValue];
		}
		[modeIndexObj release];
        
        // 「拡大率指定の追加」の対応 start
        NSNumber *specifyModeIndexObj = [[dic objectForKey:KEY_SPECIFY_MODE_INDEX] retain];
		if (modeIndexObj != nil) {
			specifyScaleModeIndex = [specifyModeIndexObj intValue];
		}
		[specifyModeIndexObj release];
        
        NSNumber *specifyScaleObj = [[dic objectForKey:KEY_SPECIFY_SCALE_VALUE] retain];
		if (specifyScaleObj != nil) {
			specifyScale = [specifyScaleObj intValue];
		}
		[specifyScaleObj release];
        // 「拡大率指定の追加」の対応 end
		
		[dic release];
	}
	
	[dirPath release];
	
	//return keepDocumentStatus;
	return YES;
}

//- (void) writeKeepDocumentStatus:(BOOL)status
// 「拡大率指定の追加」の対応 start
/*
- (void) writeDocumentSettingsWithKeepStatus:(BOOL)status
                       withFileSortItemIndex:(int)itemIndex
                       withFileSortModeIndex:(int)modeIndex
*/  
- (void) writeDocumentSettingsWithKeepStatus:(BOOL)status
					   withFileSortItemIndex:(int)itemIndex
					   withFileSortModeIndex:(int)modeIndex
                             withSpecifyMode:(int)specifyModeIndex
                            withSpecifyScale:(int)scale
// 「拡大率指定の追加」の対応 start
{
	[self createSettingsDirectory];
	
	NSMutableDictionary *dic = [NSMutableDictionary dictionary];
	if (dic == nil) {
		return;
	}
	
	NSNumber *keepStatusObj = [NSNumber numberWithBool:status];
	[dic setObject:keepStatusObj forKey:KEY_KEEP_STATUS];
	
	NSNumber *itemIndexObj = [NSNumber numberWithInt:itemIndex];
	[dic setObject:itemIndexObj forKey:KEY_SORT_ITEM_INDEX];
	
	NSNumber *modeIndexObj = [NSNumber numberWithInt:modeIndex];
	[dic setObject:modeIndexObj forKey:KEY_SORT_MODE_INDEX];
    
    // 「拡大率指定の追加」の対応 start
    NSNumber *specifyModeIndexObj = [NSNumber numberWithInt:specifyModeIndex];
	[dic setObject:specifyModeIndexObj forKey:KEY_SPECIFY_MODE_INDEX];
    
    NSNumber *specifyScaleObj = [NSNumber numberWithInt:scale];
	[dic setObject:specifyScaleObj forKey:KEY_SPECIFY_SCALE_VALUE];
    // 「拡大率指定の追加」の対応 end
	
	NSString* dirPath = [[self getDocumentDirectoryPath] retain];
	if (dirPath == nil) {
		return;
	}
	
	NSString* filePath = [dirPath stringByAppendingPathComponent:DW_GLOBAL_SETTINGS_FILE];
	if (filePath != nil) {
		[dic writeToFile:filePath atomically:YES];
	}
	
	[dirPath release];
}
// FileSort の対応 end

// AR NO.17560 の対応 start
- (void) createSettingsDirectory
{
	NSArray *rootPaths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, 
															 NSUserDomainMask, 
															 YES); 
    NSString *documentsPath = [rootPaths objectAtIndex:0];
	NSFileManager *fileManager = [NSFileManager defaultManager];
	NSString *settingsDirectoryPath = [documentsPath stringByAppendingString:SETTINGS_DIRECTORY_NAME];
	BOOL isDirectoryExist = [fileManager fileExistsAtPath:settingsDirectoryPath];
	if (!isDirectoryExist) {
		[fileManager createDirectoryAtPath:settingsDirectoryPath 
			   withIntermediateDirectories:YES 
								attributes:nil 
									 error:nil];
	}
}
// AR NO.17560 の対応 end

// FileSort の対応 start
- (void) createSettingsSubDirectory
{
	[self createSettingsDirectory];
	NSString* settingsPath = [[self getDocumentDirectoryPath] retain];
	NSFileManager *fileManager = [NSFileManager defaultManager];
	NSString *settingsSubDirectoryPath = [settingsPath stringByAppendingString:SETTINGS_SUB_DIRECTORY_NAME];
	BOOL isDirectoryExist = [fileManager fileExistsAtPath:settingsSubDirectoryPath];
	if (!isDirectoryExist) {
		[fileManager createDirectoryAtPath:settingsSubDirectoryPath 
			   withIntermediateDirectories:YES 
								attributes:nil 
									 error:nil];
	}
	
	
	[settingsPath release];
}
// FileSort の対応 end

- (BOOL) readDocumentStatusWithFileName:(NSString*)name 
					   withCreationDate:(NSString*)date 
					   withDocumentSize:(NSString*)size
{
	if (name == nil || date == nil || size == nil) {
		return NO;
	}
	
	// Memory Leak の対応 start
	NSString *fileName = [name retain];
	// Memory Leak の対応 end
	
	// get plist name with file name.
	NSMutableString* plistName = [[NSMutableString alloc]init];
	[plistName appendString:fileName];
	[plistName appendString:@".plist"];
	
	NSString *filePath = [[self getSettingsFilePathWithFileName:plistName] retain];
	if (filePath == nil) {
		// Memory Leak の対応 start
		[plistName release];
		[fileName release];
		// Memory Leak の対応 end
		return NO;
	}
	
	NSMutableDictionary *dic = [[NSMutableDictionary alloc] initWithContentsOfFile:filePath];
	if (dic == nil) {
		// Memory Leak の対応 start
		[plistName release];
		//add by yangjx 0608 start
		[filePath release];
		//add by yangjx 0608 end
		[fileName release];
		// Memory Leak の対応 end
		return NO;
	}
	
	// Memory Leak の対応 start
	NSString *fileDate = [date retain];
	NSString *fileSize = [size retain];
	// Memory Leak の対応 end
	
	NSString *dateRecord = [[dic objectForKey:KEY_CREATION_DATE] retain];
	NSString *sizeRecord = [[dic objectForKey:KEY_DOCUMENT_SIZE] retain];
	
	BOOL bResult = NO;
	if (([dateRecord isEqualToString:fileDate] && [sizeRecord isEqualToString:fileSize])) {
		
		NSNumber *pageIndexObj = [[dic objectForKey:KEY_PAGE_INDEX] retain];
		pageIndex = [pageIndexObj intValue];
		[pageIndexObj release];
		
		NSNumber *pageScaleObj = [[dic objectForKey:KEY_PAGE_SCALE] retain];
		pageScale = [pageScaleObj longValue];
		[pageScaleObj release];
		
		NSNumber *pagePointXObj = [[dic objectForKey:KEY_PAGE_POINT_X] retain];
		pagePointX = [pagePointXObj floatValue];
		[pagePointXObj release];
		
		NSNumber *pagePointYObj = [[dic objectForKey:KEY_PAGE_POINT_Y] retain];
		pagePointY = [pagePointYObj floatValue];
		[pagePointYObj release];
		
		NSNumber *facingModeObj = [[dic objectForKey:KEY_FACE_MODE] retain];
		facingMode = [facingModeObj intValue];
		[facingModeObj release];
		
		NSNumber *fontOrientationObj = [[dic objectForKey:KEY_FONT_ORIEN] retain];
		fontOrientationH = [fontOrientationObj boolValue];
		[fontOrientationObj release];
		
		if ([[fileName pathExtension] caseInsensitiveCompare:@"xdw"] == NSOrderedSame ||
			[[fileName pathExtension] caseInsensitiveCompare:@"xbd"] == NSOrderedSame) {
			
			NSNumber *showAnnotationObj = [[dic objectForKey:KEY_SHOW_ANNO] retain];
			showAnnotation = [showAnnotationObj boolValue];
			[showAnnotationObj release];
		}
		
		NSNumber *pageStatusObj = [[dic objectForKey:KEY_PAGE_STATUS] retain];
		pageStatus = [pageStatusObj intValue];
		[pageStatusObj release];
		
		bResult = YES;
	} else {
		//AR No.17581 start
		[self deleteSettingsFileWithFileName:plistName];
		//AR No.17581 end
	}
	
	[fileName release];
	[fileDate release];
	[fileSize release];
	[plistName release];
	[filePath release];
	[dateRecord release];
	[sizeRecord release];
	[dic release];
	
	return bResult;
}

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
							withFileSize:(NSString *)size
{
	if (name == nil || date == nil || size == nil) {
		return;
	}
	
	// FileSort の対応 start
	[self createSettingsSubDirectory];
	// FileSort の対応 end
	
	NSString *fileName = [name retain];
	NSString *fileDate = [date retain];
	NSString *fileSize = [size retain];
	
	// get file plist name.
	NSMutableString* plistName = [[NSMutableString alloc]init];
	[plistName appendString:fileName];
	[plistName appendString:@".plist"];
	
	// get dir path.
	// Memory Leak の対応 start
	// NSString *dirPath = [self getDocumentDirectoryPath];
	
	// FileSort の対応 start
	//NSString *dirPath = [[self getDocumentDirectoryPath] retain];
	NSString *dirPath = [[self getSettingsSubDirectoryPath] retain];
	// FileSort の対応 end
	
	// Memory Leak の対応 end
	if (dirPath == nil) {
		return;
	}
	
	// create file path.
	NSString *filePath = [dirPath stringByAppendingPathComponent:plistName];
	if (filePath == nil) {
		// Memory Leak の対応 start
		[dirPath release];
		//add by yangjx 0608 start
		[plistName release];
		//add by yangjx 0608 end
		// Memory Leak の対応 end
		return;
	}
	
	NSMutableDictionary *dic = [NSMutableDictionary dictionary];
	if (dic != nil) {
		NSNumber *pageIndexObj = [NSNumber numberWithInt:index];
		[dic setObject:pageIndexObj forKey:KEY_PAGE_INDEX];
		
		NSNumber *pageScaleObj = [NSNumber numberWithLong:scale];
		[dic setObject:pageScaleObj forKey:KEY_PAGE_SCALE];
		
		NSNumber *pagePointXObj = [NSNumber numberWithFloat:pointX];
		[dic setObject:pagePointXObj forKey:KEY_PAGE_POINT_X];
		
		NSNumber *pagePointYObj = [NSNumber numberWithFloat:pointY];
		[dic setObject:pagePointYObj forKey:KEY_PAGE_POINT_Y];
		
		NSNumber *facingModeObj = [NSNumber numberWithInt:mode];
		[dic setObject:facingModeObj forKey:KEY_FACE_MODE];
		
		NSNumber *fontOrientationObj = [NSNumber numberWithBool:orientation];
		[dic setObject:fontOrientationObj forKey:KEY_FONT_ORIEN];
		
		if ([[fileName pathExtension] caseInsensitiveCompare:@"xdw"] == NSOrderedSame ||
			[[fileName pathExtension] caseInsensitiveCompare:@"xbd"] == NSOrderedSame) {
			NSNumber *showAnnotationObj = [NSNumber numberWithBool:show];
			[dic setObject:showAnnotationObj forKey:KEY_SHOW_ANNO];
		}
		
		NSNumber *pageStatusObj = [NSNumber numberWithInt:status];
		[dic setObject:pageStatusObj forKey:KEY_PAGE_STATUS];
		
		[dic setObject:fileDate forKey:KEY_CREATION_DATE];
		
		[dic setObject:fileSize forKey:KEY_DOCUMENT_SIZE];
	}
	
	[dic writeToFile:filePath atomically:YES];
	
	// release
	[fileName release];
	[fileDate release];
	[fileSize release];
	[plistName release];
	// Memory Leak の対応 start
	[dirPath release];
	// Memory Leak の対応 end
}

- (void) deleteSettingsFileWithFileName:(NSString*)name
{
	if (name == nil) {
		return;
	}
	
	NSString *fileName = [name retain];
	NSString *filePath = [self getSettingsFilePathWithFileName:fileName];
	if (filePath != nil) {
		NSFileManager *fileManager = [NSFileManager defaultManager];
		[fileManager removeItemAtPath:filePath error:nil];
	}
	[fileName release];
}

- (void) deleteAllSettingsFileInDirectory
{
	// Memory Leak の対応 start
	// NSString *dirPath = [self getDocumentDirectoryPath];
	// FileSort の対応 start
	//NSString *dirPath = [[self getDocumentDirectoryPath] retain];
	NSString *dirPath = [[self getSettingsSubDirectoryPath] retain];
	// FileSort の対応 end
	// Memory Leak の対応 end
	if (dirPath == nil) {
		return;
	}
	NSFileManager *fileManager = [NSFileManager defaultManager];
	[fileManager removeItemAtPath:dirPath error:nil];
	
	// Memory Leak の対応 start
	[dirPath release];
	// Memory Leak の対応 end
}

- (NSString*) getDocumentDirectoryPath
{
	NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, 
														 NSUserDomainMask, 
														 YES); 
    NSString *directoryPath = [paths objectAtIndex:0];
	NSString *settingsDirectoryPath = [directoryPath stringByAppendingString:SETTINGS_DIRECTORY_NAME];	
	return settingsDirectoryPath;
}

// AR NO.17560 の対応 start
- (NSString*) getSettingsSubDirectoryPath
{
	NSString *dirPath = [[self getDocumentDirectoryPath] retain];
	if (dirPath == nil) {
		return nil;
	}
	
	NSString *settingsSubDirectoryPath = [dirPath stringByAppendingString:SETTINGS_SUB_DIRECTORY_NAME];	
	
	[dirPath release];
	
	return settingsSubDirectoryPath;
}
// AR NO.17560 の対応 end

- (NSString*) getSettingsFilePathWithFileName:(NSString*)name
{
	if (name == nil) {
		return nil;
	}
	
	NSString *filePath = nil;
	// Memory Leak の対応 start
	// NSString *fileName = [name retain];
	// Memory Leak の対応 end
	
	// FileSort の対応 start
	//NSString *dirPath = [[self getDocumentDirectoryPath] retain];
	NSString *dirPath = [[self getSettingsSubDirectoryPath] retain];
	// FileSort の対応 end
	
	if (dirPath == nil) {
		return nil;
	}
	// Memory Leak の対応 start
	NSString *fileName = [name retain];
	// Memory Leak の対応 end
	NSFileManager *filemanager = [NSFileManager defaultManager];
	NSArray *files = [filemanager contentsOfDirectoryAtPath:dirPath error:nil];
	if (files == nil) {
		// Memory Leak の対応 start
		[dirPath release];
		[fileName release];
		// Memory Leak の対応 end
		return nil;
	}
	
	for (NSString* file in files) {
		if ([file isEqualToString:fileName] == YES) {
			filePath = [dirPath stringByAppendingPathComponent:fileName];
			break;
		}
	}
	
	[fileName release];
	[dirPath release];
	
	return filePath;
}

//File Multiple Del by Yangjx 0613 start
//create trash directory
- (NSString *) createTrashDirectory
{
	BOOL createSuccess;
	NSArray *rootPaths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, 
															 NSUserDomainMask, 
															 YES); 
    NSString *documentsPath = [rootPaths objectAtIndex:0];
	NSFileManager *fileManager = [NSFileManager defaultManager];
	NSString *trashDirectoryPath = [documentsPath stringByAppendingString:_TRASH_DIR_];
	BOOL isDirectoryExist = [fileManager fileExistsAtPath:trashDirectoryPath];
	if (!isDirectoryExist) {
	    createSuccess =	[fileManager createDirectoryAtPath:trashDirectoryPath 
							   withIntermediateDirectories:YES 
												attributes:nil 
													 error:nil];
	} else {
		return trashDirectoryPath;
	}
	
	if (createSuccess) {
		return trashDirectoryPath;
	}
    
	return nil;
}

// delete file move file from documentDir to trashDir
- (BOOL) moveDocumentFromSrcPath:(NSString*)src toDestPath:(NSString *)dest
{
	if (src == nil || dest == nil)
	{
		return NO;
	}
	
	NSString* srcPath = [src retain];
    NSString *destPath = [dest retain];
	
	UIAlertView *alertView = nil;
	NSFileManager *fileManager = [NSFileManager defaultManager];
	BOOL bSuccess = [fileManager fileExistsAtPath:srcPath];
	if (bSuccess == NO) {
		alertView = [[UIAlertView alloc]initWithTitle:NSLocalizedString(@"TITLE_ALERT_APPNAME", nil) 
											  message:NSLocalizedString(@"MSG_FINDFILE_FAIL", nil)
											 delegate:nil
									cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_OK", nil)
									otherButtonTitles:nil];
		[alertView show];
		[alertView release];
	} else {
		
		NSString *fileName = [srcPath lastPathComponent];
		NSString *trashPath = [destPath stringByAppendingPathComponent:fileName];
		
		bSuccess = [fileManager moveItemAtPath:srcPath 
										toPath:trashPath error:nil];
		if (bSuccess != YES) {
			alertView = [[UIAlertView alloc]initWithTitle:NSLocalizedString(@"TITLE_ALERT_APPNAME", nil) 
												  message:NSLocalizedString(@"MSG_DELETEFILE_FAIL", nil)
												 delegate:nil
										cancelButtonTitle:NSLocalizedString(@"BUTTON_TITLE_OK", nil)
										otherButtonTitles:nil];
			[alertView show];
			[alertView release];
		}
	}
	
	// release
	[srcPath release];
	[destPath release];
	
	return bSuccess;
}

// yangjx 20110622 start
// AR 17863
// cancel delete move file from trashDir to doucmentDir
- (BOOL) moveFileFromTrashToDocument 
{
	BOOL result = NO;
	NSString *trashDir = [[self createTrashDirectory] retain];
	if (trashDir == nil) {
		return result;
	}
    
	NSFileManager *fileManager = [NSFileManager defaultManager];
	NSArray *fileItemList = [fileManager contentsOfDirectoryAtPath:trashDir error:nil]; 
	
	NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];    
	
	for (NSString *fileItem in fileItemList) {
		NSString *srcFilePath = [trashDir stringByAppendingPathComponent:fileItem];
		NSString *dstFilePath = [[self checkFileNameInDocument:fileItem] retain];
		
		if (srcFilePath != nil && dstFilePath != nil) {
			result = [fileManager moveItemAtPath:srcFilePath 
										  toPath:dstFilePath error:nil];
		}
		
		[dstFilePath release];
	}
	
	[pool release];
	//release
	[trashDir release];
	return result;
}

- (NSString *) checkFileNameInDocument:(NSString *)moveFileName
{   
	if (moveFileName == nil) {
		return nil;
	}
	
	NSInteger fileNum = 0;
	BOOL isDir = false;
	NSString *upDataFileName = nil;
	
	NSFileManager *fileManager = [NSFileManager defaultManager];
	NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES); 
    NSString *dir = [paths objectAtIndex:0];
	NSString *dstFilePath = [dir stringByAppendingPathComponent:moveFileName];
	
	while ([fileManager fileExistsAtPath:dstFilePath isDirectory:&isDir]) {
		if (!isDir) {
			fileNum++;
			
			upDataFileName = [[self changeFileName:moveFileName withNum:fileNum] retain];
			
			if (upDataFileName != nil) {
				dstFilePath = [dir stringByAppendingPathComponent:upDataFileName];
			}
			
			[upDataFileName release];
		}
	}
	
	return dstFilePath; 	
}

- (NSString *) changeFileName:(NSString*)fileName withNum:(NSInteger)num
{
	NSString *file = nil;
	NSString *pathExtension = nil;
	
	if (fileName != nil) {
		
		file = [fileName stringByDeletingPathExtension];
		pathExtension = [fileName pathExtension];
		file = [file stringByAppendingFormat:@"-%d",num];
		file = [file stringByAppendingPathExtension:pathExtension];
		
		// yangjx 2011/06/29 start
		// AR.NO 17871 の対応
		if ([file length] > 255) {
			//file = [strArray objectAtIndex:0];
			file = [fileName stringByDeletingPathExtension];
			file = [file substringToIndex:([file length] - 3)];
			file = [file stringByAppendingFormat:@"-%d",num];
			file = [file stringByAppendingPathExtension:pathExtension];
		}
		// yangjx 2011/06/29 end
	}
	
	return file;
}
// yangjx 20110622 end
- (void) deleteAllFilesFromTrashDirectory
{
    NSString *trashDir = [[self createTrashDirectory] retain];
	if (trashDir == nil) {
		return;
	}
    
	NSFileManager *fileManager = [NSFileManager defaultManager];
	NSArray *fileItemList = [fileManager contentsOfDirectoryAtPath:trashDir error:nil];
	for (NSString *fileItem in fileItemList){
		if (fileItem != nil) {
			NSMutableString* plistFileName = [[NSMutableString alloc]initWithString:fileItem];
			[plistFileName appendString:@".plist"];
			[self deleteSettingsFileWithFileName:plistFileName];
			[plistFileName release];
		}
	}
	[fileManager removeItemAtPath:trashDir error:nil];
	[trashDir release];
}

// get file path
- (NSString*) getDocumentFilePathWithFileName:(NSString *)fileName
{
	NSString *documentFilePath = nil;
    
	NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
	NSString *documentDirectory = [paths objectAtIndex:0];
	documentFilePath = [documentDirectory stringByAppendingPathComponent:fileName];
    
	return documentFilePath;
}


// yangjx 20110622 start
//AR17848 sortの対応
- (void) writeDocumentSettingsWithFileSortItemIndex:(int)itemIndex
							  withFileSortModeIndex:(int)modeIndex
{
	[self createSettingsDirectory];
	NSString* dirPath = [[self getDocumentDirectoryPath] retain];
	if (dirPath == nil) {
		return;
	}
	NSString* filePath = [dirPath stringByAppendingPathComponent:DW_GLOBAL_SETTINGS_FILE];
	
	if (filePath != nil) {
		NSMutableDictionary *dic = [[NSMutableDictionary alloc] initWithContentsOfFile:filePath];
		
		NSNumber *itemIndexObj = [NSNumber numberWithInt:itemIndex];
		[dic setObject:itemIndexObj forKey:KEY_SORT_ITEM_INDEX];
		
		NSNumber *modeIndexObj = [NSNumber numberWithInt:modeIndex];
		[dic setObject:modeIndexObj forKey:KEY_SORT_MODE_INDEX];
		
		[dic writeToFile:filePath atomically:YES];
		
		[dic release];
	}
	
	[dirPath release];	
}
// yangjx 20110622 end
//File Multiple Del by Yangjx 0613 end


//『文書情報画面』の追加 start
- (FileUpdateErrorCode)updateFileNameWithSrcName:(NSString *)srcName 
                                    withDestName:(NSString *)dstName 
{
	if (srcName != nil && dstName != nil) {
		FileUpdateErrorCode errorCode = FILEUPDATE_ERRORCODE_SUCCESS;
		NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
		NSString *dirPath = [paths objectAtIndex:0];
		NSString *srcPath = [dirPath stringByAppendingPathComponent:srcName];
		NSFileManager *fileManager = [[NSFileManager alloc] init];
		BOOL isDirectory = NO;
		if ([fileManager fileExistsAtPath:srcPath isDirectory:&isDirectory] 
			&& !isDirectory) {
            // tongtx 20110705 start
			// AR NO.17891 の対応
            /*
            if ([dstName length] == 0) {
                errorCode = FILEUPDATE_ERRORCODE_FILENAME_EMPTY;
                goto ErrorEnd;
            */
            
			if ([[srcName pathExtension] length] > 0 ) {
				if ([dstName length] - [[srcName pathExtension] length] - 1 == 0) {
					errorCode = FILEUPDATE_ERRORCODE_FILENAME_EMPTY;
					goto ErrorEnd;
				}
			} else {
				if ([dstName length] == 0) {
					errorCode = FILEUPDATE_ERRORCODE_FILENAME_EMPTY;
					goto ErrorEnd;
				}
			}
			// tongtx 20110705 end
            
            // liuqw 20110701 start
            // AR NO.17883 の対応
            /*
            if ([dstName rangeOfString:@"/" options:NSCaseInsensitiveSearch].location != NSNotFound ||
                [dstName rangeOfString:@"／" options:NSCaseInsensitiveSearch].location != NSNotFound ||
                [dstName rangeOfString:@":" options:NSCaseInsensitiveSearch].location != NSNotFound ||
                [dstName rangeOfString:@"：" options:NSCaseInsensitiveSearch].location != NSNotFound) {
                errorCode = FILEUPDATE_ERRORCODE_INVALID_CHAR;
                goto ErrorEnd;
            }
            */
            
			if ([dstName rangeOfString:@"/" options:NSCaseInsensitiveSearch].location != NSNotFound ||
                [dstName rangeOfString:@":" options:NSCaseInsensitiveSearch].location != NSNotFound) {
				errorCode = FILEUPDATE_ERRORCODE_INVALID_CHAR;
				goto ErrorEnd;
			}
            // liuqw 20110701 end
            
            // tongtx 20110708 start
			// AR NO.17914 の対応
			if([dstName characterAtIndex:0] == '.'){
				errorCode = FILEUPDATE_ERRORCODE_OTHERS;
				goto ErrorEnd;
			}
			// tongtx 20110708 end
			
			// 20110623 tongtx start	
			// AR 17857の対応
            /*
            if ([[dstName stringByDeletingPathExtension] length] > FILENAME_MAX_LENGTH) {
                errorCode = FILEUPDATE_ERRORCODE_OVERLENGTH;
                goto ErrorEnd;
            }
            */
			if ([dstName length] > FILENAME_MAX_LENGTH) {
				errorCode = FILEUPDATE_ERRORCODE_OVERLENGTH;
				goto ErrorEnd;
			}
			// 20110623 tongtx end
            
			NSString *dstPath = [dirPath stringByAppendingPathComponent:dstName];
			NSArray *files = [fileManager contentsOfDirectoryAtPath:dirPath error:NULL];
			for (NSString *item in files) {
				// 20110623 tongtx start
				// AR17853の対応
				if ([srcName isEqualToString:item]) {
					continue;
				}
				// 20110623 tongtx end
				if ([item caseInsensitiveCompare:dstName] == NSOrderedSame) {
					errorCode = FILEUPDATE_ERRORCODE_FILENAME_EXISTED;
					goto ErrorEnd;
				}
			}
			if ([fileManager moveItemAtPath:srcPath toPath:dstPath error:NULL]) {
				NSString *fileSettingPath = [self getSettingsSubDirectoryPath];
				if (fileSettingPath != nil) {
					NSString *srcSettingPath = [fileSettingPath stringByAppendingPathComponent:
												[srcName stringByAppendingPathExtension:SETTINGS_FILE_SUFFIX]];
					if ([fileManager fileExistsAtPath:srcSettingPath isDirectory:&isDirectory] && !isDirectory) {
						NSString *dstSettingPath = [fileSettingPath stringByAppendingPathComponent:
													[dstName stringByAppendingPathExtension:SETTINGS_FILE_SUFFIX]];
						if ([fileManager moveItemAtPath:srcSettingPath toPath:dstSettingPath error:NULL]) {
							NSDictionary *fileAttributes = [fileManager attributesOfItemAtPath:dstPath error:NULL];
							NSString *createDate = [[fileAttributes objectForKey:NSFileCreationDate] description];						
							NSDictionary *settingAttributes = [[NSDictionary alloc] initWithContentsOfFile:dstSettingPath];
							[settingAttributes setValue:createDate forKey:KEY_CREATION_DATE];
							[settingAttributes writeToFile:dstSettingPath atomically:YES];
							[settingAttributes release];
						}
					}
				}
			}
			else {
				errorCode = FILEUPDATE_ERRORCODE_OTHERS;
				goto ErrorEnd;
			}
		}
		else {
			errorCode = FILEUPDATE_ERRORCODE_NOT_EXISTED;
			goto ErrorEnd;
		}
		[fileManager release];
		return errorCode;
	ErrorEnd:
		[fileManager release];
		return errorCode;
	}
	return FILEUPDATE_ERRORCODE_FILENAME_EMPTY;
}
//『文書情報画面』の追加 end

// liuqw 20110628 start
// AR NO.17871 の対応
- (BOOL) isDocumentCanSaveSettings:(NSString*)fileName
{
    BOOL isCanSave = NO;
    
    // liuqw 2011/07/14 start
    if (keepStatus == NO) {
        return YES;
    }
    // liuqw 2011/07/14 end
    
    if (fileName != nil) {
        int length = [fileName length];
        if (length + 6 > FILENAME_MAX_LENGTH) {
            isCanSave = NO;
        } else {
            isCanSave = YES;
        }
    }
    
    return isCanSave;
}
// liuqw 20110628 end

// tongtx 2011/08/15 start
// Briefcaseと連携機能の追加
- (BOOL) createFileAtDirectoryPath:(NSString *)directoryPath 
                              file:(NSString *)filename 
                          contents:(NSData *)data
                       overwritten:(BOOL)canOverwritten 
{
	BOOL result = NO;
	if ([data length] > 0 && (filename != nil)) {
		NSFileManager *fileManager = [[NSFileManager alloc] init];
		NSString *newFilename = filename;
		if (!canOverwritten) {
			[self changeExistedFilenameAtPath:directoryPath fromFile:filename toFile:&newFilename];
			if (targetFilename == nil) {
				targetFilename = [newFilename copy];
			}
		}
		NSString *filePath = [directoryPath stringByAppendingPathComponent:newFilename];
		result = [fileManager createFileAtPath:filePath contents:data attributes:nil];
		[fileManager release];
	}

	return result;
}

- (BOOL) createDirectoryAtPath:(NSString *)path
{
	BOOL isCreated = NO;
    
	if (path != nil) {
		NSFileManager *fileManager = [[NSFileManager alloc] init];
		if ([fileManager fileExistsAtPath:path]) {
			isCreated = YES;
		} else {
			if ([fileManager createDirectoryAtPath:path 
					   withIntermediateDirectories:YES 
										attributes:nil 
											 error:nil]) {
				isCreated = YES;
			}
		}
		[fileManager release];
	}
    
	return isCreated;
}

- (NSData*) fileContentsAtPath:(NSString *)path
{
	NSFileManager *fileManager = [[NSFileManager alloc] init];
	NSData *data = [fileManager contentsAtPath:path];
	[fileManager release];
    
	return data;
}

- (void) removeFilesAtPath:(NSString *)path
{
	NSFileManager *fileManager = [[NSFileManager alloc] init];
	[fileManager removeItemAtPath:path error:NULL];
	[fileManager release];
}

- (BOOL) compareDataWithSrcPath:(NSString *)srcPath 
                    withDstPath:(NSString *)dstPath
{
	// AR19031
	// 2010.03.02 M.Chikyu start.
	
	/*
	 NSFileManager *fileManager = [[NSFileManager alloc] init];
	 NSData *srcData = [fileManager contentsAtPath:srcPath];
	 NSData *dstData = [fileManager contentsAtPath:dstPath];
	 [fileManager release];
	 
	 return [srcData isEqualToData:dstData];
	 */
	
	
	// ファイルが異なると判断できる場合のみNOを出力、同じかファイル情報が取れない場合はYES
	// (破損したファイルでファイルコピーを実行させないため）
	
	// compare file state
	NSFileManager *fileManager = [[[NSFileManager alloc] init] autorelease];
	
	// get file attributes
	NSString* srcFileSize = nil;
	NSString* srcFileDate = nil;
	NSString* dstFileSize = nil;
	NSString* dstFileDate = nil;
	
	// get src file attributes
	NSDictionary* srcFileAttrs = [fileManager attributesOfItemAtPath:srcPath error:nil];
	
	// get temp file attributes
	NSDictionary* dstFileAttrs = [fileManager attributesOfItemAtPath:dstPath error:nil];
	
	if (srcFileAttrs == nil || dstFileAttrs == nil)
	{
		// ファイル情報が取れないので異なるファイルと判断できない
		return YES;
	}
	
	srcFileSize = [srcFileAttrs objectForKey:NSFileSize];
	srcFileDate = [srcFileAttrs objectForKey:NSFileModificationDate];
	
	if (srcFileSize == nil || srcFileDate == nil)
	{
		// ファイル情報が取れないので異なるファイルと判断できない
		return YES;
	}
	
	dstFileSize = [dstFileAttrs objectForKey:NSFileSize];
	dstFileDate = [dstFileAttrs objectForKey:NSFileModificationDate];
	
	if (dstFileSize == nil || dstFileDate == nil)
	{
		// ファイル情報が取れないので異なるファイルと判断できない
		return YES;
	}
	
	if ([dstFileSize compare:srcFileSize] == NSOrderedSame &&
		[dstFileDate compare:srcFileDate] == NSOrderedSame)
	{
		// ファイルサイズと日付が同じ場合は同じファイルと判断
		return YES;
	}
	
	// ファイルサイズまたはファイル日付が違う場合は異なるファイルと判断
	return NO;
	
	// 2010.03.02 M.Chikyu end.
}

// liuqw 2012/03/06 start
// AR NO.19019の対応
- (BOOL) copyEditedFileToDocuments:(NSString*)srcPath 
					  destFileName:(NSString *)dstFileName 
					   overwritten:(BOOL)overwrite
{
	if (srcPath == nil || dstFileName == nil) return NO;
	
	// get new file name.
	NSString *newFileName_ = dstFileName;
	NSString *documentsDirectory_ = [self getDocumentFilePathWithFileName:nil];
	
	NSFileManager *fileManager = [NSFileManager defaultManager];
	
	NSString *dstPath_ = [documentsDirectory_ stringByAppendingPathComponent:newFileName_];
	if (overwrite == YES) 
	{
		if ([fileManager fileExistsAtPath:dstPath_])
		{
			[fileManager removeItemAtPath:dstPath_ error:nil];
		}
	}
	else
	{
		// 2012.03.07 M.Chikyu start.
		if (targetFilename != nil)
		{
			return NO;
		}
		// 2012.03.07 M.Chikyu end.

		[self changeExistedFilenameAtPath:documentsDirectory_ fromFile:dstFileName toFile:&newFileName_];
		dstPath_ = [documentsDirectory_ stringByAppendingPathComponent:newFileName_];

		// 2012.03.07 M.Chikyu start.
		/*
		if (targetFilename == nil)
		{
			targetFilename = [newFileName_ copy];
		}
		 */

		targetFilename = [newFileName_ copy];
		// 2012.03.07 M.Chikyu end.
	}
	
	return [fileManager copyItemAtPath:srcPath toPath:dstPath_ error:nil];
}
// liuqw 2012/03/06 end

- (void)dealloc{
	[targetFilename release];
	[super dealloc];
}
// tongtx 2011/08/15 end 
@end
