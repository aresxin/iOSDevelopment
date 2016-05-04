//
//  NSThread+BlockAdditions.h
//  JXFramework
//
//  Created by yangjinxin on 15/9/25.
//  Copyright (c) 2015年 yangjinxin. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <dispatch/dispatch.h>
#import <UIKit/UIKit.h>

@interface NSThread (BlockAdditions)
- (void)performBlock:(void (^)())block;
- (void)performBlock:(void (^)())block waitUntilDone:(BOOL)wait;
+ (void)performBlock:(void (^)())block afterDelay:(CGFloat)aDelay;
+ (void)performBlockInBackground:(void (^)())block;
+ (void)performBlockOnMainThread:(void (^)())block;
@end
