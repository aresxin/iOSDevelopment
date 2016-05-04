//
//  bluetoothVoiceViewController.h
//  bluetoothVoice
//
//  Created by ZhongChao on 12-4-20.
//  Copyright 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <GameKit/GameKit.h>
#import <AVFoundation/AVFoundation.h>


@interface bluetoothVoiceViewController : UIViewController
                                    <GKVoiceChatClient, 
                                    GKSessionDelegate, 
                                    GKPeerPickerControllerDelegate> {
    GKSession               *currentSession;
    IBOutlet UIButton       *buttonConnenct;
    IBOutlet UIButton       *buttonDisconnect;
    IBOutlet UIButton       *buttonMute;
    GKPeerPickerController  *pick;
    //NSString                *stringFilePath;
    //AVAudioPlayer           *audioPlayer;
    BOOL                    isMute;
}
@property (nonatomic, retain) GKSession *currentSession;
@property (nonatomic, retain) IBOutlet UIButton *buttonConnenct;
@property (nonatomic, retain) IBOutlet UIButton *buttonDisconnect;
@property (nonatomic, retain) IBOutlet UIButton *buttonMute;

- (IBAction) actionConnect:(id)sender;
- (IBAction) actionDisconnect:(id)sender;
- (IBAction) actionMute:(id)sender;
@end
