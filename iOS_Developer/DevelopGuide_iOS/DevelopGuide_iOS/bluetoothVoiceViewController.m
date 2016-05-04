//
//  bluetoothVoiceViewController.m
//  bluetoothVoice
//
//  Created by ZhongChao on 12-4-20.
//  Copyright 2012年 __MyCompanyName__. All rights reserved.
//

#import "bluetoothVoiceViewController.h"

@implementation bluetoothVoiceViewController
@synthesize currentSession;
@synthesize buttonConnenct;
@synthesize buttonDisconnect;
@synthesize buttonMute;

- (void)dealloc
{
    [currentSession release];
    [buttonConnenct release];
    [buttonDisconnect release];
    [buttonMute release];
    
    [super dealloc];
}

- (void)didReceiveMemoryWarning
{
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

#pragma mark - View lifecycle
// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad
{
    [super viewDidLoad];
    isMute = NO;
    [self.buttonMute setTitle:@"Mute" forState:UIControlStateNormal];
    [self.buttonConnenct setHidden:NO];
    [self.buttonDisconnect setHidden:YES];
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

- (IBAction) actionConnect:(id)sender
{
    pick = [[GKPeerPickerController alloc] init];
    pick.delegate = self;
    pick.connectionTypesMask = GKPeerPickerConnectionTypeNearby;
    
    [self.buttonConnenct setHidden:YES];
    [self.buttonDisconnect setHidden:NO];
    
    [pick show];
}

- (IBAction) actionDisconnect:(id)sender
{
    [self.currentSession disconnectFromAllPeers];
    [self.currentSession setDataReceiveHandler:nil withContext:nil];
    [self.currentSession release];
    currentSession = nil;
    
    [self.buttonConnenct setHidden:NO];
    [self.buttonDisconnect setHidden:YES];
}

- (IBAction) actionMute:(id)sender
{
    if (!isMute) {
        [self.buttonMute setTitle:@"Unmute" forState:UIControlStateNormal];
    } else {
        [self.buttonMute setTitle:@"Mute" forState:UIControlStateNormal]; 
    }
    isMute = !isMute;
    [GKVoiceChatService defaultVoiceChatService].microphoneMuted = isMute;
}


#pragma mark -
#pragma mark GKPeerPickerControllerDelegate
//connected device
- (void) peerPickerController:(GKPeerPickerController *)picker didConnectPeer:(NSString *)peerID toSession:(GKSession *)session
{
    self.currentSession = session;
    session.delegate = self;
    NSLog(@"session.peerID : %@", session.peerID);
    // 设定获得session的委托
    [session setDataReceiveHandler:self withContext:nil];
    
    pick.delegate = nil;
    [pick dismiss];
    [pick autorelease];
}
//cancel connect device
- (void) peerPickerControllerDidCancel:(GKPeerPickerController *)picker
{
    pick.delegate = nil;
    [pick dismiss];
    //[pick autorelease];
    [self.buttonConnenct setHidden:NO];
    [self.buttonDisconnect setHidden:YES];
}


#pragma mark
#pragma mark GKSessionDelegate
//
- (void) session:(GKSession *)session connectionWithPeerFailed:(NSString *)peerID withError:(NSError *)error
{
    
}

//Indicates a state change for the given peer连接设备或者断开连接时
- (void) session:(GKSession *)session peer:(NSString *)peerID didChangeState:(GKPeerConnectionState)state
{
    switch (state) {
        case GKPeerStateConnected:
            NSLog(@"device connected");
            //播放音频文件
            [GKVoiceChatService defaultVoiceChatService].microphoneMuted = NO;
            NSError *error = nil;
            NSString *soundFilePath = [[NSBundle mainBundle] pathForResource:@"11" ofType:@"mp4"];
            NSURL *fileURL = [[NSURL alloc] initWithString:soundFilePath];
            AVAudioPlayer *audioPlayer = [[AVAudioPlayer alloc] initWithContentsOfURL:fileURL error:&error];
            if (nil != error) {
                NSLog(@"open file error");
                return;
            }
            [fileURL release];
            [audioPlayer release];
            
            AVAudioSession *audioSession = [AVAudioSession sharedInstance];
            if (![audioSession setCategory:AVAudioSessionCategoryPlayAndRecord error:&error]) {
                NSLog(@"%@", [error localizedDescription]);
                return;
            }
            
            [GKVoiceChatService defaultVoiceChatService].client = self;
            
            if (![[GKVoiceChatService defaultVoiceChatService] startVoiceChatWithParticipantID:peerID error:&error ]) {
                NSLog(@"start chat error  1");
                return;
            }
            
            if (nil != error) {
                NSLog(@"user info : %@", [error userInfo]);
                return;
            }

            
            
            break;
            
        case GKPeerStateDisconnected:
            NSLog(@"device disconnected");
            [[GKVoiceChatService defaultVoiceChatService] stopVoiceChatWithParticipantID:peerID];
//            [self.currentSession release];
//            currentSession = nil;
            
            [currentSession disconnectFromAllPeers];
            [self.currentSession setAvailable:NO];
            [self.currentSession setDataReceiveHandler:nil withContext:nil];
            [self.currentSession release];
            currentSession = nil;
            
            [self.buttonConnenct setHidden:NO];
            [self.buttonDisconnect setHidden:YES];
            break;
            
        case GKPeerStateConnecting:
            NSLog(@"device connecting");
            break;
            
        default:
            break;
    }
}

//接收数据的委托方法
- (void)receiveData:(NSData *)data fromPeer:(NSString *)peer inSession:(GKSession *)session context:(void *)context
{
    NSString *str = @"语音聊天开始";
    UIAlertView *alert = [[[UIAlertView alloc] initWithTitle:@"Receive Data" message:str delegate:self cancelButtonTitle:@"OK" otherButtonTitles:nil, nil] autorelease];
    
    [alert show];
    [str release];
    
    [[GKVoiceChatService defaultVoiceChatService] receivedData:data fromParticipantID:peer];
    NSLog(@"receive data description : %@", [data description]);
    NSLog(@"receive data : %@", data);
}

#pragma mark -
#pragma mark GKVoiceChatClient delegate
// 收集录音数据发送给以连接的蓝牙端口
- (void)voiceChatService:(GKVoiceChatService *)voiceChatService sendData:(NSData *)data toParticipantID:(NSString *)participantID
{
    NSError *error = nil;
    // 用Session发送数据
    [currentSession sendData:data toPeers:[NSArray arrayWithObject:participantID] withDataMode:GKSendDataReliable error:&error];
    
    if (nil != error) {
        NSLog(@"send error");
    }
}

- (NSString *)participantID
{
    NSString *stringID = nil;
    if (nil != currentSession) 
    {
        stringID = currentSession.peerID;
    }
    
    return stringID;
}

@end
