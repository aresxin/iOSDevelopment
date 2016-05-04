//
//  XXThread.m
//  DevelopGuide_iOS
//
//  Created by yangjinxin on 13-4-10.
//
//

#import "XXThread.h"
static XXThread    *thread_;
@implementation XXThread


- (id) init
{
    self = [super init];
    if (self)
    {
        taskQueue = [[NSOperationQueue alloc] init];
    }
    return self;
}

+ (XXThread *) shareSettings
{
    //@synchronized线程保护
    @synchronized(self) {
        if (thread_ == nil) {
            thread_ = [[self alloc] init];
        }
    }
    return thread_;
}

// 添加一个操作到线程队列中
- (void) creatNewOperationSelector:(SEL)sel
                          toTarget:(id)target
                        withObject:(id)object
{
    NSInvocationOperation *operation = [[NSInvocationOperation alloc] initWithTarget:target
                                                                            selector:sel
                                                                              object:object];
    [taskQueue addOperation:operation];
    [operation release];
}
@end
