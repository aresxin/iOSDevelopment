//
//  AssetsLibrary.h
//  DevelopGuide_iOS
//
//  Created by lu matthew on 12-7-5.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AssetsLibrary/AssetsLibrary.h>
@interface AssetsLibrary : UIViewController {
    AssetsLibrary *_assetsLib;
    IBOutlet UITextView *_textView;
}
- (IBAction)showAssetsLibray:(id)sender;
@end
