//
//  NSThread+BlockAdditions.m
//  JXFramework
//
//  Created by yangjinxin on 15/9/25.
//  Copyright (c) 2015年 yangjinxin. All rights reserved.
//

#import "NSThread+BlockAdditions.h"

@implementation NSThread (BlockAdditions)

- (void)performBlock:(void (^)())block waitUntilDone:(BOOL)wait
{
    [NSThread performSelector:@selector(ng_runBlock:)
                     onThread:self
                   withObject:[block copy]
                waitUntilDone:wait];
}

+ (void)ng_runBlock:(void (^)())block
{
    block();
}


- (void)performBlock:(void (^)())block
{
    if ([[NSThread currentThread] isEqual:self])
        block();
    else
        [self performBlock:block waitUntilDone:NO];
}

+ (void)performBlock:(void (^)())block afterDelay:(CGFloat)aDelay
{
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(aDelay * NSEC_PER_SEC)), dispatch_get_main_queue(), block);
}

+ (void)performBlockInBackground:(void (^)())block{

    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT,0), ^{
        block();
    });
}

+ (void)performBlockOnMainThread:(void (^)())block{
    dispatch_async(dispatch_get_main_queue(), ^{
        block();
    });
}

@end
