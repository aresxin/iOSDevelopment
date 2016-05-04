//
//  DWScrollView.h
//  DWViewer
//
//  Created by FX Neusoft on 10-10-29.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@class DWPageView;

@interface DWScrollView : UIScrollView
{
	int index;
	DWPageView *page;
	BOOL isActivePage;
	
	float minZoomScale;
	BOOL isFacingPage;
	CGPoint initContentOffset;
    
    long minScale;
    long baseScale;
    long maxScale;
	
	// 2012.02.01(Ver2.1 New) M.Chikyu
	CGRect aferFrame;
	BOOL isPreDraw;
	// 2012.02.01(Ver2.1 New) M.Chikyu
}

@property int index;
@property (nonatomic, assign) DWPageView *page;
@property BOOL isActivePage;
@property float minZoomScale;
@property BOOL isFacingPage;
@property CGPoint initContentOffset;

@property long minScale;
@property long baseScale;
@property long maxScale;

// 2012.02.01(Ver2.1 New) M.Chikyu
@property CGRect afterFrame;
@property BOOL isPreDraw;
// 2012.02.01(Ver2.1 New) M.Chikyu

@end


// 2012.02.01(Ver2.1 New) M.Chikyu

@class DWPageEditView;

@interface DWEditScrollView : UIScrollView
{
	int index;
	DWPageEditView *page;
	BOOL isActivePage;
	
	float minZoomScale;
	BOOL isFacingPage;
	CGPoint initContentOffset;
    
    long minScale;
    long baseScale;
    long maxScale;
}

@property int index;
@property (nonatomic, assign) DWPageEditView *page;
@property BOOL isActivePage;
@property float minZoomScale;
@property BOOL isFacingPage;
@property CGPoint initContentOffset;

@property long minScale;
@property long baseScale;
@property long maxScale;

@end
// 2012.02.01(Ver2.1 New) M.Chikyu
