//
//  XdwListinXbdViewController.h
//  DWViewer
//
//  Created by icd-lixin on 6/8/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "PageViewManager.h"
#include "XdwFileInfo.h"
@protocol XdwListViewDelegate;
@interface XdwListinXbdViewController : UITableViewController {
	id <XdwListViewDelegate> delegate;
	
	PageViewManager*    pageViewMgr;
    XdwFileInfo*        fileInfo;
	int                 xdwDocCount;
	CGRect              nameLabelRect;
	CGRect              pageLabelRect;
    
    // lixin 20110626 DW_iPhoneEnhance_12 start
	// AR.17872 の対応 
	int                 selectDocIndex;
	// lixin 20110626 DW_iPhoneEnhance_12 end
}
@property (nonatomic, assign) id <XdwListViewDelegate> delegate; 
@property (nonatomic, assign) CGRect nameLabelRect;
@property (nonatomic, assign) CGRect pageLabelRect;
// lixin 20110626 DW_iPhoneEnhance_12 start
// AR.17872 の対応 
@property int selectDocIndex;
// lixin 20110626 DW_iPhoneEnhance_12 end

- (id) initWithPageViewManager:(PageViewManager*)mgr;

// lixin 20110830 DW_iPhoneViewer_20の追加 start
- (void) reloadDataWithPageViewManager:(PageViewManager*)mgr;
// lixin 20110830 end

@end

@protocol XdwListViewDelegate <NSObject>
@optional
- (void)didSelectXdwDocInTable:(int)xdwPageIndex;
@end