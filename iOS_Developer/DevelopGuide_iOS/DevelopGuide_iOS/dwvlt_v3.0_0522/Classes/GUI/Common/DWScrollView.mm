//
//  DWScrollView.m
//  DWViewer
//
//  Created by FX Neusoft on 10-10-29.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "DWScrollView.h"
#import "DWPageView.h"


@implementation DWScrollView
@synthesize index;
@synthesize page;
@synthesize isActivePage;
@synthesize minZoomScale;
@synthesize isFacingPage;
@synthesize initContentOffset;

@synthesize minScale;
@synthesize baseScale;
@synthesize maxScale;

// 2012.02.01(Ver2.1 New) M.Chikyu
@synthesize afterFrame;
@synthesize isPreDraw;
// 2012.02.01(Ver2.1 New) M.Chikyu

- (id)initWithFrame:(CGRect)frame
{
    if ((self = [super initWithFrame:frame]))
	{
        // Initialization code
		index = 0;
		page = nil;
		isActivePage = NO;
		
		minZoomScale = 1.0;
		isFacingPage = NO;
		
		initContentOffset = CGPointMake(0.0, 0.0);
        
        minScale = 1;
        baseScale = 100;
        maxScale = 200;
		
		// 2012.02.01(Ver2.1 New) M.Chikyu
		isPreDraw = NO;
		// 2012.02.01(Ver2.1 New) M.Chikyu
    }
    return self;
}

- (void)dealloc
{
    [super dealloc];
}

@end


// 2012.02.01(Ver2.1 New) M.Chikyu

@implementation DWEditScrollView

@synthesize index;
@synthesize page;
@synthesize isActivePage;
@synthesize minZoomScale;
@synthesize isFacingPage;
@synthesize initContentOffset;

@synthesize minScale;
@synthesize baseScale;
@synthesize maxScale;

- (id)initWithFrame:(CGRect)frame
{
    if ((self = [super initWithFrame:frame]))
	{
        // Initialization code
		index = 0;
		page = nil;
		isActivePage = NO;
		
		minZoomScale = 1.0;
		isFacingPage = NO;
		
		initContentOffset = CGPointMake(0.0, 0.0);
        
        minScale = 1;
        baseScale = 100;
        maxScale = 200;
    }
    return self;
}

- (void)dealloc
{
    [super dealloc];
}

@end
// 2012.02.01(Ver2.1 New) M.Chikyu
