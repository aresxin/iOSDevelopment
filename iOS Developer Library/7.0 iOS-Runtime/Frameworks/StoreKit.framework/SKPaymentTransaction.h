/* Generated by RuntimeBrowser
   Image: /System/Library/Frameworks/StoreKit.framework/StoreKit
 */

@class NSArray, NSData, NSDate, NSError, NSString, SKPayment, SKPaymentTransaction;

@interface SKPaymentTransaction : NSObject {
    id _internal;
}

@property(readonly) NSString * _transactionIdentifier;
@property(readonly) NSArray * downloads;
@property(readonly) NSError * error;
@property(readonly) NSString * matchingIdentifier;
@property(readonly) SKPaymentTransaction * originalTransaction;
@property(readonly) SKPayment * payment;
@property(readonly) NSDate * transactionDate;
@property(readonly) NSString * transactionIdentifier;
@property(readonly) NSData * transactionReceipt;
@property(readonly) int transactionState;

- (void)_setDownloads:(id)arg1;
- (void)_setError:(id)arg1;
- (void)_setOriginalTransaction:(id)arg1;
- (void)_setTemporaryIdentifier:(id)arg1;
- (void)_setTransactionDate:(id)arg1;
- (void)_setTransactionIdentifier:(id)arg1;
- (void)_setTransactionReceipt:(id)arg1;
- (void)_setTransactionState:(int)arg1;
- (id)_transactionIdentifier;
- (BOOL)canMergeWithTransaction:(id)arg1;
- (id)copyXPCEncoding;
- (void)dealloc;
- (id)downloads;
- (id)error;
- (id)init;
- (id)initWithPayment:(id)arg1;
- (id)initWithXPCEncoding:(id)arg1;
- (id)matchingIdentifier;
- (BOOL)mergeWithTransaction:(id)arg1;
- (id)originalTransaction;
- (id)payment;
- (id)transactionDate;
- (id)transactionIdentifier;
- (id)transactionReceipt;
- (int)transactionState;

@end