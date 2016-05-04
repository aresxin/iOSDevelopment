//
//  CooperationSettingsViewController.h
//  DWViewer
//
//  Created by liuqw on 11-2-24.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol CooperationSettingsViewDelegate;

@interface CooperationSettingsViewController : UITableViewController {
	id <CooperationSettingsViewDelegate> delegate;
	NSArray *list;
}
@property (nonatomic, assign) id <CooperationSettingsViewDelegate> delegate;

@end

@protocol CooperationSettingsViewDelegate <NSObject>
@optional
- (void)didClickedCooperationMenuButtonIndex:(int)index;
@end