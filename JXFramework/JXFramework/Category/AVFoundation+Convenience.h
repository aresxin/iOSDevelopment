//
//  AVFoundation+Convenience.h
//  OpenGLES
//
//  Created by CN40436 on 15-1-16.
//  Copyright (c) 2015年 NHN China. All rights reserved.
//

#import <AVFoundation/AVFoundation.h>
#import <UIKit/UIKit.h>
#import <AssetsLibrary/AssetsLibrary.h>

@interface AVAsset (Convenience)

- (AVAssetTrack *)firstVideoTrack;
- (AVAssetTrack *)firstAudioTrack;

+ (void)setTimeScale:(NSInteger)scale;
+ (int32_t)defaultTimeScale;
@end

@interface AVCaptureDevice (Convenience)

+ (BOOL)hasFrontCamera;

- (BOOL)isFlashEnabled;
- (BOOL)isFocusEnabled;

+ (BOOL)isCameraEnabel;

+ (BOOL)isAlbumEnabel;

@end

@interface UIImage (Sample)

+ (UIImage *)imageWithSampleBuffer:(CMSampleBufferRef)sampleBuffer;
@end

CGFloat CMTimeRangeGetProgressForTime(CMTimeRange range, CMTime time);
NSInteger CMTimeGetFrameIndex(CMTime time);
CMTime CMTimeMakeWithFrameIndex(NSInteger index);
BOOL CMTimeEqualToTime(CMTime time1, CMTime time2);
BOOL CMTimeLaterToTime(CMTime time1, CMTime time2);

extern NSString *const kAssetLoadValueKeyDuration;
extern NSString *const kAssetLoadValueKeyTracks;
extern NSTimeInterval const kAssetLoadRunloopInterval;
