/* Generated by RuntimeBrowser
   Image: /System/Library/PrivateFrameworks/DataAccess.framework/DataAccess
 */

/* RuntimeBrowser encountered an ivar type encoding it does not handle. 
   See Warning(s) below.
 */

@class <DADataclassLockWatcher>;

@interface DAWaiterWrapper : NSObject {
    id _completionHandler;
    int _dataclasses;
    <DADataclassLockWatcher> *_waiter;
    int _waiterNum;
}

@property(copy) id completionHandler;
@property int dataclasses;
@property(retain) <DADataclassLockWatcher> * waiter;
@property(readonly) int waiterNum;

- (void).cxx_destruct;
- (id)completionHandler;
- (int)dataclasses;
- (id)description;
- (id)init;
- (void)setCompletionHandler:(id)arg1;
- (void)setDataclasses:(int)arg1;
- (void)setWaiter:(id)arg1;
- (id)waiter;
- (int)waiterNum;

@end