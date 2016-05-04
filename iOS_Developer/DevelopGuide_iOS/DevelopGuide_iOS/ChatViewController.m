//
//  ChatViewController.m
//  ChatMe
//
//  Created by neusoft  on 11-7-13.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "ChatViewController.h"

 
@implementation ChatViewController
@synthesize udpSocket;
@synthesize messView;
@synthesize receView;
// The designated initializer.  Override if you create the controller programmatically and want to perform customization that is not appropriate for viewDidLoad.
/*
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization.
    }
    return self;
}
*/


// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    [super viewDidLoad];
}

- (void) viewWillAppear:(BOOL)animated
{
	[self openUDPServer];
}

//建立基于UDP的Socket连接
-(void)openUDPServer{
	//初始化udp
	AsyncUdpSocket *tempSocket=[[AsyncUdpSocket alloc] initWithDelegate:self];
	self.udpSocket=tempSocket;
	[tempSocket release];
	//绑定端口
	NSError *error = nil;
	[self.udpSocket bindToPort:9527 error:&error];
	//启动接收线程
	[self.udpSocket receiveWithTimeout:-1 tag:0];
}

- (IBAction) send:(id)sender
{
	//[UIApplication sharedApplication].networkActivityIndicatorVisible = YES;
	NSString *messageStr = messView.text;
	[self sendMassage:messageStr];
	[messView resignFirstResponder];
	//self.messView.text = @"";
}

//通过UDP,发送短消息
-(void)sendMassage:(NSString *)message
{
	
	NSString *sendString=@"";
	sendString=[sendString stringByAppendingString:message];
	//开始发送
	BOOL res = [self.udpSocket sendData:[sendString dataUsingEncoding:NSASCIIStringEncoding] 
								 toHost:@"10.1.128.202" 
								   port:9527 
							withTimeout:-1 
									tag:0];
	if (!res) {
		UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"提示"
														message:@"发送失败"
													   delegate:self
											  cancelButtonTitle:@"取消"
											  otherButtonTitles:nil];
		[alert show];
		[alert release];
	}
	
}


// Override to allow orientations other than the default portrait orientation.
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    // Return YES for supported orientations.
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

#pragma mark -
#pragma mark UDP Delegate Methods
- (BOOL)onUdpSocket:(AsyncUdpSocket *)sock didReceiveData:(NSData *)data withTag:(long)tag fromHost:(NSString *)host port:(UInt16)port
{   
	//接收到数据回调
	[self.udpSocket receiveWithTimeout:-1 tag:0];
	NSString *info=[[[NSString alloc] initWithData:data encoding: NSASCIIStringEncoding] autorelease];
	
	self.receView.text = info;
	//已经处理完毕
	return YES;
}

- (void)onUdpSocket:(AsyncUdpSocket *)sock didNotSendDataWithTag:(long)tag dueToError:(NSError *)error
{
	//无法发送时,返回的异常提示信息
	UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"提示"
													message:[error description]
												   delegate:self
										  cancelButtonTitle:@"取消"
										  otherButtonTitles:nil];
	[alert show];
	[alert release];
	
}
- (void)onUdpSocket:(AsyncUdpSocket *)sock didNotReceiveDataWithTag:(long)tag dueToError:(NSError *)error
{   
	//无法接收时，返回异常提示信息
	UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"提示"
													message:[error description]
												   delegate:self
										  cancelButtonTitle:@"取消"
										  otherButtonTitles:nil];
	[alert show];
	[alert release];	
}


- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc. that aren't in use.
}

- (void)viewDidUnload {
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}


- (void)dealloc {
	[messView release];
	[udpSocket release];
	[receView release];
    [super dealloc];
}


@end
