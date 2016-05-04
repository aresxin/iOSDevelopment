//
//  NSBundle+Additions.h
//  JXFramework
//
//  Created by yangjinxin on 15/9/25.
//  Copyright (c) 2015年 yangjinxin. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface NSBundle (Additions)
+ (NSString *)appName;
+ (NSString *)appVersion;
+ (NSString *)appBuildNumber;
+ (NSString *)deviceInfo;
+ (NSString *)osVersion;
+ (NSString *)appVersionForHeader;
@end
