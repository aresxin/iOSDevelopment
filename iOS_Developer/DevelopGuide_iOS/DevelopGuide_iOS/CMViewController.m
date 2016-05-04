//
//  CMViewController.m
//  CoreMotionTest
//
//  Created by qwe on 12-4-10.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//
/*
 *Core Motion 获取设备的旋转,位置,加速度等信息
 */

#import "CMViewController.h"

@interface CMViewController ()
- (void) startMotion;
- (void) stopMotion;
@end

@implementation CMViewController
@synthesize motionManager;
@synthesize queue;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    self.view.backgroundColor = [UIColor scrollViewTexturedBackgroundColor];
    // Do any additional setup after loading the view from its nib.
    
    self.motionManager = [[[CMMotionManager alloc] init] autorelease];
    motionManager.deviceMotionUpdateInterval = 1.0 / 10.0; 
    [motionManager startDeviceMotionUpdates];
    if (motionManager.deviceMotionAvailable ) 
    {
        timer = [NSTimer scheduledTimerWithTimeInterval:0.2f target:self
                                               selector:@selector(updateView:) userInfo:nil
                                                repeats:YES];
    }
    else 
    {
        [motionManager stopDeviceMotionUpdates];
        self.motionManager = nil;
    }
    
    
    UIAccelerometer *accelerometer = [UIAccelerometer sharedAccelerometer]; 
    accelerometer.updateInterval = 0.2f; 
    accelerometer.delegate = self;
}

- (void)viewDidUnload
{
    [timer invalidate];
    [motionManager stopDeviceMotionUpdates]; 
    [motionManager release];
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

- (void) dealloc
{
    [motionManager release];
    [queue release];
    [super dealloc];
}


-(void) updateView:(NSTimer *)timer {
    CMDeviceMotion *motionData = motionManager.deviceMotion;
    CMAttitude *attitude = motionData.attitude;
    CMAcceleration gravity = motionData.gravity;
    CMAcceleration userAcceleration = motionData.userAcceleration; 
    CMRotationRate rotate = motionData.rotationRate;
    NSTimeInterval motion = motionManager.deviceMotionUpdateInterval;
    
    CMAccelerometerData *acceler = motionManager.accelerometerData;
    
    yawLabel.text = [NSString stringWithFormat:@"%2.2f",attitude.yaw];
    pitchLabel.text = [NSString stringWithFormat:@"%2.2f",attitude.pitch];
    rollLabel.text = [NSString stringWithFormat:@"%2.2f",attitude.roll];
    
    accelIndicatorX.progress = ABS(userAcceleration.x);
    accelIndicatorY.progress = ABS(userAcceleration.y); 
    accelIndicatorZ.progress = ABS(userAcceleration.z);
    accelLabelX.text = [NSString stringWithFormat:@"%2.2f",userAcceleration.x];
    accelLabelY.text = [NSString stringWithFormat:@"%2.2f",userAcceleration.y]; 
    accelLabelZ.text = [NSString stringWithFormat:@"%2.2f",userAcceleration.z];
    
    gravityIndicatorX.progress = ABS(gravity.x);
    gravityIndicatorY.progress = ABS(gravity.y); 
    gravityIndicatorZ.progress = ABS(gravity.z);
    gravityLabelX.text = [NSString stringWithFormat:@"%2.2f",gravity.x];
    gravityLabelY.text = [NSString stringWithFormat:@"%2.2f",gravity.y];
    gravityLabelZ.text = [NSString stringWithFormat:@"%2.2f",gravity.z];
    
    
    rotIndicatorX.progress = ABS(rotate.x); 
    rotIndicatorY.progress = ABS(rotate.y);
    rotIndicatorZ.progress = ABS(rotate.z);
    rotLabelX.text = [NSString stringWithFormat:@"%2.2f",rotate.x];
    rotLabelY.text = [NSString stringWithFormat:@"%2.2f",rotate.y]; 
    rotLabelZ.text = [NSString stringWithFormat:@"%2.2f",rotate.z];
}


- (void)accelerometer:(UIAccelerometer *)meter didAccelerate:(UIAcceleration *)acceleration {
    rawAccelLabelX.text = [NSString stringWithFormat:@"%2.2f", acceleration.x]; 
    rawAccelIndicatorX.progress = ABS(acceleration.x);
    rawAccelLabelY.text = [NSString stringWithFormat:@"%2.2f", acceleration.y];
    rawAccelIndicatorY.progress = ABS(acceleration.y);
    rawAccelLabelZ.text =[NSString stringWithFormat:@"%2.2f", acceleration.z]; 
    rawAccelIndicatorZ.progress = ABS(acceleration.z);
}

- (void) startMotion
{
    self.motionManager = [[[CMMotionManager alloc] init] autorelease];
    motionManager.deviceMotionUpdateInterval = 1.0/60.0;
    if (motionManager.deviceMotionAvailable ) 
    {
        self.queue = [NSOperationQueue currentQueue];
        [motionManager startDeviceMotionUpdatesToQueue:queue
                                           withHandler:^ (CMDeviceMotion *motionData, NSError *error) 
        {
            CMAttitude *attitude = motionData.attitude;
            CMAcceleration gravity = motionData.gravity;
            CMAcceleration userAcceleration = motionData.userAcceleration;
            CMRotationRate rotate = motionData.rotationRate;
            // handle data here......
        }];
    }
    else 
    {
        [motionManager release]; 
    }
}

- (void) stopMotion
{
    [motionManager stopDeviceMotionUpdates];
}
@end
