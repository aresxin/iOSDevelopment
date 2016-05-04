//
//  XXStore.m
//  DevelopGuide_iOS
//
//  Created by yangjinxin on 13-4-3.
//
//

#import "XXStore.h"

#define SQLITR_NAME   @"CRMDataMode"
#define DATEMODE_NAM  @"CRMModel"

static XXStore* instance = nil;
@implementation XXStore
@synthesize managedObjectContext=__managedObjectContext;

@synthesize managedObjectModel=__managedObjectModel;

@synthesize persistentStoreCoordinator=__persistentStoreCoordinator;

@synthesize threadManagedObjectContext = _threadManagedObjectContext;

@synthesize delegate;

+ (XXStore*) shareStore
{
    if (instance == nil) {
        instance = [[XXStore alloc] init];
    }
    return instance;
}

+ (void)destory
{
    [instance release];
    instance = nil;
}

- (void)dealloc
{
    [__managedObjectContext release];
    [__managedObjectModel release];
    [__persistentStoreCoordinator release];
    [super dealloc];
}

- (void) resetPersistentStore
{
    [self saveContext];
    [__managedObjectContext release];
    __managedObjectContext = nil;
    [__managedObjectModel release];
    __managedObjectModel = nil;
    [__persistentStoreCoordinator release];
    __persistentStoreCoordinator = nil;
}

- (void) didReceiveMemoryWarning
{
    
    
}

#pragma mark -
#pragma mark - Core Data stack

- (void)saveContext
{
    NSError *error = nil;
    NSManagedObjectContext *managedObjectContext = self.managedObjectContext;
    if (managedObjectContext != nil) {
        if ([managedObjectContext hasChanges] && ![managedObjectContext save:&error]) {
            /*
             Replace this implementation with code to handle the error appropriately.
             
             abort() causes the application to generate a crash log and terminate. You should not use this function in a shipping application, although it may be useful during development. If it is not possible to recover from the error, display an alert panel that instructs the user to quit the application by pressing the Home button.
             */
            // NSLog(@"Unresolved error %@, %@", error, [error userInfo]);
#ifdef DEBUG
            abort();
#endif
        }
    }
}

- (void)saveContextOnThread
{
    NSError *error = nil;
    NSManagedObjectContext *managedObjectContext = self.threadManagedObjectContext;
    if (managedObjectContext != nil) {
        if ([managedObjectContext hasChanges] && ![managedObjectContext save:&error]) {
            /*
             Replace this implementation with code to handle the error appropriately.
             
             abort() causes the application to generate a crash log and terminate. You should not use this function in a shipping application, although it may be useful during development. If it is not possible to recover from the error, display an alert panel that instructs the user to quit the application by pressing the Home button.
             */
            // NSLog(@"Unresolved error %@, %@", error, [error userInfo]);
#ifdef DEBUG
            abort();
#endif
        }
    }
}


/**
 Returns the managed object context for the application.
 If the context doesn't already exist, it is created and bound to the persistent store coordinator for the application.
 */
- (NSManagedObjectContext *)managedObjectContext
{
    if (__managedObjectContext != nil) {
        return __managedObjectContext;
    }
    
    NSPersistentStoreCoordinator *coordinator = [self persistentStoreCoordinator];
    if (coordinator != nil) {
        __managedObjectContext = [[NSManagedObjectContext alloc] init];
        [__managedObjectContext setPersistentStoreCoordinator:coordinator];
    }
    
    return __managedObjectContext;
}

- (NSManagedObjectContext *) threadManagedObjectContext
{
    if (_threadManagedObjectContext != nil) {
        return _threadManagedObjectContext;
    }
    
    NSPersistentStoreCoordinator *coordinator = [self persistentStoreCoordinator];
    if (coordinator != nil) {
        _threadManagedObjectContext = [[NSManagedObjectContext alloc] init];
        [_threadManagedObjectContext setPersistentStoreCoordinator:coordinator];
    }
    
    // 如果子线程的managed context发生变化，更新主线程的managed context
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(doMergeChangesFromNotification:) name:NSManagedObjectContextDidSaveNotification object:_threadManagedObjectContext];
    
    return _threadManagedObjectContext;
}

/**
 Returns the managed object model for the application.
 If the model doesn't already exist, it is created from the application's model.
 */
- (NSManagedObjectModel *)managedObjectModel
{
    if (__managedObjectModel != nil) {
        return __managedObjectModel;
    }
    NSURL *modelURL = [[NSBundle mainBundle] URLForResource:DATEMODE_NAM withExtension:@"momd"];
    __managedObjectModel = [[NSManagedObjectModel alloc] initWithContentsOfURL:modelURL];
    return __managedObjectModel;
}

/**
 Returns the persistent store coordinator for the application.
 If the coordinator doesn't already exist, it is created and the application's store added to it.
 */
