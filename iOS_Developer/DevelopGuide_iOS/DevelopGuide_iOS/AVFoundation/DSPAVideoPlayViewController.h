//
//  DSPAVideoPlayViewController.h
//  DevelopGuide_iOS
//
//  Created by yangjinxin on 13-8-2.
//
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>
#import <MediaPlayer/MediaPlayer.h>
#import <CoreMedia/CoreMedia.h>
@interface DSPAVideoPlayViewController : UIViewController {
    NSURL           *videoURL_;
    NSArray         *videoURLs_;
    AVPlayerLayer   *videoPlayer_;
    AVPlayer        *avPlayer_;
    AVQueuePlayer   *avQueuePlayer_;
}

#pragma mark -
#pragma makk init
- (id) initWithFrame:(CGRect)frame withVideoURL:(NSURL *)videoUrl;
- (id) initWithFrame:(CGRect)frame videlURLs:(NSArray *)videoUrls;

#pragma mark -
#pragma makk play video
- (void) play;
- (void) playMultiple;
@end
