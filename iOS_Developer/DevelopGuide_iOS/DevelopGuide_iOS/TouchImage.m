//
//  TouchImage.m
//  TouchFrame
//
//  Created by 廖 海龙 on 12-2-17.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//
/*
 *拖动矩形的边缘，改变矩形的Frame
  Demo下载地址 http://www.cocoachina.com/bbs/read.php?tid=95340
 */
#import "TouchImage.h"

@implementation TouchImage
@synthesize bgLayer;

- (id)initWithColor:(UIColor *)color{
    
    self = [super init];
    if (self) {
		double_click_count = 0;
        //self.backgroundColor = color;
		[self.layer setMasksToBounds:YES];
		//[self.layer setCornerRadius:10.0];
		[self.layer setBorderWidth:5.0f];
		
		CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
		//CGImageCreate();
		CGColorRef colorref = CGColorCreate(colorSpace,(CGFloat[]){ 0, 0, 0, 1}); 
		[self.layer setBorderColor:colorref];
		
		bgLayer = [[CALayer alloc] init]; 
		UIImage *image = [UIImage imageNamed:@"fuck.jpg"]; 
		bgLayer.frame = CGRectMake(0, 0, image.size.width,image.size.height);
		bgLayer.contents = (id)[image CGImage]; 
		[self.layer addSublayer:bgLayer];
		[bgLayer release];
		//[self setNeedsDisplay];
    }
    return self;
}

