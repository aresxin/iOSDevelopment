//
//  TouchMoveScaleView.m
//  TouchMoveScaleDemo
//
//  Created by jimney on 07/05/10.
//  Copyright 2010 OpenSource. All rights reserved.
//	Welcome to my HomePage In CocoaChina:http://www.cocoachina.com/bbs/u.php?action=topic

#import "TouchMoveScaleView.h"

@implementation TouchMoveScaleView
@synthesize maskOriginPoint;
@synthesize originImage;
@synthesize isDragAble;
/*
 *通过传入视图大小和原始图像，初始化视图
 *同时设置图片动画初始数据
 */
- (id)initWithFrame:(CGRect)frame image:(UIImage*)image
{
    if ((self = [super initWithFrame:frame])) 
	{		
		imageWidth						= image.size.width;
		imageHeight						= image.size.height;
		//显示图像视图
		originImage						=   [[UIImage alloc] initWithCGImage:image.CGImage];
		imageView						=	[[UIImageView alloc] initWithImage:originImage];
		[self addSubview:imageView];
		
		// 使图片视图支持交互和多点触摸
		[imageView setUserInteractionEnabled:YES];
		[imageView setMultipleTouchEnabled:YES];
		
		// 移动初始距离
		initialDistance = -1;
		
		// 动画缩放比例数据
		// 缩放后可见动画视图的原始位置坐标
		maskOriginPoint.x				=	maskOriginPoint.y = 0;
		
		// 缩放后可见动画视图的大小
		scaleSize						=   originImage.size;
		
		// 缩放后可见动画视图的相对于原始图片比例
		animationFinalScal				=	1.0;
		
		// 动画缩放控制标志
		//imageView.transform = CGAffineTransformIdentity;
    }
    return self;
}

// 定义一个静态全局变量，跟踪两次touch
static UITouch *g_firstTouch = nil;
static UITouch *g_secondTouch = nil;
/*
 *跟踪记录触摸开始的事件，并设置触摸相关的数据
 */
- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
	// touch move image in view
	{
		// 两点先后触摸和同时触摸
		if([touches count] < 2)
		{
			// first time single touch
			if (g_firstTouch == nil && g_secondTouch == nil)
			{
				g_firstTouch						= [[touches allObjects] objectAtIndex:0];
				firstStartTouchPosition				= [g_firstTouch locationInView:imageView];
				initialDistance						= -1;
			}
			else // 当有个点已经在屏幕时，设置第二点触摸点 
			{
				if(g_firstTouch == nil)
				{
					g_firstTouch						= [[touches allObjects] objectAtIndex:0];
					firstStartTouchPosition				= [g_firstTouch locationInView:imageView];
					
				}
				else
					if(g_secondTouch == nil)
					{
						g_secondTouch					= [[touches allObjects] objectAtIndex:0];
						secondStartTouchPosition		= [g_secondTouch locationInView:imageView];
						
					}
				
				initialDistance							= [self distanceBetweenTwoPoints:firstStartTouchPosition 
																toPoint:secondStartTouchPosition];
			}
			
		}
		else //if([touches count] == 2)
		{
			// multi touch
			g_firstTouch							= [[touches allObjects] objectAtIndex:0];
			g_secondTouch							= [[touches allObjects] objectAtIndex:1];
			
			
			firstStartTouchPosition					= [g_firstTouch locationInView:imageView];
			secondStartTouchPosition				= [g_secondTouch locationInView:imageView];
			
			initialDistance								= [self distanceBetweenTwoPoints:firstStartTouchPosition 
															toPoint:secondStartTouchPosition];
			
		}
#ifdef DEBUG
//		NSLog(@"g_firstTouch = %@", g_firstTouch);
//		NSLog(@"g_secondTouch = %@", g_secondTouch);
//		NSLog(@"firstStartTouchPosition = (%f, %f)", firstStartTouchPosition.x, firstStartTouchPosition.y);
//		NSLog(@"firstStartTouchPosition = (%f, %f)", secondStartTouchPosition.x, secondStartTouchPosition.y);	
//		NSLog(@"initialDistance = %f", initialDistance);
#endif	
	}
}
/*
 *在触摸移动事件中，根据一点触摸，移动视图
 *两点同时触摸，视图做缩放变化
 */
- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
	{
		UITouch *touch1 = [[touches allObjects] objectAtIndex:0];
		
		if ([touches count] == 1 && (g_firstTouch == nil || g_secondTouch == nil))// 只有一个点在move
		{
			CGPoint vectorPoint;
			if (touch1 == g_firstTouch)
			{
				//NSLog(@"firstTouch touch move!");
				CGPoint pos = [g_firstTouch locationInView:imageView];
				vectorPoint = CGPointMake(pos.x - firstStartTouchPosition.x, pos.y - firstStartTouchPosition.y);
			}
			else if (touch1 == g_secondTouch)
			{
				//NSLog(@"second Touch touch move!");
				CGPoint pos = [g_secondTouch locationInView:imageView];
				vectorPoint = CGPointMake(pos.x - secondStartTouchPosition.x, pos.y - secondStartTouchPosition.y);
			}
			else
			{
				return;
			}
			
			// 改变maskOriginPoint			
			// 当图片放大后，在屏幕上滑动距离的实际值改变，应该是* animationAllScal，这很重要
			maskOriginPoint.x -= vectorPoint.x * animationFinalScal;
			maskOriginPoint.y -= vectorPoint.y * animationFinalScal;
			// 单点触摸移动，做动画移动变换
			imageView.transform = CGAffineTransformTranslate(imageView.transform, vectorPoint.x,  vectorPoint.y);
			return;
		}
		
		if ((initialDistance > 0) && ([touches count] > 1)) 
		{
			UITouch *touch2 = [[touches allObjects] objectAtIndex:1];
			CGFloat currentDistance = [self distanceBetweenTwoPoints:[touch1 locationInView:imageView] 
															 toPoint:[touch2 locationInView:imageView]];
			CGFloat movement = currentDistance - initialDistance;
			CGFloat scale = [self scaleAmount: movement];
			// 两点触摸移动，做动画缩放
			imageView.transform = CGAffineTransformScale(imageView.transform, scale, scale);
			
			// x,y 缩放为整体大小变化的一半
			// 遮罩区域原始位置准确
			maskOriginPoint.x += scaleSize.width * (scale - 1) /2;
			maskOriginPoint.y += scaleSize.height * (scale - 1) /2;
			// 缩放的计算没问题
			// 相对原始图片变化
			animationFinalScal = imageView.transform.a;
			scaleSize.width  = animationFinalScal * originImage.size.width;
			scaleSize.height = animationFinalScal * originImage.size.height;
			//NSLog(@"move: scaleSize.width = %f， scaleSize.height = %f\n", scaleSize.width, scaleSize.height);
			
			
//当缩放图像的宽度小于屏幕时，不能缩放 
#define SCALE_BACK
#ifdef SCALE_BACK
			//缩放后的图像不小于屏幕
			CGRect screenRect = [[UIScreen mainScreen] applicationFrame];
			BOOL isScaled = NO;
			scale = 1.0;
			if(scaleSize.width >= scaleSize.height)
			{
//				NSLog(@"scaleSize.width >= scaleSize.height");
//				NSLog(@"scaleSize.width = %f， scaleSize.height = %f\n", scaleSize.width, scaleSize.height);
				
				if(scaleSize.width < screenRect.size.width)
				{
					scale		= screenRect.size.width / scaleSize.width ;
					isScaled	= YES;
				}
			}
			else
			{
				
				if(scaleSize.height < screenRect.size.height)
				{
					scale		= screenRect.size.height / scaleSize.height ;
					isScaled	= YES;
				}
			}
			// 需要恢复整屏幕大小
			if (isScaled)
			{
				imageView.transform = CGAffineTransformScale(imageView.transform, scale, scale);
				// x,y 缩放为整体大小变化的一半
				// 遮罩区域原始位置准确
				maskOriginPoint.x += scaleSize.width * (scale - 1) /2;
				maskOriginPoint.y += scaleSize.height * (scale - 1) /2;
				// 缩放的计算没问题
				// 相对原始图片变化,获得当前视图的缩放后的比例
				animationFinalScal = imageView.transform.a;
				scaleSize.width    = animationFinalScal * originImage.size.width;
				scaleSize.height   = animationFinalScal * originImage.size.height;
				
			}
#endif
			
			
		}	
	}
}
/*
 * 触摸结束，重设事件相关数据
 */
- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
	{
		// 重设touch移动的距离
		initialDistance		= -1;
		// 重设touch事件变量
		g_firstTouch		= nil ;
		g_secondTouch		= nil;
		//当只有一次touch事件时
		if ([touches count] < 2 )
		{
			if ([[touches allObjects] objectAtIndex:0] == g_firstTouch) 
			{
				g_firstTouch = nil;
			}
			else	if ([[touches allObjects] objectAtIndex:0] == g_secondTouch) 
			{
				g_secondTouch = nil;
			}
			
		}
		else  
		{
			if ([[touches allObjects] objectAtIndex:0] == g_firstTouch) 
			{
				// 以后用for循环替代，更好
				g_firstTouch = nil;
				g_secondTouch = nil;
			}
		}
		
		// 在结束，动画恢复相应的移动或者缩放
		// 当图片移除边界，恢复
		// 当图片缩放到一定大小，恢复，此功能以后要实现
		// maskImageView.size
		// maskOriginPoint
		// scaleSize
		
		CGContextRef context = UIGraphicsGetCurrentContext();
		[UIView beginAnimations:nil context:context];
		[UIView setAnimationCurve:UIViewAnimationCurveEaseOut];
		[UIView setAnimationDuration:0.5f];
		
		CGRect screenRect = [[UIScreen mainScreen] applicationFrame];
		CGRect	rect = imageView.frame;
		
		// 下面为动画缩放超过所设置大小，做动画恢复
		// 注意：下面的效果没有实现，有问题，你可以修改
//#define SCALE_BACK
#ifdef SCALE_BACK
		//缩放后的图像不小于屏幕
		BOOL isScaled = NO;
		CGFloat scale = 1.0;
		if(scaleSize.width >= scaleSize.height)
		{
			//NSLog(@"scaleSize.width >= scaleSize.height");
			//NSLog(@"scaleSize.width = %f， scaleSize.height = %f\n", scaleSize.width, scaleSize.height);
			
			if(scaleSize.width < screenRect.size.width)
			{
				scale				= screenRect.size.width / scaleSize.width ;
				isScaled			= YES;
			}
		}
		else
		{
			
			if(scaleSize.height < screenRect.size.height)
			{
				scale				= screenRect.size.height / scaleSize.height ;
				isScaled			= YES;
			}
		}
		// 需要恢复整屏幕大小
		if (isScaled)
		{
			// x,y 缩放为整体大小变化的一半
			// 遮罩区域原始位置准确
			maskOriginPoint.x += scaleSize.width * (scale - 1) /2;
			maskOriginPoint.y += scaleSize.height * (scale - 1) /2;
			// 缩放的计算没问题
			// 相对原始图片变化
			animationFinalScal	*= scale;
			scaleSize.width		= animationFinalScal * originImage.size.width;
			scaleSize.height		= animationFinalScal * originImage.size.height;
			rect.size					= scaleSize;
		}
#endif
		
		// 此值为判断图片右边和下边到屏幕距离
		CGFloat deltaX = (scaleSize.width  - maskOriginPoint.x) -  screenRect.size.width;
		//CGFloat deltaY = (scaleSize.height - maskOriginPoint.y) -  screenRect.size.height;
#ifdef DEBUG	
		//NSLog(@"==========================================================\n");
		//NSLog(@"animationFinalScal = %f\n", animationFinalScal);
		//NSLog(@"mainscreen move dist = %f\n", animationFinalScal * screenRect.size.width);
		//NSLog(@"maskOriginPoint.x = %f, maskOriginPoint.y = %f\n",maskOriginPoint.x, maskOriginPoint.y);
		//NSLog(@"scaleSize.width = %f， scaleSize.height = %f\n", scaleSize.width, scaleSize.height);
		//NSLog(@"screenRealSize.width = %f， screenRealSize.height = %f\n", screenRect.size.width, screenRect.size.height);
		//NSLog(@"moveX = %f, moveY = %f\n", deltaX, deltaY);
#endif		
		
		// 移出右外
		if(deltaX < 0)
		{
			//NSLog(@"right outside!\n");
			rect.origin.x				= -(scaleSize.width - screenRect.size.width);
			maskOriginPoint.x	=   scaleSize.width - screenRect.size.width;
		}
		// 优先右上对齐
		// 当x小于零，表示移出左外
		if (maskOriginPoint.x < 0)
		{
			//NSLog(@"left outside!\n");
			rect.origin.x				= 0;
			maskOriginPoint.x	= 0;
		}
		else// x > 0
		{
			if (rect.size.width < screenRect.size.width) 
			{
				//NSLog(@"up outside!\n");
				rect.origin.x				= 0;
				maskOriginPoint.x	= 0;
			}
		}
		// 当y小于零，表示移出上外
		if (maskOriginPoint.y < 0 )
		{
			//NSLog(@"up outside!\n");
			rect.origin.y				= 0;
			maskOriginPoint.y	= 0;
		}
		else// y > 0
		{
			if (rect.size.height < screenRect.size.height) 
			{
				//NSLog(@"up outside!\n");
				rect.origin.y				= 0;
				maskOriginPoint.y	= 0;
			}
		}
		
		
		[imageView setFrame:rect];
		[UIView commitAnimations]; 
		
		//NSLog(@"maskOriginPoint.x = %f", maskOriginPoint.x);
		//NSLog(@"animation end: scaleSize.width = %f， scaleSize.height = %f\n", scaleSize.width, scaleSize.height);
		
	}
}

/*
 *计算touch的两个点的距离
 */
- (CGFloat)distanceBetweenTwoPoints:(CGPoint)fromPoint toPoint:(CGPoint)toPoint 
{
	
	float x = toPoint.x - fromPoint.x;
	float y = toPoint.y - fromPoint.y;
	
	return sqrt(x * x + y * y);
}

/*
 *根据移动的距离，计算相应的缩放比例
 */
- (CGFloat)scaleAmount: (CGFloat)delta 
{
	CGFloat pix = sqrt(self.bounds.size.width * self.bounds.size.height);
	CGFloat scale = 1.0 + (delta / pix);
	return scale;
}

/*
 *释放内存
 */
- (void) dealloc
{
	[imageView release];
	[originImage release];
    [super dealloc];
}
@end
