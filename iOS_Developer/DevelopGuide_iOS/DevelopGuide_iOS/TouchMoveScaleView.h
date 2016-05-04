//
//  TouchMoveScaleView.h
//  TouchMoveScaleDemo
//
//  Created by jimney on 07/05/10.
//  Copyright 2010 OpenSource. All rights reserved.
//	Welcome to my HomePage In CocoaChina:http://www.cocoachina.com/bbs/u.php?action=topic

#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>

/*
 *类说明
 *此类主要实现在触摸过程中，实时控制视图动画的变换
 *一点触摸移动视图，两点触摸缩放视图的动作
 *实现的主要思路：因为动画的过程是连贯的，在变化的过程中，
 *不能直接去获得过程中的值，不连续的动画控制比较难
 *因为虽然图片视图的大小或者位置发生改变时，但是视图本身的数据并没变化
 *所以采用人为跟踪动画变换过程，将此时所表现在视图界面中的动画变化后的虚拟值，
 *保存在相应的变量中
 */

//！补充：虚拟机中使用多点触摸，按住ALT键，可显示两个触摸点，点击移动即可看到效果

@interface TouchMoveScaleView : UIView 
{
	
	UIImage					*originImage;
	UIImageView				*imageView;
	
	CGFloat					imageWidth;
	CGFloat					imageHeight;

	// 跟踪图片在屏幕显示区域的原点位于整个图片的位置
	CGPoint					maskOriginPoint;
	// 跟踪缩放后图片相对于原始图片的比例大小
	CGSize					scaleSize;

	
	// 动画移动及缩放图像
	CGPoint					firstStartTouchPosition;
	CGPoint					secondStartTouchPosition;
	CGFloat					initialDistance;
	
	// 动画放缩后，原始图片变化比例
	CGFloat					animationFinalScal;
		
}
@property(nonatomic)			CGPoint		maskOriginPoint;
@property(nonatomic,retain)		UIImage		*originImage;
@property(nonatomic)			BOOL		isDragAble;

// 初始化视图
- (id)initWithFrame:(CGRect)frame image:(UIImage*)image;

// 根据touch 的亮点距离变化，改变图片的大小
- (CGFloat)scaleAmount: (CGFloat)delta;

// 计算两个点之间的距离
- (CGFloat)distanceBetweenTwoPoints:(CGPoint)fromPoint toPoint:(CGPoint)toPoint;

@end
