//
//  LocationNotificationViewController.h
//  DevelopGuide_iOS
//
//  Created by xin on 12-3-28.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface LocationNotificationViewController : UIViewController {
    IBOutlet    UITextView  *textView_;
}
- (IBAction) actionAddNotification:(id)sender;
- (IBAction) actionDelNOtification:(id)sender;
- (IBAction) actionPresentNotification:(id)sender;
@end
