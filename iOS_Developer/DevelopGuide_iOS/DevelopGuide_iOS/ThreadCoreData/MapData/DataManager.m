//
//  DataManager.m
//  ToyotaSalesService
//
//  Created by yangjinxin on 13-7-29.
//  Copyright (c) 2013年 xin. All rights reserved.
//

#import "DataManager.h"
#import "XXStore.h"

@implementation DataManager
static DataManager *instance = nil;
+ (DataManager*) sharedInstance
{
    @synchronized(self)
    {
        if (instance == nil)
        {
            instance = [[self alloc] init];
        }
    }
    
    return instance;
}

- (id)init
{
    if (self = [super init])
    {
        
    }
    
    return self;
}

/*
 * 1.0 从DB中查询数据
 */
- (void) asyncFetchRequestEntiry:(NSString *)entiryName
                    fetchRequest:(NSFetchRequest *)fetchRequest
               CompletionHandler:(void (^)(NSArray *results))block
{
    NSFetchRequest* fetch = nil;
    
    if (fetchRequest != nil)
    {
        fetch = fetchRequest;
    }
    else
    {
        fetch = [[NSFetchRequest alloc] init];
    }
    
    [fetch setEntity:[[XXStore shareStore] entityForName:entiryName]];
   
    // create thread moc
    NSManagedObjectContext *childContext = [[NSManagedObjectContext alloc]
                                            initWithConcurrencyType:NSPrivateQueueConcurrencyType];
    
    [childContext performBlock:^{
        assert([NSThread isMainThread] == NO);
        
        NSError *error = nil;
        NSArray *results = nil;
        
        results = [childContext executeFetchRequest:fetch
                                              error:&error];
        
        dispatch_sync(dispatch_get_main_queue(), ^{
            assert([NSThread isMainThread] == YES);
            
            if (block != nil)
            {
                block(results);
            }
        });
       
    }];
}


/*
 * 2.0 从DB中删除数据
 */
- (void)deleteObject:(NSManagedObjectID *)objectID
{
    [[XXStore shareStore] deleteObjectById:objectID];
    [[XXStore shareStore] saveContext];
}

- (void)deleteMultiObject:(NSArray*)objectIDs
{
    if (objectIDs == nil || [objectIDs count]<=0) {
        return;
    }
    
    for (NSManagedObjectID *objectID in objectIDs)
    {
        [[XXStore shareStore] deleteObjectById:objectID];
    }
    [[XXStore shareStore] saveContext];
}


@end
