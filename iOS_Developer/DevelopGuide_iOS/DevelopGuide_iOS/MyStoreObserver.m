//
//  MyStoreObserver.m
//  SignatureN
//
//  Created by fanshao on 09-9-1.
//  Copyright 2009 Sensky. All rights reserved.
//

#import "MyStoreObserver.h"
#import<UIKit/UIKit.h>
#import<UIKit/UIAlert.h>
#import "JSON.h"
#import "NSData+Addition.h"
@implementation MyStoreObserver


- (void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions
{
	NSLog(@"paymetnQueue");
	for (SKPaymentTransaction* transaction in transactions)
	{
		switch (transaction.transactionState)
		{
			case SKPaymentTransactionStatePurchased:
				NSLog(@"Complete Transaction");
				[self completeTransaction:transaction];
				break;
			case SKPaymentTransactionStateFailed:
                NSLog(@"Failed Transaction");
				[self failedTransaction:transaction];
				break;
			case SKPaymentTransactionStateRestored:
				break;
			default:
				break;
		}
	}
}

-(void) PurchasedTransaction: (SKPaymentTransaction *)transaction{
	NSArray *transactions =[[NSArray alloc] initWithObjects:transaction, nil];
	[self paymentQueue:[SKPaymentQueue defaultQueue] updatedTransactions:transactions];
	[transactions release];
}

- (void) completeTransaction: (SKPaymentTransaction *)transaction
{
	NSLog(@"Transaction　complete");
    NSError *jsonError = nil;
    NSDictionary *info = [NSDictionary dictionaryWithObject:[transaction.transactionReceipt base64String] forKey:@"receipt-data"];
    NSData* jsonData = [NSJSONSerialization dataWithJSONObject:info options:NSJSONWritingPrettyPrinted error:&jsonError];

	NSURL *sandboxStoreURL = [[NSURL alloc] initWithString: @"https://sandbox.itunes.apple.com/verifyReceipt"];
	//NSData *postData = [NSData dataWithBytes:[josnValue UTF8String] length:[josnValue length]];
	NSMutableURLRequest *connectionRequest = [NSMutableURLRequest requestWithURL:sandboxStoreURL];
	[connectionRequest setHTTPMethod:@"POST"];
	[connectionRequest setTimeoutInterval:120.0];
	[connectionRequest setCachePolicy:NSURLRequestUseProtocolCachePolicy];
	[connectionRequest setHTTPBody:jsonData];
	[[SKPaymentQueue defaultQueue] finishTransaction: transaction];
	
	
	NSURLConnection *connection = [[NSURLConnection alloc]
                                   initWithRequest:connectionRequest
                                   delegate:self];
	[connection release];
}

- (void) failedTransaction: (SKPaymentTransaction *)transaction
{
	[[NSNotificationCenter defaultCenter] postNotificationName:@"faliedTransaction" object:nil];
	[[SKPaymentQueue defaultQueue] finishTransaction: transaction];
}

-(void) paymentQueueRestoreCompletedTransactionsFinished: (SKPaymentTransaction *)transaction{

}

-(void) paymentQueue:(SKPaymentQueue *) paymentQueue restoreCompletedTransactionsFailedWithError:(NSError *)error{

}


#pragma mark connection delegate
- (void)connection:(NSURLConnection *)connection didReceiveData:(NSData *)data
{
	NSLog(@"connection didReceiveData : %@",  [[[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding] autorelease]);
	//[self.receivedData appendData:data];
}
- (void)connectionDidFinishLoading:(NSURLConnection *)connection{
    NSLog(@"connectionDidFinishLoading");
}

- (void)connection:(NSURLConnection *)connection didReceiveResponse:(NSURLResponse *)response{
    
    NSLog(@"connection didReceiveResponse: %d", [(NSHTTPURLResponse *)response statusCode]);
	switch([(NSHTTPURLResponse *)response statusCode]) {
		case 200:
		case 206:
			break;
		case 304:
			break;
		case 400:
			break;
		case 404:
		    break;
		case 416:
			break;
		case 403:
			break;
		case 401:
		case 500:
			break;
		default:
			break;
	}	
}

- (void)connection:(NSURLConnection *)connection didFailWithError:(NSError *)error {
	

}

@end
