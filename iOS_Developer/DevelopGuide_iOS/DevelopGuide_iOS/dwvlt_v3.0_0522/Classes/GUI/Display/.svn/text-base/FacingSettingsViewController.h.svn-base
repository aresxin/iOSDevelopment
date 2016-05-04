//
//  FacingSettingsViewController.h
//  DWViewer
//
//  Created by sun on 10-10-22.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol FacingSettingsViewDelegate;

@interface FacingSettingsViewController : UITableViewController {
	id <FacingSettingsViewDelegate> delegate;
	NSArray *list;
	NSArray *listIconName;//save the icon file name for list add by lixin 20011201
	int index;
}
@property (nonatomic, assign) id <FacingSettingsViewDelegate> delegate;
@property int index;

@end

@protocol FacingSettingsViewDelegate <NSObject>
@optional
- (void)didFacingSettingsChanged:(int)index;
@end