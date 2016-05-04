//
//  DWAnnGhostView.m
//  DWViewer
//
//  Created by liuqw on 11-8-9.
//  Copyright 2011 Neusoft dalian. All rights reserved.
//

#import "Utility.h"
#import "DWAnnGhostView.h"

@implementation DWAnnShadowGhostView

@synthesize delegate;
@synthesize lineColor;
@synthesize lineWidth;


- (id) initWithFrame:(CGRect)frame 
       withPageFrame:(CGRect)pageRect 
         withIsFixed:(BOOL)fixed
{
	self = [super initWithFrame:frame];

	if (self != nil)
	{
		self.backgroundColor		= [UIColor clearColor];
		self.userInteractionEnabled	= true;

		annoSrcRect		= frame;
		pageViewRect	= pageRect;
		isNeedMove		= YES;
		isFixed			= fixed;
	}

    return self;
}


- (void) touchesBegan:(NSSet *) touches
			withEvent:(UIEvent *) event
{
    if (isFixed == YES)
	{
		return;
	}

	NSInteger numThouchs = [[event allTouches] count];
	if (numThouchs == 1)
	{
		srcPosition = [[touches anyObject] locationInView:self];
	}
}


- (void) touchesMoved:(NSSet *) touches
			withEvent:(UIEvent *) event
{	
    if (isFixed == YES)
	{
		return;
	}

	NSInteger numThouchs = [[event allTouches] count];
	if (numThouchs == 1)
	{
		dstPosition = [[touches anyObject] locationInView:[self superview]];
		
		if (!CGPointEqualToPoint(annoSrcRect.origin, dstPosition))
		{
			self.backgroundColor	= [UIColor blackColor];
			self.alpha				= 0.5f;
		}
        
        // liuqw 20120203 start
        // AR NO.18881の対応
        
        /*
		self.center = CGPointMake(dstPosition.x, dstPosition.y);
         */
        
        self.frame = CGRectMake(dstPosition.x - srcPosition.x, 
                                dstPosition.y - srcPosition.y, 
                                annoSrcRect.size.width, 
                                annoSrcRect.size.height);
        
        // liuqw 20120203 end
        
		CGRect dstRect = self.frame;

		if (CGRectIntersectsRect(pageViewRect, dstRect) == NO)
		{
			self.backgroundColor = [UIColor clearColor];
			isNeedMove = NO;

			[self setFrame:annoSrcRect];
		}
		else
		{
			self.backgroundColor = [UIColor blackColor];
			isNeedMove = YES;
		}				
	}
	else
	{
		float offsetX = self.frame.origin.x - annoSrcRect.origin.x;
		float offsetY = self.frame.origin.y - annoSrcRect.origin.y;
		
		if (CGRectIntersectsRect(pageViewRect, self.frame) == YES)
		{
			CGSize moveOffset = CGSizeMake(offsetX, offsetY);
			[delegate didFinishedMoveAnnotationWithMovedOffset:moveOffset];

			annoSrcRect	= self.frame;
			isNeedMove	= NO;
		}
	}

}


- (void) touchesEnded:(NSSet *) touches
			withEvent:(UIEvent *) event
{
    if (isFixed == YES)
	{
		return;
	}

	NSInteger numThouchs = [[event allTouches] count];
	if (numThouchs == 1)
	{
		if (isNeedMove == YES)
		{
			self.alpha = 0.0f;
		}
		else
		{
			self.backgroundColor = [UIColor clearColor];
		}
        
		float offsetX = self.frame.origin.x - annoSrcRect.origin.x;
		float offsetY = self.frame.origin.y - annoSrcRect.origin.y;
		
		if (CGRectIntersectsRect(pageViewRect, self.frame) == YES )
		{
			if (isNeedMove == YES)
			{
				CGSize moveOffset = CGSizeMake(offsetX, offsetY);
				[delegate didFinishedMoveAnnotationWithMovedOffset:moveOffset];

                annoSrcRect = self.frame;
			}
		}	
	}
}


- (void)drawRect:(CGRect)rect 
{
	//TODO:Draw annotation
}

- (void)dealloc
{
    [super dealloc];
}

@end



// ---------------------------------------

@implementation DWAnnBorderGhostView

@synthesize dashLineColor;

