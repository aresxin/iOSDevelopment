//
//  ChatViewController.h
//  ChatMe
//
//  Created by neusoft  on 11-7-13.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AsyncUdpSocket.h"

@interface ChatViewController : UIViewController {
	IBOutlet UITextView *messView;
	IBOutlet UITextView *receView;
	AsyncUdpSocket    *udpSocket;

}
@property (nonatomic, retain) AsyncUdpSocket *udpSocket;
@property (nonatomic, retain) IBOutlet UITextView *messView;
@property (nonatomic, retain) IBOutlet UITextView *receView;
-(void)sendMassage:(NSString *)message;
-(void)openUDPServer;
- (IBAction) send:(id)sender;
@end
