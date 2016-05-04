//
//  CMViewController.h
//  CoreMotionTest
//
//  Created by qwe on 12-4-10.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <CoreMotion/CoreMotion.h>

@interface CMViewController : UIViewController <UIAccelerometerDelegate>{
    CMMotionManager *motionManager;
    NSOperationQueue *queue;
    NSTimer *timer;
    
    IBOutlet UILabel *yawLabel;
    IBOutlet UILabel *pitchLabel;
    IBOutlet UILabel *rollLabel;
    
    IBOutlet UIProgressView *accelIndicatorX;
    IBOutlet UIProgressView *accelIndicatorY;
    IBOutlet UIProgressView *accelIndicatorZ;
    IBOutlet UILabel *accelLabelX;
    IBOutlet UILabel *accelLabelY;
    IBOutlet UILabel *accelLabelZ;
    
    IBOutlet UIProgressView *gravityIndicatorX;
    IBOutlet UIProgressView *gravityIndicatorY; 
    IBOutlet UIProgressView *gravityIndicatorZ; 
    IBOutlet UILabel *gravityLabelX;
    IBOutlet UILabel *gravityLabelY;
    IBOutlet UILabel *gravityLabelZ;
    
    
    IBOutlet UIProgressView *rotIndicatorX; 
    IBOutlet UIProgressView *rotIndicatorY;
    IBOutlet UIProgressView *rotIndicatorZ;
    IBOutlet UILabel *rotLabelX;
    IBOutlet UILabel *rotLabelY;
    IBOutlet UILabel *rotLabelZ;
    
    
    IBOutlet UILabel *rawAccelLabelX;
    IBOutlet UIProgressView *rawAccelIndicatorX;
    IBOutlet UILabel *rawAccelLabelY;
    IBOutlet UIProgressView *rawAccelIndicatorY;
    IBOutlet UILabel *rawAccelLabelZ;
    IBOutlet UIProgressView *rawAccelIndicatorZ;

}
@property (nonatomic, retain) CMMotionManager *motionManager;
@property (nonatomic, retain) NSOperationQueue *queue;
@end
