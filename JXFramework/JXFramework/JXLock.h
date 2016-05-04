//
//  JXLock.h
//  JXFramework
//
//  Created by yangjinxin on 15/9/8.
//  Copyright (c) 2015年 yangjinxin. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface JXLock : NSObject


void runOnMainQueue(void (^block)(void));

void runSyncOnLockQueue(void (^block)(void));

void runAsyncOnLockQueue(void (^block)(void));

@end
