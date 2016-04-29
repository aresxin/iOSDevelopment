/* Generated by RuntimeBrowser
   Image: /System/Library/Frameworks/MediaPlayer.framework/MediaPlayer
 */

@class MPMoviePlayerController;

@interface MPMoviePlayerViewController : UIViewController {
    id _internal;
    BOOL _statusBarWasHidden;
}

@property(readonly) MPMoviePlayerController * moviePlayer;

- (void).cxx_destruct;
- (BOOL)_canReloadView;
- (void)_moviePlayerViewController_applicationDidEnterBackgroundNotification:(id)arg1;
- (void)_moviePlayerViewController_playbackDidFinishNotification:(id)arg1;
- (BOOL)_shouldUseFullScreenLayoutInWindow:(id)arg1 parentViewController:(id)arg2;
- (BOOL)canBecomeFirstResponder;
- (void)dealloc;
- (void)didRotateFromInterfaceOrientation:(int)arg1;
- (id)init;
- (id)initWithAsset:(id)arg1;
- (id)initWithContentURL:(id)arg1;
- (void)loadView;
- (id)moviePlayer;
- (BOOL)prefersStatusBarHidden;
- (void)remoteControlReceivedWithEvent:(id)arg1;
- (BOOL)shouldAutorotate;
- (BOOL)shouldAutorotateToInterfaceOrientation:(int)arg1;
- (unsigned int)supportedInterfaceOrientations;
- (void)viewDidAppear:(BOOL)arg1;
- (void)viewDidDisappear:(BOOL)arg1;
- (void)viewWillAppear:(BOOL)arg1;
- (void)viewWillDisappear:(BOOL)arg1;
- (void)willAnimateRotationToInterfaceOrientation:(int)arg1 duration:(double)arg2;

@end