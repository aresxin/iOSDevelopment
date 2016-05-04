//
//  DWTextSelectedView.m
//  DWViewer
//
//  Created by tongtiexin on 3/12/12.
//  Copyright (c) 2012 Neusoft dalian. All rights reserved.
//

#import "DWSelectGhostView.h"
#import "PageViewManager.h"
#import "DWViewerGUIConst.h"

#define DRAG_POINT_WIDTH 30
#define DRAG_LINE_WIDTH  2

@implementation DWSelectGhostView
@synthesize delegate;

- (id)initWithFrame:(CGRect)frame selectInfo:(DWSelectInfo*)info
{
    self = [super initWithFrame:frame];
    if (self) 
	{
		self.userInteractionEnabled = YES;
		
		// init ghost view color.
		color_ = [[UIColor alloc] initWithRed:0.8 green:0.86 blue:0.93 alpha:0.7];
		
		// init gesture recognizer.
		panRecognizer_  = [[UIPanGestureRecognizer alloc] initWithTarget:self 
																  action:@selector(actionOnPanGestureRecognizer:)];
		[panRecognizer_ setMaximumNumberOfTouches:1];
		panRecognizer_.cancelsTouchesInView = YES;
		panRecognizer_.delegate = self;
		[self addGestureRecognizer:panRecognizer_];
		
		// init select info.
		info_ = [info retain];
		
		// init drag point.
		dragPoint_ = kDragPointNull;
		
		// init drag point.
		NSString *pointImagePath = [[NSBundle mainBundle] pathForResource:_ICON_DRAG_POINT_ ofType:nil];
		UIImage *pointImg = [UIImage imageWithContentsOfFile:pointImagePath];
		
		dragPointLeft_  = [[UIImageView alloc] initWithImage:pointImg];
		[self addSubview:dragPointLeft_];
		
		dragPointRight_  = [[UIImageView alloc] initWithImage:pointImg];
		[self addSubview:dragPointRight_];
		
		// init left drag line.
		NSString *leftImagePath = [[NSBundle mainBundle] pathForResource:_ICON_DRAG_LEFT_ ofType:nil];
		UIImage *leftImg = [UIImage imageWithContentsOfFile:leftImagePath];
		dragLineLeft_  = [[UIImageView alloc] initWithImage:leftImg];
		[self setLeftDragPointPos];
		[self addSubview:dragLineLeft_];
		
		// init right drag line.
		NSString *rightImagePath = [[NSBundle mainBundle] pathForResource:_ICON_DRAG_RIGHT_ ofType:nil];
		UIImage *rightImg = [UIImage imageWithContentsOfFile:rightImagePath];
		dragLineRight_ = [[UIImageView alloc] initWithImage:rightImg];
		[self setRightDragPointPos];
		[self addSubview:dragLineRight_];
		
		// init step value.
		[self initStepValue];
    }
	
    return self;
}

- (BOOL)gestureRecognizer:(UIGestureRecognizer *)gestureRecognizer shouldReceiveTouch:(UITouch *)touch
{
	CGPoint point = [touch locationInView:self];
	CGRect dragPointLeftRect  = dragPointLeft_.frame;
	CGRect dragPointRightRect = dragPointRight_.frame;
	if (CGRectContainsPoint(dragPointLeftRect, point) == YES)
	{
		dragPoint_ = kDragPointLeft;
	}
	else if (CGRectContainsPoint(dragPointRightRect, point) == YES)
	{
		dragPoint_ = kDragPointRight;
	}
	else
	{
		dragPoint_ = kDragPointNull;
	}
	
	if (dragPoint_ == kDragPointNull) 
	{
		return NO;
	}
	
	[delegate ghostViewWillBeginDragging:self];

	return YES;
}

- (void) initStepValue
{
	if ([info_.pixRects count] > 0)
	{
		CGRect rect = [[info_.pixRects objectAtIndex:0] CGRectValue];
		info_.stepX = rect.size.width;
		info_.stepY = rect.size.height;
	}
}

