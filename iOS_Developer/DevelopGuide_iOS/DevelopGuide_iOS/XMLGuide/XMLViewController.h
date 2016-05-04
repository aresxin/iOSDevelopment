//
//  XMLViewController.h
//  DevelopGuide_iOS
//
//  Created by neusoft  on 11-12-9.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>


@interface XMLViewController : UIViewController {
    IBOutlet    UIButton    *parseButton;
    IBOutlet    UIButton    *packageButton;
    IBOutlet    UITextView  *xmlStrView;
}

@property   (nonatomic, retain) IBOutlet    UIButton    *parseButton;
@property   (nonatomic, retain) IBOutlet    UIButton    *packageButton;
@property   (nonatomic, retain) IBOutlet    UITextView    *xmlStrView;

- (IBAction) actionParserButton:(id)sender;
- (IBAction) actionPackageButton:(id)sender;
@end
