//
//  DataManager.m
//  ToyotaSalesService
//
//  Created by yangjinxin on 13-7-29.
//  Copyright (c) 2013年 xin. All rights reserved.
//

#import "DataManager.h"
#import "XXStore.h"
#import "DBModelMap.h"
#import "NSManagedObjectContext+RKAdditions.h"
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
    
    childContext.parentContext           = [XXStore shareStore].managedObjectContext;
    
    [childContext performBlock:^{
        assert([NSThread isMainThread] == NO);
        
        NSError *error = nil;
        NSArray *results = nil;
        
        results = [childContext executeFetchRequest:fetch
                                              error:&error];
        
        dispatch_async(dispatch_get_main_queue(), ^{
            assert([NSThread isMainThread] == YES);
            
            if (block != nil)
            {
                block(results);
            }
        });
       
    }];
}

- (NSArray *) fetchRequestEntiry:(NSString *)entiryName
                    fetchRequest:(NSFetchRequest *)fetchRequest
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
    
    childContext.parentContext           = [XXStore shareStore].managedObjectContext;
    
    
    __block NSArray *results = nil;
    
    [childContext performBlockAndWait:^{
               
        NSError *error = nil;
        
        results = [childContext executeFetchRequest:fetch
                                              error:&error];
    }];

    return results;
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


- (void) insertMultiObject:(NSArray *)objects
                    entity:(NSString *)entityName
{
    NSLog(@"%s",__FUNCTION__);
    
    if (objects == nil || [objects count] == 0)
    {
        return;
    }
    
    NSManagedObjectContext *childContext = [[NSManagedObjectContext alloc] initWithConcurrencyType:NSPrivateQueueConcurrencyType];
    childContext.parentContext           = [XXStore shareStore].managedObjectContext;
    
    [childContext performBlockAndWait:^{
      
        for (int i = 0; i < [objects count]; i++)
        {
            DBModelMap      *model     = [objects objectAtIndex:i];
            
            NSManagedObject *mangedObj = [childContext insertNewObjectForEntityForName:entityName];
            
            [model convertToDBData:mangedObj];
            
            model.managedObjectID      = mangedObj.objectID;
        }
        
        NSError *error = nil;
        [childContext save:&error];
    }];
}

/*
 * 3.0 批量插入数据
 * 此方法是异步执行的
 */
- (void) asyncInsertMultiObject:(NSArray *)objects
                         entity:(NSString *)entityName
{
    if (objects == nil || [objects count] == 0)
    {
        return;
    }
    
    NSManagedObjectContext *childContext = [[NSManagedObjectContext alloc] initWithConcurrencyType:NSPrivateQueueConcurrencyType];
    
    // set child managedobjectContext ParentContext
    childContext.parentContext           = [XXStore shareStore].managedObjectContext;
    
    [childContext performBlock:^{
        
        assert([NSThread isMainThread] == NO);
        
        for (int i = 0; i < [objects count]; i++)
        {
            DBModelMap      *model     = [objects objectAtIndex:i];
            
            NSManagedObject *mangedObj = [childContext insertNewObjectForEntityForName:entityName];
            
            [model convertToDBData:mangedObj];
        }
        
        NSError *error = nil;
        [childContext save:&error];
    }];

}
@end
