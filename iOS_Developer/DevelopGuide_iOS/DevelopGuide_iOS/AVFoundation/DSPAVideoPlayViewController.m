//
//  DSPAVideoPlayViewController.m
//  DevelopGuide_iOS
//
//  Created by yangjinxin on 13-8-2.
//
//

#import "DSPAVideoPlayViewController.h"

@interface DSPAVideoPlayViewController ()

@end

@implementation DSPAVideoPlayViewController

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
	// Do any additional setup after loading the view.
    self.view.backgroundColor = [UIColor redColor];
    [self play];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark - 
#pragma makk init
- (id) initWithFrame:(CGRect)frame withVideoURL:(NSURL *)videoUrl
{
    self = [super init];
    if (self) {
        // Custom initialization
        self.view.frame = frame;
        videoURL_       = videoUrl;
        
        
        
    }
    return self;
}

- (id) initWithFrame:(CGRect)frame videlURLs:(NSArray *)videoUrls
{
    return self;
}

#pragma mark -
#pragma makk play video
- (void) play
{
    
    NSString *videoURL = [[NSBundle mainBundle] pathForResource:@"Movie" ofType:@"m4v"];
	AVAsset *asset = [[AVURLAsset alloc] initWithURL:[NSURL fileURLWithPath:videoURL] options:nil];
    AVPlayerItem *playerItem = [AVPlayerItem playerItemWithAsset:asset];
    
    CGFloat totalMovieDuration = (CGFloat)playerItem.duration.value / playerItem.duration.timescale;
    
    //playerItem.reversePlaybackEndTime =  CMTimeMakeWithSeconds(1200, 600);
    //[playerItem seekToTime: CMTimeMake(20, 1)];
    //CMTime previewCMTime = CMTimeMake(previewSeconds, 1);
    avPlayer_       = [[AVPlayer alloc] initWithPlayerItem:playerItem];
    videoPlayer_    = [AVPlayerLayer playerLayerWithPlayer:avPlayer_];
    videoPlayer_.videoGravity = AVLayerVideoGravityResizeAspect;
    videoPlayer_.frame        = self.view.bounds;
    videoPlayer_.backgroundColor = [UIColor yellowColor].CGColor;
    [self.view.layer addSublayer:videoPlayer_];
    
    //[avPlayer_ play];

}

- (void) playMultiple
{
    
}

@end
