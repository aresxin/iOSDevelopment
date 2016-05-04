//
//  CoreAnimationTestController.m
//  DevelopGuide_iOS
//
//  Created by xin on 12-5-21.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "CoreAnimationTestController.h"
#import "ColoredTextLayer.h"

@implementation CoreAnimationTestController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)didReceiveMemoryWarning
{
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

#pragma mark - View lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
      self.navigationController.toolbar.hidden = YES;
    
    
    UIFont *font = [UIFont systemFontOfSize:18];
    NSArray *colors = [NSArray arrayWithObjects:[UIColor yellowColor],[UIColor redColor],nil];
    NSArray *strArr = [NSArray arrayWithObjects:@"abcd",@"opqei", nil];
    ColoredTextLayer *layer = [[ColoredTextLayer alloc] init];
    layer.frame = CGRectMake(50, 200, 300, 100);
    [layer setTexts:strArr
           inColors:colors
           withFont:font
          lineSpace:2
          wordSpace:1 ];
    [self.view.layer addSublayer:layer];
    [layer release];
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}


- (IBAction)buttonPressed1: (id)sender
{
    CGPoint fromPoint = _imgView.center;
    
    //路径曲线
    UIBezierPath *movePath = [UIBezierPath bezierPath];
    [movePath moveToPoint:fromPoint];
    CGPoint toPoint = CGPointMake(300, 460);
    [movePath addQuadCurveToPoint:toPoint
                     controlPoint:CGPointMake(toPoint.x,fromPoint.y)];
    
    //关键帧
    CAKeyframeAnimation *moveAnim = [CAKeyframeAnimation animationWithKeyPath:@"position"];
    moveAnim.path = movePath.CGPath;
    moveAnim.removedOnCompletion = YES;
    
    //scale变化
    CABasicAnimation *scaleAnim = [CABasicAnimation animationWithKeyPath:@"transform"];
    scaleAnim.fromValue = [NSValue valueWithCATransform3D:CATransform3DIdentity];
    //x，y轴缩小到0.1,Z 轴不变
    scaleAnim.toValue = [NSValue valueWithCATransform3D:CATransform3DMakeScale(0.1, 0.1, 1.0)];
    scaleAnim.removedOnCompletion = YES;
    
    //透明度变化
    CABasicAnimation *opacityAnim = [CABasicAnimation animationWithKeyPath:@"alpha"];
    opacityAnim.fromValue = [NSNumber numberWithFloat:1.0];
    opacityAnim.toValue = [NSNumber numberWithFloat:0.1];
    opacityAnim.removedOnCompletion = YES;
    
    //旋转变化
    CABasicAnimation *rotationAnim = [CABasicAnimation animationWithKeyPath:@"transform"];
    rotationAnim.fromValue = [NSValue valueWithCATransform3D:CATransform3DIdentity];
    
    //沿Z轴旋转
    rotationAnim.toValue = [NSValue valueWithCATransform3D: CATransform3DMakeRotation(M_PI,0,0,1)];
    
    //沿Y轴旋转
    // scaleAnim.toValue = [NSValue valueWithCATransform3D: CATransform3DMakeRotation(M_PI,0,1.0,0)];
    
    //沿X轴旋转
    // scaleAnim.toValue = [NSValue valueWithCATransform3D: CATransform3DMakeRotation(M_PI,1.0,0,0)];
    rotationAnim.cumulative = YES;
    rotationAnim.duration =1;
    //旋转2遍，360度    
    rotationAnim.repeatCount =2;
    
    //关键帧，scale,透明度,旋转组合起来执行
    CAAnimationGroup *animGroup = [CAAnimationGroup animation];
    animGroup.animations = [NSArray arrayWithObjects:moveAnim, scaleAnim,opacityAnim, nil];
    animGroup.duration = 1;
    //animGroup.autoreverses = YES;
    [_imgView.layer addAnimation:animGroup forKey:nil];
}


