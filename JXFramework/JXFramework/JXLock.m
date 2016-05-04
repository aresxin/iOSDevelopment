//
//  JXLock.m
//  JXFramework
//
//  Created by yangjinxin on 15/9/8.
//  Copyright (c) 2015年 yangjinxin. All rights reserved.
//

/*
 * Reference:
 * http://www.raywenderlich.com/60749/grand-central-dispatch-in-depth-part-1
 * https://www.zybuluo.com/MicroCai/note/64272
 */



#define CREATE_CONCURRENT_QUEUE  1

#import "JXLock.h"


@interface JXLock ()
{
    dispatch_queue_t                            _lockQueue;
    
}
@end

@implementation JXLock

static void *kLockQueueKey;


+ (instancetype)sharedInstance;
{
    static dispatch_once_t pred;
    static JXLock *sharedInstance = nil;

    dispatch_once(&pred, ^{
        sharedInstance = [[[self class] alloc] init];
    });
    return sharedInstance;
}

+ (dispatch_queue_t)sharedLockQueue;
{
    return [[JXLock sharedInstance] currentLockQueue];
}

- (dispatch_queue_t)currentLockQueue
{
    return _lockQueue;
}


+ (void *)lockQueueSpecificKey;
{
    return [[JXLock sharedInstance] lockQueueSpecificKey];
}

- (void *)lockQueueSpecificKey;
{
    return kLockQueueKey;
}

- (instancetype)init
{
    self = [super init];
    
    if (self) {
        // create Concurrent queue ...
        
#if  CREATE_CONCURRENT_QUEUE
        /*
         * 方案一
         * 创建并发线程，提高性能，因为get方法可以并发，set方法不能并发。
         */
        //_lockQueue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
        _lockQueue = dispatch_queue_create("com.lock.queue", DISPATCH_QUEUE_CONCURRENT);
        
        // set queue specific key 防止死锁
        kLockQueueKey = &kLockQueueKey;
        dispatch_queue_set_specific(_lockQueue, kLockQueueKey, (__bridge void *)self, NULL);
#else
        /*
         * 方案二
         * 创建串行线程，保证线程安全
         */
        _lockQueue = dispatch_queue_create("com.lock.queue", NULL);
        
        // set queue specific key 防止死锁
        kLockQueueKey = &kLockQueueKey;
        dispatch_queue_set_specific(_lockQueue, kLockQueueKey, (__bridge void *)self, NULL);
        
#endif

    }
    
    return self;
}


void runOnMainQueue(void (^block)(void))
{
    if ([NSThread isMainThread]) {
        block();
    } else {
        dispatch_async(dispatch_get_main_queue(), block);
    }
}

/* 
 * 创建可以并发的queue,因为get方法可以并发,提高访问性能。
 * 调用Sync会阻塞调用线程，block结束后，返回值。
 * get方法需要lock时,调用下面的方法。
 */
void runSyncOnLockQueue(void (^block)(void))
{
    if (dispatch_get_specific([JXLock lockQueueSpecificKey])) {
        //判断调用线程是否已经是在queue线程，如果是queue线程，直接执行block防止死锁。
        block();
    } else {
        dispatch_queue_t queue = [JXLock sharedLockQueue];
        dispatch_sync(queue, block);
    }
}


/*
 * set方法不需要阻塞调用线程，所以调用Async方法
 * set方法不能并发,所以用“barrier”的方式调用。
 * “barrier”会等queue的其它方法执行完，在执行。
 * set方法需要上锁时调用下面的方法
 */
void runAsyncOnLockQueue(void (^block)(void))
{
    if (dispatch_get_specific([JXLock lockQueueSpecificKey])) {
        block();
    } else {
        dispatch_queue_t queue = [JXLock sharedLockQueue];
        
#if  CREATE_CONCURRENT_QUEUE
        dispatch_barrier_async(queue,block);
#else
        dispatch_async(queue, block);
#endif
    }
}



@end
