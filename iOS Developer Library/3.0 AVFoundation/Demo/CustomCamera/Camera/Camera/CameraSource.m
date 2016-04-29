//
//  CameraSource.m
//  Camera
//
//  Created by yangjinxin on 15/2/28.
//  Copyright (c) 2015年 yangjinxin. All rights reserved.
//

#import "CameraSource.h"
@interface CameraSource ()
@property (nonatomic) AVCaptureSession *session;
@property (nonatomic) AVCaptureDevice *videoDevice;
@property (nonatomic, strong)       AVCaptureStillImageOutput   * stillImageOutput;
@end

@implementation CameraSource

+ (instancetype)cameraWithPosition:(AVCaptureDevicePosition)position delegate:(id<CameraSourceDelegate>)delegate
{
    return [[CameraSource alloc] initWithPosition:position delegate:delegate];
}

- (instancetype)initWithPosition:(AVCaptureDevicePosition)position delegate:(id<CameraSourceDelegate>)delegate
{
    self = [super init];
    if (self) {
        
        if (position == AVCaptureDevicePositionBack) {
            _backCameraActive = YES;
        } else {
            _backCameraActive = NO;
        }
        
        
        _flashActive = NO;
        
        // create AVCaptureSession
        AVCaptureSession *session = [[AVCaptureSession alloc] init];
        if ([session canSetSessionPreset:AVCaptureSessionPresetHigh]) {
            [session setSessionPreset:AVCaptureSessionPresetHigh];
        } else {
            [session setSessionPreset:AVCaptureSessionPresetMedium];
        };
        
        self.session = session;
        
        
        self.stillImageOutput = [[AVCaptureStillImageOutput alloc] init];
        NSDictionary * outputSettings = [[NSDictionary alloc] initWithObjectsAndKeys:AVVideoCodecJPEG,AVVideoCodecKey, nil];
        //这是输出流的设置参数AVVideoCodecJPEG参数表示以JPEG的图片格式输出图片
        [self.stillImageOutput setOutputSettings:outputSettings];
        if ([self.session canAddOutput:self.stillImageOutput]) {
            [self.session addOutput:self.stillImageOutput];
        }
        
        // Reload capture devices.
        [self addVideoDevice];
    }
    return self;
}

- (BOOL)addVideoDevice
{
    AVCaptureSession *session = self.session;
    
    NSArray *devices = [AVCaptureDevice devicesWithMediaType:AVMediaTypeVideo];
    AVCaptureDevicePosition proposedPosition;
    // video
    if (_backCameraActive) {
        proposedPosition = AVCaptureDevicePositionBack;
    } else {
        proposedPosition = AVCaptureDevicePositionFront;
    }
    
    AVCaptureDevice *proposedDevice = nil;
    for (AVCaptureDevice *device in devices) {
        if (device.position == proposedPosition) {
            proposedDevice = device;
            break;
        }
    }
    if (!proposedDevice) {
        
        return NO;
    }
    
    NSError *error = nil;
    AVCaptureDeviceInput *input = [AVCaptureDeviceInput deviceInputWithDevice:proposedDevice error:&error];
    if (input) {
        // trying to add this device.
        if ([session canAddInput:input]) {
            [session addInput:input];
            
            // set video device
            self.videoDevice = proposedDevice;
            
            NSError *error = nil;
            if ([proposedDevice lockForConfiguration:&error]) {
                // set low light boost
                if ([proposedDevice isLowLightBoostSupported]) {
                    proposedDevice.automaticallyEnablesLowLightBoostWhenAvailable = YES;
                }
                
                // on
                if ([self isFlashActive]) {
                    // set flash
                    if ([proposedDevice isFlashModeSupported:AVCaptureFlashModeOn]) {
                        [proposedDevice setFlashMode:AVCaptureFlashModeOn];
                    }
                    
                    // set torch
                    if ([proposedDevice isTorchModeSupported:AVCaptureTorchModeOn]) {
                        [proposedDevice setTorchMode:AVCaptureTorchModeOn];
                    }
                    
                    // off
                } else {
                    // set flash
                    if ([proposedDevice isFlashModeSupported:AVCaptureFlashModeOff]) {
                        [proposedDevice setFlashMode:AVCaptureFlashModeOff];
                    }
                    
                    // set torch
                    if ([proposedDevice isTorchModeSupported:AVCaptureTorchModeOff]) {
                        [proposedDevice setTorchMode:AVCaptureTorchModeOff];
                    }
                }
                
                // set focus
                if ([proposedDevice isFocusModeSupported:AVCaptureFocusModeContinuousAutoFocus]) {
                    [proposedDevice setFocusMode:AVCaptureFocusModeContinuousAutoFocus];
                }
                if ([proposedDevice isFocusPointOfInterestSupported]) {
                    [proposedDevice setFocusPointOfInterest:CGPointMake(0.5f, 0.5f)];
                }
                
                // set expose
                if ([proposedDevice isExposureModeSupported:AVCaptureExposureModeContinuousAutoExposure]) {
                    [proposedDevice setExposureMode:AVCaptureExposureModeContinuousAutoExposure];
                }
                if ([proposedDevice isExposurePointOfInterestSupported]) {
                    [proposedDevice setExposurePointOfInterest:CGPointMake(0.5f, 0.5f)];
                }
                
                [proposedDevice unlockForConfiguration];
            } else {
                //WriteError(error, @"Set Properties For Current Camera");
            }
            
            return YES;
        } else {
            //WriteWarning(@"Can't add the proposed video device to current capture session.");
        }
    } else {
        //WriteError(error, @"Create Capture Device Input For Video");
    }
    
    return NO;
}



