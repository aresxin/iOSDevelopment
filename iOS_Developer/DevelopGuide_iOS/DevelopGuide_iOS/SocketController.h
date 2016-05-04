//
//  SocketController.h
//  DevelopGuide_iOS
//
//  Created by neusoft  on 11-12-15.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>


@interface SocketController : UIViewController {
    IBOutlet    UIButton    *sendBtn;
    IBOutlet    UITextView  *messageView;
    IBOutlet    UITextField *ipTextField;
    IBOutlet    UITextField *numtextField;
}

@property   (nonatomic, retain) IBOutlet    UIButton    *sendBtn;
@property   (nonatomic, retain) IBOutlet    UITextView  *messageView;
@property   (nonatomic, retain) IBOutlet    UITextField *ipTextField;
@property   (nonatomic, retain) IBOutlet    UITextField *numtextField;
- (IBAction) sendMessage:(id)sender;

@end
