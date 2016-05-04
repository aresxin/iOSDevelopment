//
//  DSPAVideoPlayView.m
//  DevelopGuide_iOS
//
//  Created by yangjinxin on 13-8-2.
//
//
#import "DSPAVideoPlayView.h"

@interface DSPAVideoPlayView ()
- (void) setPlayer:(AVPlayer *)thePlayer;
- (void) initVideoPlayNow:(BOOL)playNow;
@end

@implementation DSPAVideoPlayView
@synthesize videoURL    = videoURL_;
@synthesize videoPlayer = videoPlayer_;

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
    }
    return self;
}


- (id) initWithFrame:(CGRect)frame
        withVideoURL:(NSURL *)videoUrl
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
        self.videoURL = videoUrl;
    }
    return self;
}


- (id) initWithFrame:(CGRect)frame
        withVideoURL:(NSURL *)videoUrl
             playNow:(BOOL)isPlayNow
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
        self.videoURL = videoUrl;
        [self initVideoPlayNow:isPlayNow];
    }
    return self;
}

// chang view layer
+ (Class)layerClass {
    return [AVPlayerLayer class];
}

- (void) initVideoPlayNow:(BOOL)playNow
{
	AVAsset *asset = [[AVURLAsset alloc] initWithURL:self.videoURL
                                             options:nil];
    AVPlayerItem *playerItem = [AVPlayerItem playerItemWithAsset:asset];
    
    CGFloat totalMovieDuration = (CGFloat)playerItem.duration.value / playerItem.duration.timescale;
    NSLog(@"totalMovieDuration is %f",totalMovieDuration);
    
    videoPlayer_            = [[AVPlayer alloc] initWithPlayerItem:playerItem];
    [self setPlayer:videoPlayer_];
    
    if (playNow)
    {
        [self play];
    }
}


- (void) setPlayer:(AVPlayer *)thePlayer
{
    [(AVPlayerLayer*)self.layer setPlayer:thePlayer];
}

#pragma mark -
#pragma mark video operation
- (void) play
{
    [videoPlayer_ play];
}

- (void) pause
{
    [videoPlayer_ pause];
}

@end