- (id)initWithFrame:(CGRect)frame
		borderColor:(UIColor *)bcolor
		  zoomScale:(CGFloat)zoomScale
{
	CGRect adjustFrame = CGRectMake(frame.origin.x		- 4.0 / zoomScale,
									frame.origin.y		- 4.0 / zoomScale,
									frame.size.width	+ 5.0 / zoomScale,
									frame.size.height	+ 5.0 / zoomScale);
    self = [super initWithFrame:adjustFrame];

    if (self != nil)
	{
		if (bcolor != nil)
		{
			dashLineColor = bcolor;
		}
		else
		{
			dashLineColor = [UIColor blackColor];
		}

		annotationFrame = CGRectMake(4.0 / zoomScale,
									 4.0 / zoomScale,
									 frame.size.width  - 2.0 / zoomScale,
									 frame.size.height - 2.0 / zoomScale);

		[self setBackgroundColor:[UIColor clearColor]];

		m_zoomScale = zoomScale;

		if ([self respondsToSelector:@selector(contentScaleFactor)])
		{
			m_bmpScale = self.contentScaleFactor * m_zoomScale;
		}
		else
		{
			m_bmpScale = m_zoomScale;
		}
    }
	
    return self;
}


- (void)drawRect:(CGRect)rect 
{
	CGContextRef ctx = UIGraphicsGetCurrentContext();

	CGContextAddRect(ctx, annotationFrame);
	CGContextSetStrokeColorWithColor(ctx, dashLineColor.CGColor);

	CGFloat floats[]
	= {10.0 / m_zoomScale, 5.0 / m_zoomScale};

	CGContextSetLineDash(ctx, 1.0, floats, 2);

	CGFloat lineWidth = 2 / m_zoomScale;

	CGContextSetLineWidth(ctx, lineWidth);
	CGContextStrokePath(ctx);
}


- (void)layoutSubviews
{
	if ([self respondsToSelector:@selector(contentScaleFactor)])
	{
		self.contentScaleFactor = m_bmpScale;
	}
}


- (void)dealloc
{
	[dashLineColor release];
    [super dealloc];
}


@end

// --------------------------------



@implementation DWFreeHandAnnGhostView

@synthesize lineWidth;
@synthesize lineUIColor;

// wangpp 2012.2.29 start
// freehand transparent
@synthesize transparent;
// wangpp 2012.2.29 end

@synthesize delegate;
@synthesize arrayStrokes;


- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];

    if (self != nil)
	{
        self.backgroundColor		= [UIColor clearColor];
        self.userInteractionEnabled	= true;

		lineUIColor	= [UIColor clearColor];
		lineWidth	= 0;

		
		self.arrayStrokes = [[[NSMutableArray alloc] init] autorelease];
		isTouchBegin = NO;
    }

    return self;
}


- (void) touchesBegan:(NSSet *) touches
			withEvent:(UIEvent *) event
{
	NSInteger numThouchs = [[event allTouches] count];
	if (numThouchs == 1)
	{
		isTouchBegin = YES;

		NSMutableArray*			arrayPointsInStroke	= [NSMutableArray array];
		NSMutableDictionary*	dictStroke			= [NSMutableDictionary dictionary];

		[dictStroke setObject:arrayPointsInStroke
					   forKey:_KEY_POINTS_];

		[dictStroke setObject:lineUIColor
					   forKey:_KEY_COLOR_];

		// 2012.01.30 M.Chikyu start.
		/*
		[dictStroke setObject:[NSNumber numberWithLong:lineWidth]
					   forKey:_KEY_WIDTH_];
		 */

		[dictStroke setObject:[NSNumber numberWithFloat:lineWidth]
					   forKey:_KEY_WIDTH_];
		// 2012.01.30 M.Chikyu start.
		
		// wangpp 2012.2.29 start
		// freehand transparent
		[dictStroke setObject:[NSNumber numberWithBool:transparent] 
					   forKey:_KEY_TRANS_];
		// wangpp 2012.2.29 end

		CGPoint point = [[touches anyObject] locationInView:self];
		[arrayPointsInStroke addObject:[NSValue valueWithCGPoint:point]];
		
		[self.arrayStrokes addObject:dictStroke];
	}
}