//在本类视图addsubview以后使用
-(void)addTouchButton{
	if ([self superview]) {
		up = [[UIImageView alloc] init];
		up.userInteractionEnabled = YES;
		//[up setBackgroundColor:[UIColor grayColor]];
		[up setImage:[UIImage imageNamed:@"pix@2x.png"]];
		up.layer.cornerRadius=10;
		up.frame = CGRectMake(0, 0, 14, 14);
		up.center = CGPointMake(self.frame.size.width/2+self.frame.origin.x, self.frame.origin.y);
		[self.superview insertSubview:up atIndex:10000];
		[up release];
		
		
		down = [[UIImageView alloc] init];
		down.userInteractionEnabled = YES;
		//[down setBackgroundColor:[UIColor grayColor]];
		down.layer.cornerRadius=10;
		[down setImage:[UIImage imageNamed:@"pix.png"]];
		down.frame = CGRectMake(0, 0, 14, 14);
		down.center = CGPointMake(self.frame.size.width/2+self.frame.origin.x, self.frame.origin.y+self.frame.size.height);
		[self.superview insertSubview:down atIndex:10001];
		[down release];
		
		
		left = [[UIImageView alloc] init];
		left.userInteractionEnabled = YES;
		//[left setBackgroundColor:[UIColor grayColor]];
		left.layer.cornerRadius=10;
		[left setImage:[UIImage imageNamed:@"pix.png"]];
		left.frame = CGRectMake(0, 0, 14, 14);
		left.center = CGPointMake(self.frame.origin.x, self.frame.origin.y+self.frame.size.height/2);
		[self.superview insertSubview:left atIndex:10002];
		[left release];
		
		right = [[UIImageView alloc] init];
		right.userInteractionEnabled = YES;
		//[right setBackgroundColor:[UIColor grayColor]];
		right.layer.cornerRadius=10;
		[right setImage:[UIImage imageNamed:@"pix.png"]];
		right.frame = CGRectMake(0, 0, 14, 14);
		right.center = CGPointMake(self.frame.origin.x+self.frame.size.width, self.frame.origin.y+self.frame.size.height/2);
		[self.superview insertSubview:right atIndex:10003];
		[right release];
		
		
		up_left = [[UIImageView alloc] init];
		up_left.userInteractionEnabled = YES;
		//[up_left setBackgroundColor:[UIColor grayColor]];
		up_left.layer.cornerRadius=10;
		[up_left setImage:[UIImage imageNamed:@"pix.png"]];
		up_left.frame = CGRectMake(0, 0, 14, 14);
		up_left.center = CGPointMake(self.frame.origin.x, self.frame.origin.y);
		[self.superview insertSubview:up_left atIndex:10004];
		[up_left release];
		
		
		up_right = [[UIImageView alloc] init];
		up_right.userInteractionEnabled = YES;
		//[up_right setBackgroundColor:[UIColor grayColor]];
		up_right.layer.cornerRadius=10;
		[up_right setImage:[UIImage imageNamed:@"pix.png"]];
		up_right.frame = CGRectMake(0, 0, 14, 14);
		up_right.center = CGPointMake(self.frame.origin.x+self.frame.size.width, self.frame.origin.y);
		[self.superview insertSubview:up_right atIndex:10005];
		[up_right release];
		
		down_left = [[UIImageView alloc] init];
		down_left.userInteractionEnabled = YES;
		//[down_left setBackgroundColor:[UIColor grayColor]];
		down_left.layer.cornerRadius=10;
		[down_left setImage:[UIImage imageNamed:@"pix.png"]];
		down_left.frame = CGRectMake(0, 0, 14, 14);
		down_left.center = CGPointMake(self.frame.origin.x, self.frame.origin.y+self.frame.size.height);
		[self.superview insertSubview:down_left atIndex:10006];
		[down_left release];
		
		down_right = [[UIImageView alloc] init];
		down_right.userInteractionEnabled = YES;
		//[down_right setBackgroundColor:[UIColor grayColor]];
		down_right.layer.cornerRadius=10;
		[down_right setImage:[UIImage imageNamed:@"pix.png"]];
		down_right.frame = CGRectMake(0, 0, 14, 14);
		down_right.center = CGPointMake(self.frame.origin.x+self.frame.size.width, self.frame.origin.y+self.frame.size.height);
		[self.superview insertSubview:down_right atIndex:10007];
		[down_right release];

		[up setHidden:YES];
		[down setHidden:YES];
		[left setHidden:YES];
		[right setHidden:YES];
		[up_left setHidden:YES];
		[up_right setHidden:YES];
		[down_left setHidden:YES];
		[down_right setHidden:YES];
		
		longPress =[[UILongPressGestureRecognizer alloc] initWithTarget:self action:@selector(toucheSet:)];
		longPress.minimumPressDuration = 0.5;
		[self addGestureRecognizer:longPress];
		[longPress release];
		
		double_click = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(toucheSet:)];
		double_click.numberOfTapsRequired = 2;
		double_click.numberOfTouchesRequired = 1;
		[self addGestureRecognizer:double_click];
		[double_click release];
		
		self_touch = [[UIPanGestureRecognizer alloc] initWithTarget:self action:@selector(toucheSet:)];
		self_touch.delegate = self;
		[self addGestureRecognizer:self_touch];
		[self_touch release];
		
		up_touch = [[UIPanGestureRecognizer alloc]  initWithTarget:self action:@selector(toucheSet:)];
		up_touch.delegate = self;
		[up addGestureRecognizer:up_touch];
		[up_touch release];
		
		down_touch = [[UIPanGestureRecognizer alloc]  initWithTarget:self action:@selector(toucheSet:)];
		down_touch.delegate = self;
		[down addGestureRecognizer:down_touch];
		[down_touch release];
		
		left_touch = [[UIPanGestureRecognizer alloc]  initWithTarget:self action:@selector(toucheSet:)];
		left_touch.delegate = self;
		[left addGestureRecognizer:left_touch];
		[left_touch release];
		
		right_touch = [[UIPanGestureRecognizer alloc]  initWithTarget:self action:@selector(toucheSet:)];
		right_touch.delegate = self;
		[right addGestureRecognizer:right_touch];
		[right_touch release];
		
		_up_left_touch = [[UIPanGestureRecognizer alloc]  initWithTarget:self action:@selector(toucheSet:)];
		_up_left_touch.delegate = self;
		[up_left addGestureRecognizer:_up_left_touch];
		[_up_left_touch release]; 
		
		_up_right_touch = [[UIPanGestureRecognizer alloc]  initWithTarget:self action:@selector(toucheSet:)];
		_up_right_touch.delegate = self;
		[up_right addGestureRecognizer:_up_right_touch];
		[_up_right_touch release]; 
		
		_down_left_touch = [[UIPanGestureRecognizer alloc]  initWithTarget:self action:@selector(toucheSet:)];
		_down_left_touch.delegate = self;
		[down_left addGestureRecognizer:_down_left_touch];
		[_down_left_touch release];  
		
		_down_right_touch = [[UIPanGestureRecognizer alloc]  initWithTarget:self action:@selector(toucheSet:)];
		_down_right_touch.delegate = self;
		[down_right addGestureRecognizer:_down_right_touch];
		[_down_right_touch release];  
		
		
		up_touch.maximumNumberOfTouches = 1;
		down_touch.maximumNumberOfTouches = 1;
		left_touch.maximumNumberOfTouches = 1;
		right_touch.maximumNumberOfTouches = 1;
		_up_left_touch.maximumNumberOfTouches = 1;
		_up_right_touch.maximumNumberOfTouches = 1;
		_down_left_touch.maximumNumberOfTouches = 1;
		_down_right_touch.maximumNumberOfTouches = 1;
	}
}

