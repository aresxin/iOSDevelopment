//
//  JSONParseController.h
//  DevelopGuide_iOS
//
//  Created by neusoft  on 11-12-20.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface JSONParseController : UIViewController {
    UITextView  *textView_;
}
@property (nonatomic, retain)   IBOutlet    UITextView  *textView_;
- (IBAction) parserJSON:(id)sender;
- (IBAction) packageJSON:(id)sender;
@end

@interface People : NSObject {
    NSString    *_name;
    NSString    *_info;
}
@property (nonatomic, copy) NSString *name;
@property (nonatomic, copy) NSString *info;
@end