- (void) touchesMoved:(NSSet *) touches withEvent:(UIEvent *) event
{
	NSInteger numThouchs = [[event allTouches] count];

	if (numThouchs == 1)
	{
		CGPoint point		= [[touches anyObject] locationInView:self];
		CGPoint prevPoint	= [[touches anyObject] previousLocationInView:self];

		if (isTouchBegin == YES)
		{
			// add point to stroke
			NSMutableArray *arrayPointsInStroke = [[self.arrayStrokes lastObject] 
												   objectForKey:_KEY_POINTS_];
            
            [arrayPointsInStroke addObject:[NSValue valueWithCGPoint:point]];
		}
		else
		{
			isTouchBegin = YES;

			NSMutableArray*			arrayPointsInStroke	= [NSMutableArray array];
			NSMutableDictionary*	dictStroke			= [NSMutableDictionary dictionary];

			[dictStroke setObject:arrayPointsInStroke
						   forKey:_KEY_POINTS_];

			[dictStroke setObject:lineUIColor
						   forKey:_KEY_COLOR_];

			// 2012.01.30 M.Chikyu start.
			/*
			[dictStroke setObject:[NSNumber numberWithLong:lineWidth]
						   forKey:_KEY_WIDTH_];
			 */

			[dictStroke setObject:[NSNumber numberWithFloat:lineWidth]
						   forKey:_KEY_WIDTH_];
			// 2012.01.30 M.Chikyu start.

			// wangpp 2012.2.29 start
			// freehand transparent
			[dictStroke setObject:[NSNumber numberWithBool:transparent] 
						   forKey:_KEY_TRANS_];
			// wangpp 2012.2.29 end
			
			[arrayPointsInStroke addObject:[NSValue valueWithCGPoint:point]];

			[self.arrayStrokes addObject:dictStroke];
		}

		[self setNeedsDisplay];
	}
	
	if (numThouchs == 2 && isTouchBegin == YES)
	{
		NSMutableArray *points = [[self.arrayStrokes lastObject] 
								  objectForKey:_KEY_POINTS_];
		if ([points count] > 0)
		{
			[delegate didFinishedEditFreehandAnnotationWithPionts:points];
		}
	}
}


- (void) touchesEnded:(NSSet *) touches withEvent:(UIEvent *) event
{
	NSInteger numThouchs = [[event allTouches] count];
	if (numThouchs == 1)
	{
		isTouchBegin = NO;

		NSMutableArray *arrayPointsInStroke = [[self.arrayStrokes lastObject] 
											   objectForKey:_KEY_POINTS_];
		
		CGPoint point = [[touches anyObject] locationInView:self];
		[arrayPointsInStroke addObject:[NSValue valueWithCGPoint:point]];

		[delegate didFinishedEditFreehandAnnotationWithPionts:arrayPointsInStroke];

		[self setNeedsDisplay];
	}
}


- (void) drawRect:(CGRect)rect
{
	if (self.arrayStrokes != nil)
	{
		NSMutableArray *arr = [self.arrayStrokes copy];

		for (NSDictionary *dictStroke in arr)
		{
			NSArray*	arrayPointsInstroke	= [dictStroke objectForKey:_KEY_POINTS_];
			UIColor*	color				= [dictStroke objectForKey:_KEY_COLOR_];

			float size = [[dictStroke objectForKey:_KEY_WIDTH_] floatValue];
			
			// wangpp 2012.3.5 start
			// freehand transparent
			BOOL        trans         = [[dictStroke objectForKey:_KEY_TRANS_] boolValue];
			// wangpp 2012.3.5 end
			
			// AR19012
			// 2012.02.23 M.Chikyu start.
			const CGFloat *rgb = CGColorGetComponents(color.CGColor);
			size_t rgbCount = CGColorGetNumberOfComponents(color.CGColor);
			
			if ((rgbCount == 4 && rgb[0] == 1 && rgb[1] == 1 && rgb[2] == 1) ||
				(rgbCount == 2 && rgb[0] == 1))
			{
				[[color colorWithAlphaComponent:1.0] set];
			}
			// 2012.02.23 M.Chikyu end.
			
			// wangpp 2012.3.5 start
			// freehand transparent
			/*
			 [[color colorWithAlphaComponent:0.25] set];					
			 */
			if (trans == YES) 
			{
				[[color colorWithAlphaComponent:0.25] set];	
			}
			else
			{
				[color set];
			}
			// wangpp 2012.3.5 end
			
			// draw the stroke, line by line, with rounded joints
			UIBezierPath* pathLines = [UIBezierPath bezierPath];

			CGPoint pointStart = [[arrayPointsInstroke objectAtIndex:0] CGPointValue];
			[pathLines moveToPoint:pointStart];
			
			for (int i = 0; i < (arrayPointsInstroke.count - 1); i++)
			{
				CGPoint pointNext = [[arrayPointsInstroke objectAtIndex:(i+1)] CGPointValue];
				[pathLines addLineToPoint:pointNext];
			}

			pathLines.lineWidth		= size * 1.4;
			pathLines.lineJoinStyle	= kCGLineJoinRound;
			pathLines.lineCapStyle	= kCGLineCapRound;

			[pathLines stroke];
		}

		[arr release];
	}
	
}


- (void) dealloc
{
	self.lineUIColor = nil;
	self.arrayStrokes = nil;
    [super dealloc];
}

@end