-(void)moveStop{

}


-(void)toucheSet:(UIGestureRecognizer *)gr{	
	NSLog(@"123");

	
	/********长按事件*********/
	if (gr == longPress) {
		//[self.superview bringSubviewToFront:self];
		for (int i = 0;i<[[self.superview subviews] count];i++) {
			if ([[self.superview subviews] objectAtIndex:i] == self) {
				[self.superview exchangeSubviewAtIndex:i withSubviewAtIndex:i+1];
			}
		}
		[self.superview insertSubview:up atIndex:10000];
		[self.superview insertSubview:down atIndex:10001];
		[self.superview insertSubview:left atIndex:10002];
		[self.superview insertSubview:right atIndex:10003];
		[self.superview insertSubview:up_left atIndex:10004];
		[self.superview insertSubview:up_right atIndex:10005];
		[self.superview insertSubview:down_left atIndex:10006];
		[self.superview insertSubview:down_right atIndex:10007];
		return;
	}
	
	if (gr == double_click) {
		if (double_click_count == 0) {
			double_click_count++;
			UIImage *image = [UIImage imageNamed:@"fuck2.jpg"]; 
			bgLayer.frame = CGRectMake(0, 0, image.size.width,image.size.height);
			bgLayer.contents = (id)[image CGImage]; 
		}else {
			double_click_count = 0;
			UIImage *image = [UIImage imageNamed:@"fuck.jpg"]; 
			bgLayer.frame = CGRectMake(0, 0, image.size.width,image.size.height);
			bgLayer.contents = (id)[image CGImage]; 
		}
		//[self setNeedsDisplay];
	}
	
	[UIView beginAnimations:nil context:nil];
	[UIView setAnimationDuration:0.05];
	[UIView setAnimationDelegate:self];
	[UIView setAnimationDidStopSelector:@selector(moveStop)];
	/********本身拖动事件*********/
	if (gr == self_touch) {
		all_move_point_x = [gr locationInView:self].x;
		all_move_point_y = [gr locationInView:self].y;
		
		self.center = CGPointMake(self.center.x+(all_move_point_x-all_begin_point_x), self.center.y+(all_move_point_y-all_begin_point_y));
		up.center = CGPointMake(self.frame.size.width/2+self.frame.origin.x, self.frame.origin.y);
		down.center = CGPointMake(self.frame.size.width/2+self.frame.origin.x, self.frame.origin.y+self.frame.size.height);
		left.center = CGPointMake(self.frame.origin.x, self.frame.origin.y+self.frame.size.height/2);
		right.center = CGPointMake(self.frame.origin.x+self.frame.size.width, self.frame.origin.y+self.frame.size.height/2);
		up_left.center = CGPointMake(self.frame.origin.x, self.frame.origin.y);
		up_right.center = CGPointMake(self.frame.origin.x+self.frame.size.width, self.frame.origin.y);
		down_left.center = CGPointMake(self.frame.origin.x, self.frame.origin.y+self.frame.size.height);
		down_right.center = CGPointMake(self.frame.origin.x+self.frame.size.width, self.frame.origin.y+self.frame.size.height);
		/********向上拖动事件*********/	
	}else if (gr == up_touch) {
		up_move_point_y = [gr locationInView:up].y;
        
		NSLog(@"up_move_point_y is -----%f",up_move_point_y);
		self.frame = CGRectMake(self.frame.origin.x, up.center.y, self.frame.size.width, current_height-(up.center.y - up_begin_point_y));
		up.center = CGPointMake(up.center.x, up.center.y+up_move_point_y);
		down.center = CGPointMake(self.frame.size.width/2+self.frame.origin.x, self.frame.origin.y+self.frame.size.height);
		left.center = CGPointMake(self.frame.origin.x, self.frame.origin.y+self.frame.size.height/2);
		right.center = CGPointMake(self.frame.origin.x+self.frame.size.width, self.frame.origin.y+self.frame.size.height/2);
		up_left.center = CGPointMake(self.frame.origin.x, self.frame.origin.y);
		up_right.center = CGPointMake(self.frame.origin.x+self.frame.size.width, self.frame.origin.y);
		down_left.center = CGPointMake(self.frame.origin.x, self.frame.origin.y+self.frame.size.height);
		down_right.center = CGPointMake(self.frame.origin.x+self.frame.size.width, self.frame.origin.y+self.frame.size.height);
		/********向下拖动事件*********/	
	}else if (gr == down_touch) {
		down_move_point_y = [gr locationInView:down].y;
		
		self.frame = CGRectMake(self.frame.origin.x, self.frame.origin.y, self.frame.size.width, current_height+(down.center.y - down_begin_point_y));
		up.center = CGPointMake(self.frame.size.width/2+self.frame.origin.x, self.frame.origin.y);
		down.center = CGPointMake(down.center.x,down.center.y+down_move_point_y);
		left.center = CGPointMake(self.frame.origin.x, self.frame.origin.y+self.frame.size.height/2);
		right.center = CGPointMake(self.frame.origin.x+self.frame.size.width, self.frame.origin.y+self.frame.size.height/2);
		up_left.center = CGPointMake(self.frame.origin.x, self.frame.origin.y);
		up_right.center = CGPointMake(self.frame.origin.x+self.frame.size.width, self.frame.origin.y);
		down_left.center = CGPointMake(self.frame.origin.x, self.frame.origin.y+self.frame.size.height);
		down_right.center = CGPointMake(self.frame.origin.x+self.frame.size.width, self.frame.origin.y+self.frame.size.height);
		/********向左拖动事件*********/
	}else if (gr == left_touch) {
		left_move_point_x = [gr locationInView:left].x;
		
		self.frame = CGRectMake(left.center.x, self.frame.origin.y, curretn_width -(left.center.x - left_begin_point_x), self.frame.size.height);
		up.center = CGPointMake(self.frame.size.width/2+self.frame.origin.x, self.frame.origin.y);
		down.center = CGPointMake(self.frame.size.width/2+self.frame.origin.x, self.frame.origin.y+self.frame.size.height);
		left.center = CGPointMake(left.center.x+left_move_point_x, self.frame.origin.y+self.frame.size.height/2);
		right.center = CGPointMake(self.frame.origin.x+self.frame.size.width, self.frame.origin.y+self.frame.size.height/2);
		up_left.center = CGPointMake(self.frame.origin.x, self.frame.origin.y);
		up_right.center = CGPointMake(self.frame.origin.x+self.frame.size.width, self.frame.origin.y);
		down_left.center = CGPointMake(self.frame.origin.x, self.frame.origin.y+self.frame.size.height);
		down_right.center = CGPointMake(self.frame.origin.x+self.frame.size.width, self.frame.origin.y+self.frame.size.height);
		/********向右拖动事件*********/
	}else if (gr == right_touch) {
		right_move_point_x = [gr locationInView:right].x;
		//UIMenuController
		self.frame = CGRectMake(self.frame.origin.x, self.frame.origin.y, curretn_width+(right.center.x - right_begin_point_x), self.frame.size.height);
		up.center = CGPointMake(self.frame.size.width/2+self.frame.origin.x, self.frame.origin.y);
		down.center = CGPointMake(self.frame.size.width/2+self.frame.origin.x, self.frame.origin.y+self.frame.size.height);
		left.center = CGPointMake(self.frame.origin.x, self.frame.origin.y+self.frame.size.height/2);
		right.center = CGPointMake(right.center.x+right_move_point_x, self.frame.origin.y+self.frame.size.height/2);
		up_left.center = CGPointMake(self.frame.origin.x, self.frame.origin.y);
		up_right.center = CGPointMake(self.frame.origin.x+self.frame.size.width, self.frame.origin.y);
		down_left.center = CGPointMake(self.frame.origin.x, self.frame.origin.y+self.frame.size.height);
		down_right.center = CGPointMake(self.frame.origin.x+self.frame.size.width, self.frame.origin.y+self.frame.size.height);
		/********左上拖动事件*********/
	}else if (gr == _up_left_touch) {
		_up_left_move_point_x = [gr locationInView:up_left].x;
		_up_left_move_point_y = [gr locationInView:up_left].y;
		
		self.frame = CGRectMake(up_left.center.x, up_left.center.y, curretn_width -(up_left.center.x - _up_left_begin_point_x), current_height-(up_left.center.y - _up_left_begin_point_y));
		up.center = CGPointMake(self.frame.size.width/2+self.frame.origin.x, self.frame.origin.y);
		down.center = CGPointMake(self.frame.size.width/2+self.frame.origin.x, self.frame.origin.y+self.frame.size.height);
		left.center = CGPointMake(self.frame.origin.x, self.frame.origin.y+self.frame.size.height/2);
		right.center = CGPointMake(self.frame.origin.x+self.frame.size.width, self.frame.origin.y+self.frame.size.height/2);
		up_left.center = CGPointMake(up_left.center.x+_up_left_move_point_x, up_left.center.y+_up_left_move_point_y);
		up_right.center = CGPointMake(self.frame.origin.x+self.frame.size.width, self.frame.origin.y);
		down_left.center = CGPointMake(self.frame.origin.x, self.frame.origin.y+self.frame.size.height);
		down_right.center = CGPointMake(self.frame.origin.x+self.frame.size.width, self.frame.origin.y+self.frame.size.height);
		/********右上拖动事件*********/
	}else if (gr == _up_right_touch) {
		_up_right_move_point_x = [gr locationInView:up_right].x;
		_up_right_move_point_y = [gr locationInView:up_right].y;
		
		self.frame = CGRectMake(self.frame.origin.x, up_right.center.y, curretn_width+(up_right.center.x - _up_right_begin_point_x), current_height-(up_right.center.y - _up_right_begin_point_y));
		up.center = CGPointMake(self.frame.size.width/2+self.frame.origin.x, self.frame.origin.y);
		down.center = CGPointMake(self.frame.size.width/2+self.frame.origin.x, self.frame.origin.y+self.frame.size.height);
		left.center = CGPointMake(self.frame.origin.x, self.frame.origin.y+self.frame.size.height/2);
		right.center = CGPointMake(self.frame.origin.x+self.frame.size.width, self.frame.origin.y+self.frame.size.height/2);
		up_left.center = CGPointMake(self.frame.origin.x, self.frame.origin.y);
		up_right.center = CGPointMake(up_right.center.x+_up_right_move_point_x, up_right.center.y+_up_right_move_point_y);
		down_left.center = CGPointMake(self.frame.origin.x, self.frame.origin.y+self.frame.size.height);
		down_right.center = CGPointMake(self.frame.origin.x+self.frame.size.width, self.frame.origin.y+self.frame.size.height);
		/********左下拖动事件*********/
	}else if (gr == _down_left_touch) {
		_down_left_move_point_x = [gr locationInView:down_left].x;
		_down_left_move_point_y = [gr locationInView:down_left].y;
		
		self.frame = CGRectMake(down_left.center.x, self.frame.origin.y, curretn_width -(down_left.center.x - _down_left_begin_point_x), current_height+(down_left.center.y - _down_left_begin_point_y));
		up.center = CGPointMake(self.frame.size.width/2+self.frame.origin.x, self.frame.origin.y);
		down.center = CGPointMake(self.frame.size.width/2+self.frame.origin.x, self.frame.origin.y+self.frame.size.height);
		left.center = CGPointMake(self.frame.origin.x, self.frame.origin.y+self.frame.size.height/2);
		right.center = CGPointMake(self.frame.origin.x+self.frame.size.width, self.frame.origin.y+self.frame.size.height/2);
		up_left.center = CGPointMake(self.frame.origin.x, self.frame.origin.y);
		up_right.center = CGPointMake(self.frame.origin.x+self.frame.size.width, self.frame.origin.y);
		down_left.center = CGPointMake(down_left.center.x+_down_left_move_point_x, down_left.center.y+_down_left_move_point_y);
		down_right.center = CGPointMake(self.frame.origin.x+self.frame.size.width, self.frame.origin.y+self.frame.size.height);
		/********右下拖动事件*********/
	}else if (gr == _down_right_touch) {
		_down_right_move_point_x = [gr locationInView:down_right].x;
		_down_right_move_point_y = [gr locationInView:down_right].y;
		
		self.frame = CGRectMake(self.frame.origin.x, self.frame.origin.y, curretn_width+(down_right.center.x - _down_right_begin_point_x), current_height+(down_right.center.y - _down_right_begin_point_y));
		up.center = CGPointMake(self.frame.size.width/2+self.frame.origin.x, self.frame.origin.y);
		down.center = CGPointMake(self.frame.size.width/2+self.frame.origin.x, self.frame.origin.y+self.frame.size.height);
		left.center = CGPointMake(self.frame.origin.x, self.frame.origin.y+self.frame.size.height/2);
		right.center = CGPointMake(self.frame.origin.x+self.frame.size.width, self.frame.origin.y+self.frame.size.height/2);
		up_left.center = CGPointMake(self.frame.origin.x, self.frame.origin.y);
		up_right.center = CGPointMake(self.frame.origin.x+self.frame.size.width, self.frame.origin.y);
		down_left.center = CGPointMake(self.frame.origin.x, self.frame.origin.y+self.frame.size.height);
		down_right.center = CGPointMake(down_right.center.x+_down_right_move_point_x, down_right.center.y+_down_right_move_point_y);
	}
	[UIView commitAnimations];
	
	if(self.frame.size.width<200){
		self.frame = CGRectMake(self.frame.origin.x, self.frame.origin.y, 200, self.frame.size.height);
		[self setAllPointCenter];
		//isNotBound = NO; 
		return;
	}
	
	if (self.frame.size.height<200) {
		self.frame = CGRectMake(self.frame.origin.x, self.frame.origin.y, self.frame.size.width, 200);
		[self setAllPointCenter];
		//isNotBound = NO; 
		return;
	}
	
	
	//边界限制
	if (self.frame.origin.x < 0 && self.frame.origin.y > 748-self.frame.size.height) {
		[self setFrame:CGRectMake(0, 748-self.frame.size.height, self.frame.size.width, self.frame.size.height)];
		[self setAllPointCenter];
		return;
	}
	
	if (self.frame.origin.y < 0 && self.frame.origin.x > 1024-self.frame.size.width) {
		[self setFrame:CGRectMake(1024-self.frame.size.width, 0, self.frame.size.width, self.frame.size.height)];
		[self setAllPointCenter];
		return;
	}
	
	
	if (self.frame.origin.x < 0 && self.frame.origin.y < 0) {
		[self setFrame:CGRectMake(0, 0, self.frame.size.width, self.frame.size.height)];
		[self setAllPointCenter];
		return;
	}
	if (self.frame.origin.x < 0) {
		[self setFrame:CGRectMake(0, self.frame.origin.y, self.frame.size.width, self.frame.size.height)];
		[self setAllPointCenter];
		//isNotBound = NO; 
		return;
	}
	if (self.frame.origin.y < 0) {
		[self setFrame:CGRectMake(self.frame.origin.x, 0, self.frame.size.width, self.frame.size.height)];
		[self setAllPointCenter];
		//isNotBound = NO; 
		return;
	}
	
	
	if (self.frame.origin.x > 1024-self.frame.size.width && self.frame.origin.y > 748-self.frame.size.height) {
		[self setFrame:CGRectMake(1024-self.frame.size.width, 748-self.frame.size.height, self.frame.size.width, self.frame.size.height)];
		[self setAllPointCenter];
		return;
	}
	if (self.frame.origin.x > 1024-self.frame.size.width) {
		[self setFrame:CGRectMake(1024-self.frame.size.width, self.frame.origin.y, self.frame.size.width, self.frame.size.height)];
		[self setAllPointCenter];
		return;
	}
	if (self.frame.origin.y > 748-self.frame.size.height) {
		[self setFrame:CGRectMake(self.frame.origin.x, 748-self.frame.size.height, self.frame.size.width, self.frame.size.height)];
		[self setAllPointCenter];
		return;
	}
	
}

