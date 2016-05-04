//
//  FileSortSettingsViewController.h
//  DWViewer
//
//  Created by liuqw on 11-2-18.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol FileSortSettingsViewDelegate;

@interface FileSortSettingsViewController : UITableViewController {
	int sortItemIndex;
	int sortModeIndex;
}
@property (nonatomic, assign) id <FileSortSettingsViewDelegate> delegate;
@property int sortItemIndex;
@property int sortModeIndex;

@end

@protocol FileSortSettingsViewDelegate <NSObject>
@optional
- (void)didFileSortCheckValueChanged:(FileSortSettingsViewController *)sender;
@end