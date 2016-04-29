//
//  CameraSource.h
//  Camera
//
//  Created by yangjinxin on 15/2/28.
//  Copyright (c) 2015年 yangjinxin. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import <UIKit/UIKit.h>

@protocol CameraSourceDelegate <NSObject>

@optional
// a new camera device had been added to current session.
- (void)videoDeviceDidAddToSession:(NSDictionary *)deviceInfo;

// capture session become to running.
- (void)cameraDidBecomeRunning:(BOOL)running;

// focus succeed
- (void)focusDidFinished;

// a still image is generated with currently actived camera.
- (void)stillImageDidCaptured;
- (void)didCaptureStillImage:(UIImage *)stillImage;
@end



@interface CameraSource : NSObject

/**
 Determines whether the back camera is currently actived.
 Default is YES.
 */
@property (nonatomic, readwrite, getter=isBackCameraActive) BOOL backCameraActive;

/**
 Determines whether the flash is active.
 */
@property (nonatomic, getter=isFlashActive) BOOL flashActive;


@property (nonatomic, readonly) AVCaptureSession *session;

+ (instancetype)cameraWithPosition:(AVCaptureDevicePosition)position delegate:(id<CameraSourceDelegate>)delegate;

- (instancetype)initWithPosition:(AVCaptureDevicePosition)position delegate:(id<CameraSourceDelegate>)delegate;

/**
 Returns YES if camera is running.
 */
- (BOOL)isRunning;

/**
 Start recording.
 */
- (void)startRunning;
- (void)endRunning;
- (void) shutterCamera;
@end



@interface CameraPreviewView : UIView

/**
 CameraSource
 */
@property (nonatomic) CameraSource *cameraSource;

@end



