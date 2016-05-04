//
//  Utility.m
//  DevelopGuide_iOS
//
//  Created by neusoft  on 11-12-1.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#import "Utility.h"

@implementation Utility

+ (NSString *) getResourceFilePath:(NSString *)fileName
{
    NSString *path = nil;
    NSFileManager *fileMgr = [NSFileManager defaultManager];
    path = [[[NSBundle mainBundle] resourcePath] stringByAppendingPathComponent:fileName];
    if ([fileMgr fileExistsAtPath:path]) {
        return path;
    }
    
    return nil;
}

@end
