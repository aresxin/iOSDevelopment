

#import "AsyncSocketImpl.h"
#import "GUIConst.h"

@implementation AsyncSocketImpl

@synthesize socket;
@synthesize requestData;

/*
 * 单例模式:唯一实例化一个对象
 * AsyncSocketImpl类只需要一个实例，在不同的类中调用。
 * 重复创建AsyncSocketImpl类的实例，浪费内存资源。
 */ 
static AsyncSocketImpl *socketMgr = nil;
+ (AsyncSocketImpl *) sharedAsyncSocketImpl
{    
    @synchronized(self)
    {
        if (socketMgr == nil) {
           socketMgr = [[self alloc] init];
        }
    }
    return socketMgr;
}

- (id)init
{
	if ((self = [super init]) != nil) {
		self.socket = nil;
        self.requestData = nil;
	}
	return self;
}

#pragma mark -
#pragma mark socket utility
- (BOOL)connectServer:(NSString*)hostID port:(UInt16)portID
{
	BOOL connectFlag = NO;
	NSError * error = nil;
	
	if (self.socket == nil) 
    {
        AsyncSocket *asSocket = [[AsyncSocket alloc] initWithDelegate:self];
        self.socket = asSocket;
        [asSocket release];
        
		if ([socket connectToHost:hostID onPort:portID withTimeout:-1 error:&error]) {
			//NSLog(@"server connect successfully.");
            connectFlag = YES;
		}
		else {
			//NSLog(@"server connect error: %@", error);
			connectFlag = NO;
		}	
	}
	else 
    {
		[socket readDataWithTimeout:-1 tag:0];
        //NSLog(@"server has been connected.");
		connectFlag = YES;
	}
	
	return connectFlag;
}


- (void)sendMessage:(NSString*)message withTag:(int)tag
{
    self.requestData = [NSMutableData data];
	NSData *data = [message dataUsingEncoding:NSUTF16LittleEndianStringEncoding];
#ifdef _DEBUG_
	NSString *result = [[NSString alloc] initWithData:data  
                                             encoding:NSUTF16LittleEndianStringEncoding];
	NSLog(@"iOS send message  is : %@", result);
    [result release];
#endif
    [socket writeData:data withTimeout:-1 tag:tag]; 
    //[socket writeData:data withTimeout:60 tag:tag];
}


#pragma mark -
#pragma mark socket delegate
// a socket connects and is ready for reading and writing.
- (void)onSocket:(AsyncSocket *)sock didConnectToHost:(NSString *)host port:(UInt16)port
{
	[socket readDataWithTimeout:-1 tag:0]; 
}

/*
- (BOOL)onSocketWillConnect:(AsyncSocket *)sock
{
    return YES;
}
*/
// Called after the socket has successfully completed SSL/TLS negotiation.
- (void)onSocketDidSecure:(AsyncSocket *)sock
{
	
}

// In the event of an error, the socket is closed.
- (void)onSocket:(AsyncSocket *)sock willDisconnectWithError:(NSError *)err
{
    if (err != nil) 
    {
        UIAlertView *alert = 
        [[UIAlertView alloc]initWithTitle:NSLocalizedString(ERROR_TITLE, nil) 
                                  message:NSLocalizedString(ERROR_MESSAGE_SOCKET_FAILED, nil) 
                                 delegate:self
                        cancelButtonTitle:NSLocalizedString(ERROR_OK , nil)
                        otherButtonTitles:nil];	
        [alert show];
        [alert release];
    }

}

// Called when a socket disconnects with or without error.
- (void)onSocketDidDisconnect:(AsyncSocket *)sock
{
	self.socket = nil;
}

// a socket has completed reading the requested data into memory.
- (void)onSocket:(AsyncSocket *)sock didReadData:(NSData *)data withTag:(long)tag
{
    [requestData appendData:data];
    [socket readDataWithTimeout:-1 tag:tag];
    //[socket readDataWithTimeout:60 tag:tag];
}


- (void)onSocket:(AsyncSocket *)sock didWriteDataWithTag:(long)tag
{
	//NSLog(@"write data with tag... %ld", tag);
}

- (void)releaseSocket
{
	self.socket = nil;
}

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
	if (buttonIndex == 0) {
		//exit(0);
	}
}

#pragma mark -
- (void)dealloc {
	self.socket = nil;
    [socket release];
    [requestData release];
    [super dealloc];
}

@end