-(void)setAllPointCenter{
	up.center = CGPointMake(self.frame.size.width/2+self.frame.origin.x, self.frame.origin.y);
	down.center = CGPointMake(self.frame.size.width/2+self.frame.origin.x, self.frame.origin.y+self.frame.size.height);
	left.center = CGPointMake(self.frame.origin.x, self.frame.origin.y+self.frame.size.height/2);
	right.center = CGPointMake(self.frame.origin.x+self.frame.size.width, self.frame.origin.y+self.frame.size.height/2);
	up_left.center = CGPointMake(self.frame.origin.x, self.frame.origin.y);
	up_right.center = CGPointMake(self.frame.origin.x+self.frame.size.width, self.frame.origin.y);
	down_left.center = CGPointMake(self.frame.origin.x, self.frame.origin.y+self.frame.size.height);
	down_right.center = CGPointMake(self.frame.origin.x+self.frame.size.width, self.frame.origin.y+self.frame.size.height);
}

- (BOOL)gestureRecognizer:(UIGestureRecognizer *)gestureRecognizer shouldReceiveTouch:(UITouch *)touch{
//- (BOOL)gestureRecognizer:(UIGestureRecognizer *)gestureRecognizer shouldRecognizeSimultaneouslyWithGestureRecognizer:(UIGestureRecognizer *)otherGestureRecognizer
	//return YES;
	return YES;
}

