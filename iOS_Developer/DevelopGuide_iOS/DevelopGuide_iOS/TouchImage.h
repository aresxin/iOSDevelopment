//
//  TouchImage.h
//  TouchFrame
//
//  Created by 廖 海龙 on 12-2-17.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>
@interface TouchImage : UIView <UIGestureRecognizerDelegate>{
	
	//背景层
	CALayer *bgLayer;
	
	//八个拖动点
	UIImageView *up;
	UIImageView *down;
	UIImageView *left;
	UIImageView *right;
	
	UIImageView *up_left;
	UIImageView *up_right;
	UIImageView *down_left;
	UIImageView *down_right;
	
	//共同使用值
	CGFloat current_height;
	CGFloat curretn_width;
	
	//整体拖动值
	CGFloat all_begin_point_x;
	CGFloat all_begin_point_y;
	CGFloat all_move_point_x;
	CGFloat all_move_point_y;
	
	//up拖动值
	CGFloat up_begin_point_y;
	CGFloat up_move_point_y;
	
	//down拖动值
	CGFloat down_begin_point_y;
	CGFloat down_move_point_y;
	
	//left拖动值
	CGFloat left_begin_point_x;
	CGFloat left_move_point_x;
	
	//right拖动值
	CGFloat right_begin_point_x;
	CGFloat right_move_point_x;
	
	//up+left拖动值 
	CGFloat _up_left_begin_point_x;
	CGFloat _up_left_move_point_x;
	CGFloat _up_left_begin_point_y;
	CGFloat _up_left_move_point_y;
	
	//up+right拖动值
	CGFloat _up_right_begin_point_x;
	CGFloat _up_right_move_point_x;
	CGFloat _up_right_begin_point_y;
	CGFloat _up_right_move_point_y;
	
	//down+left拖动值
	CGFloat _down_left_begin_point_x;
	CGFloat _down_left_move_point_x;
	CGFloat _down_left_begin_point_y;
	CGFloat _down_left_move_point_y;
	
	//down+right拖动值
	CGFloat _down_right_begin_point_x;
	CGFloat _down_right_move_point_x;
	CGFloat _down_right_begin_point_y;
	CGFloat _down_right_move_point_y;
	
	//长按事件
	UILongPressGestureRecognizer *longPress;
	//双击事件
	UITapGestureRecognizer *double_click;
	//整体拖动事件
	UIPanGestureRecognizer *self_touch;
	//up拖动事件
	UIPanGestureRecognizer *up_touch;
	//down拖动事件
	UIPanGestureRecognizer *down_touch;
	//left拖动事件
	UIPanGestureRecognizer *left_touch;
	//right拖动事件
	UIPanGestureRecognizer *right_touch;
	//up+left拖动事件
	UIPanGestureRecognizer *_up_left_touch;
	//up+right拖动事件
	UIPanGestureRecognizer *_up_right_touch;
	//down+left拖动事件
	UIPanGestureRecognizer *_down_left_touch;
	//down+right拖动事件
	UIPanGestureRecognizer *_down_right_touch;
	
	BOOL isNotBound;
	
	int double_click_count;
}
@property(nonatomic,retain)CALayer *bgLayer;
-(void)addTouchButton;
@end
