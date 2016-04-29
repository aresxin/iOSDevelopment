//
//  RWAppDelegate.m
//  DeviantArtBrowser
//
//  Created by Joshua Greene on 4/1/14.
//  Copyright (c) 2014 Razeware, LLC. All rights reserved.
//

#import "RWAppDelegate.h"
#import <AFNetworking/AFNetworkActivityIndicatorManager.h>
#import <AFNetworkActivityLogger/AFNetworkActivityLogger.h>

@implementation RWAppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
  [[AFNetworkActivityLogger sharedLogger] startLogging];
  
  [[AFNetworkActivityIndicatorManager sharedManager] setEnabled:YES];
  
  return YES;
}

@end
