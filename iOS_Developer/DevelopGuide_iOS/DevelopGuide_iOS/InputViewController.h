//
//  InputViewController.h
//  Demo
//
//  Created by 张玺 on 12-11-25.
//  Copyright (c) 2012年 张玺. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "BlockUI.h"
@interface InputViewController : UIViewController
{
    IBOutlet UITextField *text;
}

- (IBAction)confirm:(id)sender;

@end
