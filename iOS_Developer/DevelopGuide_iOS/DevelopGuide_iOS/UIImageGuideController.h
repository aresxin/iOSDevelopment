//
//  UIImageGuideController.h
//  DevelopGuide_iOS
//
//  Created by neusoft  on 11-12-12.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@class DrawImageView;

@interface UIImageGuideController : UIViewController <UIActionSheetDelegate>{
    //IBOutlet    UITableView     *tableView_;
    //IBOutlet    UIImageView     *imageView_;
    //NSMutableArray      *functionList;
    DrawImageView       *drawImgView;
}
//@property   (nonatomic, retain) UITableView *tableView_;
//@property   (nonatomic, retain) UIImageView *imageView_;
- (void) initToolBar;
@end
