/* Generated by RuntimeBrowser
   Image: /System/Library/Frameworks/Foundation.framework/Foundation
 */

@class NSArray, NSObject<OS_dispatch_queue>, NSString;

@interface NSOperationQueue : NSObject {
    id _private;
    void *_reserved;
}

@property int maxConcurrentOperationCount;
@property(copy) NSString * name;
@property(readonly) unsigned int operationCount;
@property(copy,readonly) NSArray * operations;
@property int qualityOfService;
@property(getter=isSuspended) BOOL suspended;
@property NSObject<OS_dispatch_queue> * underlyingQueue;

+ (BOOL)automaticallyNotifiesObserversForKey:(id)arg1;
+ (id)currentQueue;
+ (id)mainQueue;

- (id)__;
- (void)addOperation:(id)arg1;
- (void)addOperationWithBlock:(id)arg1;
- (void)addOperations:(id)arg1 waitUntilFinished:(BOOL)arg2;
- (void)cancelAllOperations;
- (void)dealloc;
- (id)description;
- (void)executeAndWaitForBlock:(id)arg1;
- (id)init;
- (BOOL)isSuspended;
- (int)maxConcurrentOperationCount;
- (id)name;
- (unsigned int)operationCount;
- (id)operations;
- (BOOL)overcommitsOperations;
- (int)qualityOfService;
- (void)setMaxConcurrentOperationCount:(int)arg1;
- (void)setName:(id)arg1;
- (void)setOvercommitsOperations:(BOOL)arg1;
- (void)setQualityOfService:(int)arg1;
- (void)setSuspended:(BOOL)arg1;
- (void)setUnderlyingQueue:(id)arg1;
- (id)underlyingQueue;
- (void)waitUntilAllOperationsAreFinished;

@end