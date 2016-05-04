//
//  AnnotationListView.h
//  DWViewer
//
//  Created by YAN on 10/19/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#include "LinkAnnotInfo.h"
#import <vector>

@protocol AnnotatinListViewDelegate;
@class PageViewManager;
@interface AnnotationListViewController : UITableViewController<UITableViewDelegate,UITableViewDataSource> 
{	
	id <AnnotatinListViewDelegate> delegate;
	PageViewManager *pageViewMgr;
	
	CGRect			kindLabelRect;
	CGRect			numberLabelRect;
	CGRect			contentLabelRect;
	
	NSMutableDictionary *dictionary;
	int annotationCount;
	int pageIndex;
	std::vector<int> annotationIndex;
	
	// AR NO.17557 の対応 start
	float leftTopX;
	float leftTopY;
	float rightButtomX;
	float rightButtomY;
	// AR NO.17557 の対応 end
}
@property (nonatomic, assign) id <AnnotatinListViewDelegate> delegate; 
@property CGRect kindLabelRect;
@property CGRect numberLabelRect;
@property CGRect contentLabelRect;
@property int pageIndex;
// AR NO.17557 の対応 start
@property float leftTopX;
@property float leftTopY;
@property float rightButtomX;
@property float rightButtomY;
// AR NO.17557 の対応 end

- (id) initWithPageViewManager:(PageViewManager*)mgr;
- (void) loadLinkAnnotationList;

// lixin 20110813 start
// ページ編集機能の追加 
- (void) reloadLinkAnnotationList;
// lixin 20110813 end

- (NSMutableArray*) getAnnotationInfoWithIndex:(int)index;

- (NSString*) wcharToNSString:(const wchar_t *)src; 

- (void) initTableViewCell:(UITableViewCell*)cell withCellIndex:(int)index;

@end

@protocol AnnotatinListViewDelegate <NSObject>
@optional
- (void)didSelectAnnotationInTable:(AnnotationListViewController*)sender;
@end