- (BOOL)gestureRecognizerShouldBegin:(UIGestureRecognizer *)gestureRecognizer{
//	[up setHidden:YES];
//	[down setHidden:YES];
//	[left setHidden:YES];
//	[right setHidden:YES];
//	[up_left setHidden:YES];
//	[up_right setHidden:YES];
//	[down_left setHidden:YES];
//	[down_right setHidden:YES];
	
	if (gestureRecognizer == self_touch) {
		all_begin_point_x = [gestureRecognizer locationInView:self].x;
		all_begin_point_y = [gestureRecognizer locationInView:self].y;
	}else if (gestureRecognizer == up_touch) {
		up_begin_point_y = up.center.y; 
		current_height = self.frame.size.height;
	}else if (gestureRecognizer == down_touch) {
		down_begin_point_y = down.center.y;
		current_height = self.frame.size.height;
	}else if (gestureRecognizer == left_touch) {
		left_begin_point_x = left.center.x;
		curretn_width = self.frame.size.width;
	}else if (gestureRecognizer == right_touch) {
		right_begin_point_x = right.center.x;
		curretn_width = self.frame.size.width;
	}else if (gestureRecognizer == _up_left_touch) {
		_up_left_begin_point_x = up_left.center.x;
		_up_left_begin_point_y = up_left.center.y;
		curretn_width = self.frame.size.width;
		current_height = self.frame.size.height;
	}else if (gestureRecognizer == _up_right_touch) {
		_up_right_begin_point_x = up_right.center.x;
		_up_right_begin_point_y = up_right.center.y;
		curretn_width = self.frame.size.width;
		current_height = self.frame.size.height;
	}else if (gestureRecognizer == _down_left_touch) {
		_down_left_begin_point_x = down_left.center.x;
		_down_left_begin_point_y = down_left.center.y;
		curretn_width = self.frame.size.width;
		current_height = self.frame.size.height;
	}else if (gestureRecognizer == _down_right_touch) {
		_down_right_begin_point_x = down_right.center.x;
		_down_right_begin_point_y = down_right.center.y;
		curretn_width = self.frame.size.width;
		current_height = self.frame.size.height;
	}
	return YES;
}


- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event{
	isNotBound = YES;
	NSLog(@"begin");
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event{
	NSLog(@"move");
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event{
	NSLog(@"end");
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event{
	NSLog(@"cancel");
}


- (void)dealloc {
    [super dealloc];
}


@end
