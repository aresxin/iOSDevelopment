//
//  DevelopGuide_iOSAppDelegate.m
//  DevelopGuide_iOS
//
//  Created by neusoft  on 11-12-9.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#import "DevelopGuide_iOSAppDelegate.h"
#import "NSObject+PropertyListing.h"
#import "TestPropertyListing.h"

@implementation DevelopGuide_iOSAppDelegate


@synthesize window=_window;

@synthesize navigationController=_navigationController;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    // Override point for customization after application launch.
    // Add the navigation controller's view to the window and display.
    self.window.rootViewController = self.navigationController;
    [self.window makeKeyAndVisible];
    
    // 接到本地通知
    UILocalNotification *localNotif = [launchOptions objectForKey:UIApplicationLaunchOptionsLocalNotificationKey];
    if (localNotif) 
    {
        NSLog(@"Recieved Notification %@",localNotif);
        NSDictionary* infoDic = localNotif.userInfo;
        NSLog(@"userInfo description=%@",[infoDic description]);
        NSString* codeStr = [infoDic objectForKey:@"noti"];
        NSLog(@"userInfo description=%@",codeStr);
    }
   
    
    
    
    // test NSObject propertylisting start
    TestPropertyListing *test = [[TestPropertyListing alloc] init];
    NSMutableDictionary *proDic = [[test properties_aps] retain];
    NSLog(@"prodic is %@",proDic);
    
    for (int i = 0; i < [[proDic allKeys] count]; i++)
    {
        NSString *key = [[proDic allKeys] objectAtIndex:i];
        NSLog(@"key is %@",key);
        
        [proDic setObject:[NSString stringWithFormat:@"%d",i] forKey:key];
    }
    
    [test getPropertiesFrom:proDic];
    NSLog(@"test is %@",test);
    NSLog(@"test is %@",test.name);
    NSLog(@"test is %@",test.age);
    NSLog(@"test is %@",test.sex);
    // test NSObject propertylisting end
    
    
    TestPropertyListing *test1 = [[TestPropertyListing alloc] init];
    //TestPropertyListing *test3 = [test1 copy];
    
    test1.name = @"new func";
    NSString *aa = (NSString *)[test1 getPropertyValue:@"name"];
    //test3.name = @"copy test3";
    
    NSMutableDictionary *dic = [NSMutableDictionary dictionaryWithObject:@"age is "
                                                                  forKey:@"age"];
    [test1 setPropertyValue:dic];
    
    
//    NSMutableDictionary *dic3 = [NSMutableDictionary dictionaryWithObject:@"age is 3"
//                                                                  forKey:@"age3"];
    //[test3 setPropertyValue:dic3];

    
    NSLog(@"test is %@",aa);
    NSLog(@"test is %@",test1.name);
    NSLog(@"test is %@",test1.age);
    NSLog(@"test is %@",test1.sex);
    
//    NSLog(@"test is %@",test3.name);
//    NSLog(@"test is %@",test3.age);
//    NSLog(@"test is %@",test3.sex);

     return YES;
}

// 当应用程序正在运行时接到本地通知
- (void)application:(UIApplication *)application didReceiveLocalNotification:(UILocalNotification *)notification 
{
    NSLog(@"not is %@",notification);
}

- (void)applicationWillResignActive:(UIApplication *)application
{
    /*
     Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
     Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
     */
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
    /*
     Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
     If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
     */
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
    /*
     Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
     */
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    /*
     Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
     */
}

- (void)applicationWillTerminate:(UIApplication *)application
{
    /*
     Called when the application is about to terminate.
     Save data if appropriate.
     See also applicationDidEnterBackground:.
     */
}

+ (DevelopGuide_iOSAppDelegate *) shareAppDelegate
{
    return (DevelopGuide_iOSAppDelegate *)[[UIApplication sharedApplication] delegate];
}

- (void)dealloc
{
    [_window release];
    [_navigationController release];
    [super dealloc];
}

@end
