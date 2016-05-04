//
//  FileManager.m
//  DevelopGuide_iOS
//
//  Created by neusoft  on 12-3-8.
//  Copyright 2012年 __MyCompanyName__. All rights reserved.
//

#import "FileManager.h"


@implementation FileManager

static FileManager *fileManager_ = nil;

- (id) init {
    self = [super init];
    if (self) {
        
    }
    return self;
}  

+ (FileManager *) shareFileManager
{
    @synchronized(self) {
        if (fileManager_ == nil) {
            fileManager_ = [[self alloc] init];
        }
    }
    return fileManager_;

}

- (void) setReadOnlyFile:(NSString *)filePath
{
    if (filePath == nil) {
        return;
    }
    /*
     * key NSFilePosixPermissions代表文件权限
     * 参数0555 
     * 第一位0代表目录，第一位1代表文件。
     * 第二位代表拥有者权限，第三位代表同组用户权限，第四位代表其他用户权限
     * 5代表文件或目录可读，可执行。
     */
    
    NSFileManager *fileMgr = [NSFileManager defaultManager];
    BOOL isDir = NO;
    NSDictionary *attrs =  nil;
    
    if ([fileMgr fileExistsAtPath:filePath isDirectory:&isDir]) 
    {
        if (isDir == YES) 
        {
            attrs =  [NSDictionary dictionaryWithObject:[NSNumber numberWithUnsignedLong:0555]
                                                 forKey:NSFilePosixPermissions];
        }
        else
        {
            attrs =  [NSDictionary dictionaryWithObject:[NSNumber numberWithUnsignedLong:1555]
                                                 forKey:NSFilePosixPermissions];
        }
        
        [fileMgr setAttributes:attrs ofItemAtPath:filePath error:nil];
    }

}

- (void) getFileAttribute:(NSString *)filePath
{
    NSFileManager *fileMgr = [NSFileManager defaultManager];
    NSDictionary *fileAttrs = [fileMgr attributesOfItemAtPath:filePath error:nil];
    NSString *fileSize = [fileAttrs objectForKey:NSFileSize];
    NSString *fileUpdateDate = [fileAttrs objectForKey:NSFileModificationDate];
    NSLog(@"file size is %@ and file update is %@",fileSize,fileUpdateDate);
}

- (void) writeDataToFile
{
    NSFileManager *fileMgr = [NSFileManager defaultManager];
    
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
	NSString *documentsDirectory = [paths objectAtIndex:0];
    NSString *logPath = [documentsDirectory stringByAppendingPathComponent: 
						 [NSString stringWithFormat: @"%@.txt", @"log"]];
    
    if ([fileMgr fileExistsAtPath:logPath] == NO) {
		[fileMgr createFileAtPath:logPath contents:nil attributes:nil];
	}
    
    NSFileHandle *fh = [NSFileHandle fileHandleForWritingAtPath:logPath];
    [fh seekToEndOfFile]; 
    NSData *data = [@"\n" dataUsingEncoding:NSUTF8StringEncoding];
    [fh writeData:data];
    NSData *wdata = [@"wirte content" dataUsingEncoding:NSUTF8StringEncoding];
    [fh writeData:wdata];
}

+ (NSString *) createFilePath:(NSString *)filePath
{
    if (filePath == nil) {
        return  nil;
    }
    NSFileManager *fileMgr = [NSFileManager defaultManager];
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
	NSString *documentsDirectory = [paths objectAtIndex:0];
    NSString *fileSavePath = [documentsDirectory stringByAppendingPathComponent:filePath];
    if ([fileMgr fileExistsAtPath:fileSavePath] == NO) {
        [fileMgr createDirectoryAtPath:fileSavePath 
               withIntermediateDirectories:YES
                                attributes:nil 
                                     error:nil];
    }
    return fileSavePath;
}
@end
