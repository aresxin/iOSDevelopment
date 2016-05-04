//
//  DevelopGuide_iOSAppDelegate.h
//  DevelopGuide_iOS
//
//  Created by neusoft  on 11-12-9.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface DevelopGuide_iOSAppDelegate : NSObject <UIApplicationDelegate> {

}

@property (nonatomic, retain) IBOutlet UIWindow *window;

@property (nonatomic, retain) IBOutlet UINavigationController *navigationController;

@end
