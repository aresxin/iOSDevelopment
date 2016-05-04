//
//  LocationNotificationViewController.m
//  DevelopGuide_iOS
//
//  Created by xin on 12-3-28.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//
/*
 * 本地通知代码示例
 * 
 */

#import "LocationNotificationViewController.h"

@implementation LocationNotificationViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)didReceiveMemoryWarning
{
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

#pragma mark - View lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

- (IBAction) actionAddNotification:(id)sender
{
    UILocalNotification *notification=[[UILocalNotification alloc] init];
    if (notification!=nil) 
    {
        
        NSDate *now=[NSDate new];
        
        //notification.fireDate=
        //[now addTimeInterval:perror];
        notification.fireDate = [now dateByAddingTimeInterval:5];
        //NSLog(@"%d",period);
        notification.timeZone=[NSTimeZone defaultTimeZone];
        notification.soundName = UILocalNotificationDefaultSoundName;
        notification.alertBody=@"TIME！";
        notification.applicationIconBadgeNumber = 10;
        notification.alertBody = [NSString stringWithFormat:@"时间到了!"];
        notification.alertAction = @"notification alert action";
        NSDictionary* info = [NSDictionary dictionaryWithObject:@"闹钟通知" forKey:@"noti"];
        notification.userInfo = info;
        
        [[UIApplication sharedApplication] scheduleLocalNotification:notification];      
        
    }
    
    [notification release];

}

- (IBAction) actionDelNOtification:(id)sender
{
    for(UILocalNotification *aNotif in [[UIApplication sharedApplication] scheduledLocalNotifications]) 
    {   
        if ([[aNotif.userInfo objectForKey:@"noti"] isEqualToString:@"闹钟通知"]) {
            [[UIApplication sharedApplication] cancelLocalNotification:aNotif];
            break;
        }
        
    } 
    
}

- (IBAction) actionPresentNotification:(id)sender
{
    UILocalNotification *notification=[[UILocalNotification alloc] init];
    if (notification!=nil) 
    {
        
        NSDate *now=[NSDate new];
        
        //notification.fireDate=[now addTimeInterval:period];
        notification.fireDate = now;
        //NSLog(@"%d",period);
        notification.timeZone=[NSTimeZone defaultTimeZone];
        
        
        notification.soundName   = UILocalNotificationDefaultSoundName;
        notification.applicationIconBadgeNumber = 1;
        notification.alertBody   = [NSString stringWithFormat:@"时间到了!"];
        notification.alertAction = @"notification alert action";
        NSDictionary* info = [NSDictionary dictionaryWithObject:@"闹钟通知" forKey:@"noti"];
        notification.userInfo = info;
        
        [[UIApplication sharedApplication] presentLocalNotificationNow:notification];      
        
    } 
    
    [notification release];

}

@end
