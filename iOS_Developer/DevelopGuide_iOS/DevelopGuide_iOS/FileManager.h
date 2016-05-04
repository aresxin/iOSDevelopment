//
//  FileManager.h
//  DevelopGuide_iOS
//
//  Created by neusoft  on 12-3-8.
//  Copyright 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface FileManager : NSObject {
    
}
+ (FileManager *) shareFileManager;
- (void) setReadOnlyFile:(NSString *)filePath;
- (void) getFileAttribute:(NSString *)filePath;
- (void) writeDataToFile;
+ (NSString *) createFilePath:(NSString *)filePath;
@end