- (void)setFlashActive:(BOOL)flashActive
{
    if (_flashActive == flashActive) {
        return;
    }
    
    if (!_videoDevice) {
        return;
    }
    
    _flashActive = flashActive;
    NSError *error = nil;
    if ([_videoDevice lockForConfiguration:&error]) {
        
        // on
        if (_flashActive) {
            // set flash
            if ([_videoDevice isFlashModeSupported:AVCaptureFlashModeOn]) {
                [_videoDevice setFlashMode:AVCaptureFlashModeOn];
            }
            
            // set torch
            if ([_videoDevice isTorchModeSupported:AVCaptureTorchModeOn]) {
                [_videoDevice setTorchMode:AVCaptureTorchModeOn];
            }
            
            // off
        } else {
            // set flash
            if ([_videoDevice isFlashModeSupported:AVCaptureFlashModeOff]) {
                [_videoDevice setFlashMode:AVCaptureFlashModeOff];
            }
            
            // set torch
            if ([_videoDevice isTorchModeSupported:AVCaptureTorchModeOff]) {
                [_videoDevice setTorchMode:AVCaptureTorchModeOff];
            }
        }
        
        [_videoDevice unlockForConfiguration];
    } else {
        
    }

}

- (void)setBackCameraActive:(BOOL)active
{
    if (_backCameraActive == active) {
        return;
    }
    AVCaptureDevicePosition position;
    
    _backCameraActive = active;
    
    if (!_videoDevice) {
        return;
    }
    
    if (active) {
        position = AVCaptureDevicePositionBack;
    } else {
        position = AVCaptureDevicePositionFront;
    }
    if (_videoDevice.position != position) {
        AVCaptureSession *session = self.session;
        for (AVCaptureDeviceInput *input in session.inputs) {
            if (_videoDevice == input.device) {
                [session beginConfiguration];
                [session removeInput:input];
                [session commitConfiguration];
                break;
            }
        }
        
        [self addVideoDevice];
    }
}

- (BOOL)isRunning
{
    if ([self.session isRunning]) {
        return YES;
    }
    return NO;
}

- (void)startRunning
{
    if ([self.session isRunning]) {
        return;
    }
    
    [self.session startRunning];
}

- (void)endRunning
{
    if ([self.session isRunning]) {
        [self.session stopRunning];
    }
}

- (void) shutterCamera
{
    AVCaptureConnection * videoConnection = [self.stillImageOutput connectionWithMediaType:AVMediaTypeVideo];
    if (!videoConnection) {
        NSLog(@"take photo failed!");
        return;
    }
    
    [self.stillImageOutput captureStillImageAsynchronouslyFromConnection:videoConnection completionHandler:^(CMSampleBufferRef imageDataSampleBuffer, NSError *error) {
        if (imageDataSampleBuffer == NULL) {
            return;
        }
        NSData * imageData = [AVCaptureStillImageOutput jpegStillImageNSDataRepresentation:imageDataSampleBuffer];
        UIImage * image = [UIImage imageWithData:imageData];
        NSLog(@"image size = %@",NSStringFromCGSize(image.size));
        
    }];
}
@end


@implementation CameraPreviewView

+ (Class)layerClass
{
    return [AVCaptureVideoPreviewLayer class];
}

- (AVCaptureSession *)session
{
    return [(AVCaptureVideoPreviewLayer *)[self layer] session];
}

- (void)setSession:(AVCaptureSession *)session
{
    [(AVCaptureVideoPreviewLayer *)[self layer] setSession:session];
}


- (void) setCameraSource:(CameraSource *)cameraSource
{
    if (_cameraSource == cameraSource) {
        return;
    }
    
    _cameraSource = cameraSource;
    AVCaptureVideoPreviewLayer *previewLayer = (AVCaptureVideoPreviewLayer *)self.layer;
    previewLayer.session = cameraSource.session;
    AVCaptureConnection *connection = [previewLayer connection];
    connection.videoOrientation = AVCaptureVideoOrientationPortrait;
    previewLayer.videoGravity = AVLayerVideoGravityResizeAspectFill;
}


@end