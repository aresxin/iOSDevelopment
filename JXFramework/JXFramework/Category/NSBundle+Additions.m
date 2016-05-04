//
//  NSBundle+Additions.m
//  JXFramework
//
//  Created by yangjinxin on 15/9/25.
//  Copyright (c) 2015年 yangjinxin. All rights reserved.
//

#import "NSBundle+Additions.h"
#import <sys/utsname.h>


@implementation NSBundle (Additions)
+ (NSString *)appName
{
    return [[NSBundle mainBundle] objectForInfoDictionaryKey:@"CFBundleDisplayName"];
}


+ (NSString *)appVersion
{
    return [[NSBundle mainBundle] objectForInfoDictionaryKey:@"CFBundleShortVersionString"];
}

+ (NSString *)appBuildNumber
{
    return [[NSBundle mainBundle] objectForInfoDictionaryKey:@"CFBundleVersion"];
}

+ (NSString *)appVersionForHeader
{
    NSString *sAppVersion   = [NSBundle appVersion];
    NSArray  *sVersionArray = [sAppVersion componentsSeparatedByString:@"."];
    NSMutableString *sMutableString = [[NSMutableString alloc] initWithString:@"I"];
    
    [sVersionArray enumerateObjectsUsingBlock:^(id obj, NSUInteger idx, BOOL *stop) {
        if (idx < 2)
        {
            [sMutableString appendString:obj];
            [sMutableString appendString:@"."];
        }
        else if (idx == 2)
        {
            [sMutableString appendString:obj];
        }
    }];
    
    return sMutableString;
}

+ (NSString *)deviceInfo
{
    struct utsname systemInfo;
    uname(&systemInfo);
    
    return [NSString stringWithCString:systemInfo.machine
                              encoding:NSUTF8StringEncoding];
}

+ (NSString *)osVersion
{
    return [NSString stringWithFormat:@"%@ %@", [[UIDevice currentDevice] systemName], [[UIDevice currentDevice] systemVersion]];;
}



@end