- (void) actionOnPanGestureRecognizer:(UIGestureRecognizer*)gestureRecognizer
{
	CGPoint point = [gestureRecognizer locationInView:self];
	if (gestureRecognizer.state == UIGestureRecognizerStateBegan) 
	{
		// if touch in left drag point.
		CGRect dragPointLeftRect  = dragPointLeft_.frame;
		CGRect dragPointRightRect = dragPointRight_.frame;
		if (CGRectContainsPoint(dragPointLeftRect, point) == YES)
		{
			info_.startPixel = CGPointMake(point.x, point.y + info_.stepY / 2);
		}
		else if (CGRectContainsPoint(dragPointRightRect, point) == YES)
		{
			info_.endPixel = CGPointMake(point.x, point.y - info_.stepY / 2);
		}
		
		if (dragPoint_ != kDragPointNull) 
		{
			UIMenuController *theMenu = [UIMenuController sharedMenuController];
			[theMenu setMenuVisible:NO animated:YES];
		}
	}
	
	if ((gestureRecognizer.state == UIGestureRecognizerStateChanged) && 
		dragPoint_ != kDragPointNull)
	{
		if (dragPoint_ == kDragPointLeft) 
		{
			float start_x = info_.startPixel.x;
			float shift_x = point.x - start_x;
			if (abs(shift_x) >= info_.stepX / 5) 
			{
				start_x = start_x + shift_x;
			}
			
			float start_y = info_.startPixel.y;
			float shift_y = point.y - start_y;
			if (abs(shift_y) >= info_.stepY) 
			{
				start_y = start_y + shift_y;
			}
			
			float end_y   = info_.endPixel.y;
			if (end_y >= start_y) 
			{
				info_.startPixel = CGPointMake(start_x, start_y);
			}
		}
		else if (dragPoint_ == kDragPointRight) 
		{
			float end_x   = info_.endPixel.x;
			float shift_x = point.x - end_x;
			if (abs(shift_x) >= info_.stepX / 5) 
			{
				end_x = end_x + shift_x;
			}
			
			float end_y   = info_.endPixel.y;
			float shift_y = point.y - end_y;
			if (abs(shift_y) >= info_.stepY) 
			{
				end_y = end_y + shift_y;
			}
			
			float start_y = info_.startPixel.y;
			if (end_y >= start_y) 
			{
				info_.endPixel = CGPointMake(end_x, end_y);
			}
		}
		
		float range_x = info_.endPixel.x - info_.startPixel.x;
		float range_y = info_.endPixel.y - info_.startPixel.y;
		if (range_y >= info_.stepY)
		{
			[delegate ghostView:self changeSelectionWithDragPoint:dragPoint_];
		}
		else if (range_x > info_.stepX / 5)
		{
			[delegate ghostView:self changeSelectionWithDragPoint:dragPoint_];
		}
	}
	
	if ((gestureRecognizer.state == UIGestureRecognizerStateEnded || 
		 gestureRecognizer.state == UIGestureRecognizerStateCancelled) &&
		dragPoint_ != kDragPointNull) 
	{
		[delegate ghostViewWillEndedDragging:self];
		
		if ([info_.pixRects count] > 0 && [self becomeFirstResponder]) 
		{
			UIMenuController *theMenu = [UIMenuController sharedMenuController];
			CGRect rect = [[info_.pixRects objectAtIndex:0] CGRectValue];
			[theMenu setTargetRect:rect inView:self];
			[theMenu setMenuVisible:YES animated:YES];
		}
	}
}

- (void) setLeftDragPointPos
{
	if ([info_.pixRects count] > 0)
	{
		CGRect rect = [[info_.pixRects objectAtIndex:0] CGRectValue];
		dragLineLeft_.frame = CGRectMake(rect.origin.x, 
										 rect.origin.y, 
										 DRAG_LINE_WIDTH, 
										 rect.size.height);
		
		dragPointLeft_.frame = CGRectMake(dragLineLeft_.frame.origin.x - (DRAG_POINT_WIDTH / 2),
										  dragLineLeft_.frame.origin.y - DRAG_POINT_WIDTH, 
										  DRAG_POINT_WIDTH, 
										  DRAG_POINT_WIDTH);
	}
}

- (void) setRightDragPointPos
{
	if ([info_.pixRects count] > 0)
	{
		CGRect rect = [[info_.pixRects lastObject] CGRectValue];
		dragLineRight_.frame = CGRectMake(rect.origin.x + rect.size.width,
										  rect.origin.y,
										  DRAG_LINE_WIDTH,
										  rect.size.height);
		dragPointRight_.frame = CGRectMake(dragLineRight_.frame.origin.x - (DRAG_POINT_WIDTH / 2),
										   dragLineRight_.frame.origin.y + dragLineRight_.frame.size.height, 
										   DRAG_POINT_WIDTH, 
										   DRAG_POINT_WIDTH);
	}
}

- (void)drawRect:(CGRect)rect
{
	CGContextRef ctx = UIGraphicsGetCurrentContext();
	CGContextSetFillColorWithColor(ctx, color_.CGColor);
	
	for (int i = 0; i < [info_.pixRects count]; i++) 
	{
		CGRect dRect = [[info_.pixRects objectAtIndex:i] CGRectValue];
		CGContextFillRect(ctx, dRect);
	}	
}

- (BOOL)canBecomeFirstResponder
{
	return YES;
}

- (void) dealloc
{
	[panRecognizer_ release];
	
	[dragPointLeft_ release];
	[dragLineLeft_ release];
	
	[dragPointRight_ release];
	[dragLineRight_ release];
	
	[info_ release];
	[color_ release];
	
	[super dealloc];
}

@end

// xujj 2012.04.02 start
// 検索機能の追加
@implementation DWSearchGhostView

- (id)initWithFrame:(CGRect)frame searchInfo:(DWSearchInfo *)info
{
    self = [super initWithFrame:frame];
    if (self)
	{
        self.backgroundColor = [UIColor clearColor];
		searchInfo_ = [info retain];
    }
    return self;
}

- (void)drawRect:(CGRect)rect
{
	CGContextRef ctx = UIGraphicsGetCurrentContext();
	
	UIColor *color = [[UIColor alloc] initWithRed:0 green:1 blue:0 alpha:0.3];
	CGContextSetFillColorWithColor(ctx, color.CGColor);
	[color release];
	
	for (int i = 0; i < [searchInfo_.pixSearchRects count]; i++) 
	{
		CGRect dRect = [[searchInfo_.pixSearchRects objectAtIndex:i] CGRectValue];
		CGContextFillRect(ctx, dRect);
	}	
}

- (void) dealloc
{
	[searchInfo_ release];
	
	[super dealloc];
}

@end
// xujj 2012.04.02 end
