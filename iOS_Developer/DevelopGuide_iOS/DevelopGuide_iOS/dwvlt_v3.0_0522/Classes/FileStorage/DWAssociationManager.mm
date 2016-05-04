//
//  DWAssociationManager.m
//  DWViewer
//
//  Created by tongtiexin on 11-8-12.
//  Copyright 2011 Neusoft dalian. All rights reserved.
//

#import "DWAssociationManager.h"
#import "DWViewerGUIConst.h"
#import "DocumentSettingsManager.h"

@implementation DWAssociationManager




+ (BOOL) readDataFromPasteBoard:(NSString *)directoryPath file:(NSString *)filename
{
    BOOL isPasted = NO;
    
    UIPasteboard *board = [UIPasteboard pasteboardWithName:POSTEBOARD_NAME create:NO];
	if (board != nil) {
		board.persistent = YES;
		NSData *data = [board dataForPasteboardType:POSTEBOARDUTI_BRIEFCASE_TO_VLT20];
		if ([data length] > 0) {
			DocumentSettingsManager *settingsManager = [[DocumentSettingsManager alloc] init];
			[settingsManager removeFilesAtPath:directoryPath];
			if ([settingsManager createDirectoryAtPath:directoryPath]) {
				isPasted = [settingsManager createFileAtDirectoryPath:directoryPath 
                                                                 file:filename
                                                             contents:data 
                                                          overwritten:YES];
			}
			[settingsManager release];
		}
	}
    
	return isPasted;
}

+ (BOOL) writeDataToPasteBoard:(NSString *)path
{
    NSData *dataFile = [NSData dataWithContentsOfMappedFile:path]; 
	NSUInteger bytes = [dataFile length];  
	
	// liuqw 2012/03/06 start
	// AR NO.19019の対応
	
	if (bytes > (1024 * 1024 * 5)) {
		return NO;
	}
	
	// liuqw 2012/03/06 end
	
	if (bytes > 0) {
		[UIPasteboard removePasteboardWithName:POSTEBOARD_NAME];
		UIPasteboard *board = [UIPasteboard pasteboardWithName:POSTEBOARD_NAME create:YES];
		board.persistent = YES;
		[board setData:dataFile forPasteboardType:POSTEBOARDUTI_VLT20_TO_BRIEFCASE];
		NSData *checkData = [board dataForPasteboardType:POSTEBOARDUTI_VLT20_TO_BRIEFCASE];
		if ([checkData length] > 0) {
			return YES;
		}
	}
    
	return NO;
}


// tongtx 20120206 start
// MTA連動機能の対応
+ (NSData *) readFileDataFromPasteBoard:(NSString *)name
                                   type:(NSString *)type
{
    if (name == nil || type == nil) 
    {
        return nil;
    }
    
    NSData *file_data = nil;
    UIPasteboard *board = [UIPasteboard pasteboardWithName:name create:NO];
    if (board != nil) 
    {
        file_data = [board dataForPasteboardType:type];
    }
    
    return file_data;
}

+ (BOOL) writeFileDataToPasteBoard:(NSString *)name 
                              type:(NSString *)type 
                          filepath:(NSString *)path
{
    if (name == nil || type == nil || path == nil) 
    {
        return NO;
    }
    
    NSData *data_ = [NSData dataWithContentsOfMappedFile:path]; 
	
	// liuqw 2012/03/06 start
	// AR NO.19019の対応
	
	if ([data_ length] > (1024 * 1024 * 5)) {
		return NO;
	}
	
	// liuqw 2012/03/06 end
	
	if (data_ != nil && [data_ length] > 0)
    {
		[UIPasteboard removePasteboardWithName:name];
        
		UIPasteboard *board = [UIPasteboard pasteboardWithName:name create:YES];
		board.persistent = YES;
		[board setData:data_ forPasteboardType:type];
        
		NSData *checkData = [board dataForPasteboardType:type];
		if ([checkData length] > 0)
        {
			return YES;
		}
	}
    
	return NO;
}
// tongtx 20120206 end

- (void)dealloc{
	[super dealloc];
}
@end
