//
//  AVFoundation+Convenience.m
//  OpenGLES
//
//  Created by CN40436 on 15-1-16.
//  Copyright (c) 2015年 NHN China. All rights reserved.
//

#import "AVFoundation+Convenience.h"

NSString *const kAssetLoadValueKeyDuration = @"duration";
NSString *const kAssetLoadValueKeyTracks = @"tracks";
NSTimeInterval const kAssetLoadRunloopInterval = 0.1f;
int32_t const kAssetTimeScaleDefault = 30;
static int32_t kAssetTimeScale = kAssetTimeScaleDefault;

@implementation AVAsset (Convenience)

- (AVAssetTrack *)firstVideoTrack;
{
    NSArray *tracks = [self tracksWithMediaType:AVMediaTypeVideo];
    if (tracks.count == 0) {
        return nil;
    }
    
    return [tracks firstObject];
}

- (AVAssetTrack *)firstAudioTrack;
{
    NSArray *tracks = [self tracksWithMediaType:AVMediaTypeAudio];
    if (tracks.count == 0) {
        return nil;
    }
    
    return [tracks firstObject];
}

+ (void)setTimeScale:(NSInteger)scale;
{
    kAssetTimeScale = (int32_t)scale;
}

+ (int32_t)defaultTimeScale;
{
    return kAssetTimeScale;
}
@end

@implementation AVCaptureDevice (Convenience)

+ (BOOL)hasFrontCamera;
{
    static BOOL firstTime = YES;
    static BOOL hasFrontCamera = NO;
    
    if (firstTime) {
        // get all cameras
        NSArray *videoDevices = [AVCaptureDevice devicesWithMediaType:AVMediaTypeVideo];
        for (AVCaptureDevice *device in videoDevices) {
            if (device.position == AVCaptureDevicePositionFront) {
                hasFrontCamera = YES;
                break;
            }
        }
        firstTime = NO;
    }
    return hasFrontCamera;
}

- (BOOL)isFlashEnabled;
{
    if (![self hasFlash]) {
        return NO;
    }
    
    if (![self isFlashAvailable]) {
        return NO;
    }
    
    if ([self isFlashModeSupported:AVCaptureFlashModeOn]) {
        return YES;
    }
    return NO;
}
- (BOOL)isFocusEnabled;
{
    if (![self isFocusModeSupported:AVCaptureFocusModeAutoFocus]) {
        return NO;
    }
    
    if (![self isFocusPointOfInterestSupported]) {
        return NO;
    }
    return YES;
}

+ (BOOL) isCameraEnabel
{
    AVAuthorizationStatus authStatus = [AVCaptureDevice authorizationStatusForMediaType:AVMediaTypeVideo];
    if (authStatus == AVAuthorizationStatusRestricted || authStatus == AVAuthorizationStatusDenied)
    {
        return NO;
    }
    
    return YES;
}

+ (BOOL) isAlbumEnabel
{
    ALAuthorizationStatus author = [ALAssetsLibrary authorizationStatus];
    if (author == ALAuthorizationStatusRestricted || author == ALAuthorizationStatusDenied)
    {
        //无权限
        return NO;
    }
    
    return YES;
}

@end


@implementation UIImage (Sample)

+ (UIImage *)imageWithSampleBuffer:(CMSampleBufferRef)sampleBuffer;
{
    CVImageBufferRef imageBuffer = CMSampleBufferGetImageBuffer(sampleBuffer);
    size_t width = CVPixelBufferGetWidth(imageBuffer);
    size_t height = CVPixelBufferGetHeight(imageBuffer);
    CGRect cropRect = CGRectMake(0, 0, width, height);
    CIImage *ciImage = [CIImage imageWithCVPixelBuffer:imageBuffer];
    CIImage *cropedImage = [ciImage imageByCroppingToRect:cropRect];
    
    CGAffineTransform rotation = CGAffineTransformMakeRotation(-M_PI_2);
    CIImage *rotatedImage = [cropedImage imageByApplyingTransform:rotation];
    return [UIImage imageWithCIImage:rotatedImage];
}
@end

CGFloat CMTimeRangeGetProgressForTime(CMTimeRange range, CMTime time)
{
    // check start
    CMTime start = range.start;
    if (CMTimeEqualToTime(start, time)) {
        return 0.0f;
    }
    
    // check end
    CMTime end = CMTimeRangeGetEnd(range);
    if (CMTimeEqualToTime(end, time)) {
        return 1.0;
    }
    
    // check range
    if (CMTimeCompare(start, time) > 0) {
        
        return 0.0f;
    }
    if (CMTimeCompare(time, end) > 0) {
       
        return 1.0f;
    }
    
    if (!CMTimeRangeContainsTime(range, time)) {
        return 0.0f;
    }
    
    CMTimeRange passedRange = CMTimeRangeFromTimeToTime(range.start, time);
    CGFloat duration = CMTimeGetSeconds(passedRange.duration);
    CGFloat totalDuration = CMTimeGetSeconds(range.duration);
    if (totalDuration != 0.0) {
        return duration/totalDuration;
    }
    return 0.0;
}

NSInteger CMTimeGetFrameIndex(CMTime time)
{
    Float64 second = CMTimeGetSeconds(time);
    CMTime convertedTime = CMTimeMakeWithSeconds(second, kAssetTimeScale);
    return (NSInteger)convertedTime.value;
}

CMTime CMTimeMakeWithFrameIndex(NSInteger index)
{
    return CMTimeMake(index, kAssetTimeScale);
}

BOOL CMTimeEqualToTime(CMTime time1, CMTime time2)
{
    if (CMTimeCompare(time1, time2) == 0) {
        return YES;
    }
    return NO;
}

BOOL CMTimeLaterToTime(CMTime time1, CMTime time2)
{
    // -1: time1 < time2
    //  0: time1 = time2
    //  1: time1 > time2
    if (CMTimeCompare(time1, time2) > 0) {
        return YES;
    }
    return NO;
}