// 旋转layer
- (IBAction)buttonPressed2: (id)sender;
{
    CABasicAnimation *scaleAnim = [CABasicAnimation animationWithKeyPath:@"transform"];
    //CATransform3DIdentity当前默认矩阵
    scaleAnim.fromValue = [NSValue valueWithCATransform3D:CATransform3DIdentity];
    
    CATransform3D transform;
    if (arc4random() % 2 == 1)
        transform = CATransform3DMakeRotation(-1.10, 0, 0, 1.0);  
    else
        transform = CATransform3DMakeRotation(1.10, 0, 0, 1.0);  
    //沿Z轴旋转 旋转90度参数为 （90*M_PI/180）
    //scaleAnim.toValue = [NSValue valueWithCATransform3D:CATransform3DMakeRotation(-180,0,0,1.0)];
    
	
	scaleAnim.toValue = [NSValue valueWithCATransform3D:transform];
	
    //沿Y轴旋转
    // scaleAnim.toValue = [NSValue valueWithCATransform3D: CATransform3DMakeRotation(M_PI,0,1.0,0)];
    
    //沿X轴旋转
    // scaleAnim.toValue = [NSValue valueWithCATransform3D: CATransform3DMakeRotation(M_PI,1.0,0,0)];
    scaleAnim.cumulative = YES;
    scaleAnim.duration =0.6;
    
    
    //scaleAnim.autoreverses = YES;
    
    scaleAnim.repeatCount = 10000;
    scaleAnim.removedOnCompletion = YES;
    
    [_imgView.layer addAnimation:scaleAnim forKey:nil];
}
- (IBAction)buttonPressed3: (id)sender
{
    
#if 0
    CGPoint fromPoint = _imgView.center;
    
    //路径曲线
    UIBezierPath *movePath = [UIBezierPath bezierPath];
    [movePath moveToPoint:fromPoint];
    CGPoint toPoint = CGPointMake(300, 460);
    [movePath addLineToPoint:toPoint];
//    [movePath addQuadCurveToPoint:toPoint
//                     controlPoint:CGPointMake(toPoint.x,fromPoint.y)];
    
    //关键帧
    CAKeyframeAnimation *moveAnim = [CAKeyframeAnimation animationWithKeyPath:@"position"];
    moveAnim.path = movePath.CGPath;
    moveAnim.removedOnCompletion = YES;
#else
    CABasicAnimation *moveAnim = [CABasicAnimation animationWithKeyPath:@"position"];
    moveAnim.fromValue = [NSValue valueWithCGPoint:_imgView.center];
    moveAnim.toValue = [NSValue valueWithCGPoint:CGPointMake(320, 480)];
    // 动画重复的次数
    moveAnim.repeatCount =2;
    // 动画从开始点fromValue到结束点toValue ，在从结束点toValue到开始点fromValue逆着播放
    moveAnim.autoreverses = YES; 
    moveAnim.removedOnCompletion = YES;
    moveAnim.duration = 2.0;
#endif
    [_imgView.layer addAnimation:moveAnim forKey:nil];
}
- (IBAction)buttonPressed4: (id)sender
{
    //透明度变化
    CABasicAnimation *opacityAnim = [CABasicAnimation animationWithKeyPath:@"alpha"];
    opacityAnim.fromValue = [NSNumber numberWithFloat:1.0];
    opacityAnim.toValue = [NSNumber numberWithFloat:0.1];
    //opacityAnim.repeatCount =2;
    opacityAnim.removedOnCompletion = YES;
    [_imgView.layer addAnimation:opacityAnim forKey:nil];
}

- (IBAction)buttonPressed5: (id)sender
{
    //水波纹动画
    [_imgView removeFromSuperview];
    [self.view addSubview:_imgView];
    CATransition *animation = [CATransition animation];
    animation.duration = 0.3f;
    animation.removedOnCompletion = YES;
    animation.type = @"rippleEffect";
    [[_imgView layer] addAnimation:animation forKey:@"cameraOpen"];
    
    /*
    CATransition *transition = [CATransition animation];
    
    transition.duration = 0.3f;
    
    transition.timingFunction = [CAMediaTimingFunction functionWithName:kCAMediaTimingFunctionLinear];
    
    transition.type = kCATransitionPush;
    
    transition.subtype = kCATransitionFromRight;
    
    transition.delegate = self;
    
    [_imgView.layer addAnimation:transition forKey:nil];
    */
    
    
    //[self.view addSubview:_imgView];
    


}

@end
