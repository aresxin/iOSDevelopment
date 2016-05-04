//
//  BaseViewController.m
//  JXFramework
//
//  Created by yangjinxin on 15/4/16.
//  Copyright (c) 2015年 yangjinxin. All rights reserved.
//

#import "BaseViewController.h"

@implementation BaseViewController


- (void)viewDidLoad
{
    [super viewDidLoad];
    [self addApplicationStateObserver];
}

- (void) viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
}

- (void) viewWillDisappear:(BOOL)animated
{
    [super viewWillDisappear:animated];
}

- (void)dealloc
{
    [self removeApplicationStateObserver];
}

#pragma mark -
#pragma mark application state change
- (void) addApplicationStateObserver
{
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(willResignActive) name:UIApplicationWillResignActiveNotification object:nil];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(willEnterForeground) name:UIApplicationDidBecomeActiveNotification object:nil];

}

- (void) removeApplicationStateObserver
{
    [[NSNotificationCenter defaultCenter] removeObserver:self name:UIApplicationWillResignActiveNotification object:nil];
    [[NSNotificationCenter defaultCenter] removeObserver:self name:UIApplicationDidBecomeActiveNotification object:nil];
}

- (void) willResignActive
{
    
}

- (void) willEnterForeground
{
    
}

@end
