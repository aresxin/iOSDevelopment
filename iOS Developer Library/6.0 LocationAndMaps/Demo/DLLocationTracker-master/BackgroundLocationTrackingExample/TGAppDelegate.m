//
//  TGAppDelegate.m
//  BackgroundLocationTrackingExample
//
//  Created by Denis Lebedev on 12.08.12.
//  Copyright (c) 2012 Denis Lebedev. All rights reserved.
//

#import "TGAppDelegate.h"
#import "MainViewController.h"

#import "DLLocationTracker.h"

@interface TGAppDelegate ()

@property (nonatomic, strong) DLLocationTracker *locationTracker;

@end

@implementation TGAppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    
    
    if ([UIApplication instancesRespondToSelector:@selector(registerUserNotificationSettings:)]){
        [application registerUserNotificationSettings:[UIUserNotificationSettings settingsForTypes:UIUserNotificationTypeAlert|UIUserNotificationTypeBadge|UIUserNotificationTypeSound categories:nil]];
    }
    
 	if ([launchOptions objectForKey:UIApplicationLaunchOptionsLocationKey]) {
        self.locationTracker = [[DLLocationTracker alloc] init];
        [self.locationTracker setLocationUpdatedInBackground:^(CLLocation *location) {
            
            UILocalNotification *notification = [[UILocalNotification alloc] init];
            notification.fireDate  = [NSDate dateWithTimeIntervalSinceNow:5];
            notification.alertBody = [NSString stringWithFormat:@"LaunchOptionsLocationKey:\n %@", location];
            notification.soundName = UILocalNotificationDefaultSoundName;
            [notification setTimeZone:[NSTimeZone defaultTimeZone]];
            [[UIApplication sharedApplication] scheduleLocalNotification:notification];
            
            
        }];
        
        [self.locationTracker startUpdatingLocation];
    }
    
    
    self.window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]];
    [self.window makeKeyAndVisible];
    
    MainViewController *vc = [[MainViewController alloc] init];
    self.window.rootViewController = vc;
    return YES;
}



@end
