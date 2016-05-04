//
//  DWEditFacingPageViewController.h
//  DWViewer
//
//  Created by icd-lixin on 8/13/11.
//  Copyright 2011 Neusoft dalian. All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol DWEditFacingPageViewDelegate;
@interface DWEditFacingPageViewController : UITableViewController {

	id <DWEditFacingPageViewDelegate> delegate;
}
@property (nonatomic, assign) id <DWEditFacingPageViewDelegate> delegate;

@end

@protocol DWEditFacingPageViewDelegate <NSObject>
@optional
- (void) didChoosePageToEditWithButtonIndex:(int)index;
@end