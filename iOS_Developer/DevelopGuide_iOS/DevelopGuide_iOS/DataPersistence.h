//
//  DataPersistence.h
//  DevelopGuide_iOS
//
//  Created by xin on 12-3-27.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface DataPersistence : UIViewController {
    IBOutlet    UITextView  *textView_;
}
- (IBAction)actionArchiver:(id)sender;
- (IBAction)actionUnArchiver:(id)sender;
@end