- (NSPersistentStoreCoordinator *)persistentStoreCoordinator
{
    if (__persistentStoreCoordinator != nil) {
        return __persistentStoreCoordinator;
    }
    
    NSURL *storeURL = [[self applicationDocumentsDirectory] URLByAppendingPathComponent:[NSString stringWithFormat:@"%@.sqlite",SQLITR_NAME]];
    
    NSError *error = nil;
    __persistentStoreCoordinator = [[NSPersistentStoreCoordinator alloc] initWithManagedObjectModel:[self managedObjectModel]];
    if (![__persistentStoreCoordinator addPersistentStoreWithType:NSSQLiteStoreType configuration:nil URL:storeURL options:nil error:&error]) {
        /*
         Replace this implementation with code to handle the error appropriately.
         
         abort() causes the application to generate a crash log and terminate. You should not use this function in a shipping application, although it may be useful during development. If it is not possible to recover from the error, display an alert panel that instructs the user to quit the application by pressing the Home button.
         
         Typical reasons for an error here include:
         * The persistent store is not accessible;
         * The schema for the persistent store is incompatible with current managed object model.
         Check the error message to determine what the actual problem was.
         
         
         If the persistent store is not accessible, there is typically something wrong with the file path. Often, a file URL is pointing into the application's resources directory instead of a writeable directory.
         
         If you encounter schema incompatibility errors during development, you can reduce their frequency by:
         * Simply deleting the existing store:
         [[NSFileManager defaultManager] removeItemAtURL:storeURL error:nil]
         
         * Performing automatic lightweight migration by passing the following dictionary as the options parameter:
         [NSDictionary dictionaryWithObjectsAndKeys:[NSNumber numberWithBool:YES], NSMigratePersistentStoresAutomaticallyOption, [NSNumber numberWithBool:YES], NSInferMappingModelAutomaticallyOption, nil];
         
         Lightweight migration will only work for a limited set of schema changes; consult "Core Data Model Versioning and Data Migration Programming Guide" for details.
         
         */
        //  NSLog(@"Unresolved error %@, %@", error, [error userInfo]);
#ifdef DEBUG
        abort();
#endif
    }
    
    return __persistentStoreCoordinator;
}

#pragma mark - Application's Documents directory

/**
 Returns the URL to the application's Documents directory.
 */
- (NSURL *)applicationDocumentsDirectory
{
    return [[[NSFileManager defaultManager] URLsForDirectory:NSDocumentDirectory inDomains:NSUserDomainMask] lastObject];
}

#pragma mark - ThreadNSManagedObjectContext
- (NSManagedObject*) insertNewObjectForEntityForNameOnThread:(NSString*)entityName
{
    return
    [NSEntityDescription insertNewObjectForEntityForName:entityName inManagedObjectContext:self.threadManagedObjectContext];
}

- (NSArray *)executeFetchRequestOnThread:(NSFetchRequest *)request error:(NSError **)error
{
    return [self.threadManagedObjectContext executeFetchRequest:request error:error];
}

#pragma mark - NSManagedObjectContext
- (NSManagedObject *)objectWithID:(NSManagedObjectID *)objectID
{
    if (objectID == nil)
    {
        return nil;
    }
    return [self.managedObjectContext objectWithID:objectID];
}

- (void)insertObject:(NSManagedObject *)object
{
    
    if (object == nil)
    {
        return;
    }
    
    [self.managedObjectContext insertObject:object];
}

- (void)deleteObject:(NSManagedObject *)object
{
    
    if (object == nil)
    {
        return;
    }
    
    [self.managedObjectContext deleteObject:object];
}

- (NSManagedObject*) insertNewObjectForEntityForName:(NSString*)entityName
{
    return
    [NSEntityDescription insertNewObjectForEntityForName:entityName inManagedObjectContext:self.managedObjectContext];
}

- (void)deleteObjectById:(NSManagedObjectID *)objectID
{
    NSManagedObject *object = [self objectWithID:objectID];
    [self deleteObject:object];
}

- (NSEntityDescription*) entityForName:(NSString*)entityName
{
    return [NSEntityDescription entityForName:entityName inManagedObjectContext:self.managedObjectContext];
}

- (NSArray *)executeFetchRequest:(NSFetchRequest *)request error:(NSError **)error
{
    return [self.managedObjectContext executeFetchRequest:request error:error];
}

#pragma mark -
#pragma mark selector
- (void)doMergeChangesFromNotification:(NSNotification*)notification
{
    [self.managedObjectContext mergeChangesFromContextDidSaveNotification:notification];
    
    if ([delegate respondsToSelector:@selector(didMergeChangesFromContextDidSaveNotification)])
    {
        [delegate didMergeChangesFromContextDidSaveNotification];
    }
}


@end
