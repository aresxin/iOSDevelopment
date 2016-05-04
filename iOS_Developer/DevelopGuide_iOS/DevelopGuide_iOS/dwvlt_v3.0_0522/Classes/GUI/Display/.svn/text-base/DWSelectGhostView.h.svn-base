//
//  DWTextSelectedView.h
//  DWViewer
//
//  Created by tongtiexin on 3/12/12.
//  Copyright (c) 2012 Neusoft dalian. All rights reserved.
//

#import <UIKit/UIKit.h>

enum DRAG_POINT 
{
	kDragPointLeft = 0,
	kDragPointRight,
	kDragPointNull
};

@class DWSelectGhostView;
@class DWSelectInfo;

// xujj 2012.04.02 start
// 検索機能の追加
@class DWSearchInfo;
// xujj 2012.04.02 end


@protocol DWSelectGhostViewDelegate <NSObject>

@optional
- (void)ghostViewWillBeginDragging:(DWSelectGhostView*)ghostView;
- (void)ghostViewWillEndedDragging:(DWSelectGhostView*)ghostView;
- (void)ghostView:(DWSelectGhostView*)ghostView changeSelectionWithDragPoint:(DRAG_POINT)point;
@end

@interface DWSelectGhostView: UIView <UIGestureRecognizerDelegate>
{
	UIPanGestureRecognizer* panRecognizer_;
	
	UIImageView*			dragPointLeft_;
	UIImageView*			dragLineLeft_;
	
	UIImageView*			dragPointRight_;
	UIImageView*			dragLineRight_;
	
	DRAG_POINT				dragPoint_;
	
	DWSelectInfo*			info_;
	UIColor*				color_;
}

@property (nonatomic, assign) id<DWSelectGhostViewDelegate> delegate;

- (id) initWithFrame:(CGRect)frame selectInfo:(DWSelectInfo*)info;
- (void) actionOnPanGestureRecognizer:(UIGestureRecognizer*)gestureRecognizer;
- (void) initStepValue;
- (void) setLeftDragPointPos;
- (void) setRightDragPointPos;
@end

// xujj 2012.04.02 start
// 検索機能の追加
@interface DWSearchGhostView : UIView
{
	DWSearchInfo*			searchInfo_;
}

- (id)initWithFrame:(CGRect)frame searchInfo:(DWSearchInfo*)info;
@end
// xujj 2012.04.02 end

