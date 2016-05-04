

#import <Foundation/Foundation.h>

#import "AsyncSocket.h"


@interface AsyncSocketImpl : NSObject <UIAlertViewDelegate>{
	AsyncSocket             *socket;
    NSMutableData           *requestData; 
}

@property (nonatomic, retain) AsyncSocket        *socket;
@property (nonatomic, retain) NSMutableData      *requestData;


+ (AsyncSocketImpl *) sharedAsyncSocketImpl;
- (BOOL)connectServer:(NSString *)hostID port:(UInt16)portID;
- (void)sendMessage:(NSString*)message withTag:(int)tag;
- (void)releaseSocket;
@end

