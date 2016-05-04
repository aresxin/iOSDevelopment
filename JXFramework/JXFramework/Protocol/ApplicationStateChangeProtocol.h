//
//  ApplicationStateChangeProtocol.h
//  JXFramework
//
//  Created by yangjinxin on 15/4/16.
//  Copyright (c) 2015年 yangjinxin. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol ApplicationStateChangeProtocol <NSObject>
@optional
/*
 * pause UI/Network ...
 */
- (void) willResignActive;

/*
 * resotre UI/Network ...
 */
- (void) willEnterForeground;

@end
