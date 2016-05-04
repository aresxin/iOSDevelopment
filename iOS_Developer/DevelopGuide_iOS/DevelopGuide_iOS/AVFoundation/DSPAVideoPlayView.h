//
//  DSPAVideoPlayView.h
//  DevelopGuide_iOS
//
//  Created by yangjinxin on 13-8-2.
//
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>
#import <MediaPlayer/MediaPlayer.h>
@interface DSPAVideoPlayView : UIView
{
@private
    NSURL           *videoURL_;
    AVPlayer        *videoPlayer_;
}
@property (nonatomic, retain) NSURL    *videoURL;
@property (nonatomic, retain) AVPlayer *videoPlayer;

- (id) initWithFrame:(CGRect)frame
        withVideoURL:(NSURL *)videoUrl;

- (id) initWithFrame:(CGRect)frame
        withVideoURL:(NSURL *)videoUrl
             playNow:(BOOL)isPlayNow;

- (void) play;
- (void) pause;
@end
