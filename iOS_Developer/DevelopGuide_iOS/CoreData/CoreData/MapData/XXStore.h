//
//  XXStore.h
//  DevelopGuide_iOS
//
//  Created by yangjinxin on 13-4-3.
//
//

#import <Foundation/Foundation.h>

@protocol XXStoreDelegate <NSObject>
@optional
- (void) didMergeChangesFromContextDidSaveNotification;
@end


@interface XXStore : NSObject {
    NSManagedObjectContext       *__managedObjectContext;
    NSManagedObjectModel         *__managedObjectModel;
    NSPersistentStoreCoordinator *__persistentStoreCoordinator;
    //子线程managedObjectContext
    NSManagedObjectContext       *_threadManagedObjectContext;
    id   <XXStoreDelegate>       delegate;
    
    NSString                     *_dataMode;
    NSString                     *_storePath;
}
@property (nonatomic, retain)  NSString *dataMode;
@property (nonatomic, retain)  NSString *storePath;

+ (XXStore*) shareStore;
+ (void)destory;
@property (nonatomic, retain, readonly) NSManagedObjectContext *managedObjectContext;
@property (nonatomic, retain, readonly) NSManagedObjectModel *managedObjectModel;
@property (nonatomic, retain, readonly) NSPersistentStoreCoordinator *persistentStoreCoordinator;

@property (nonatomic, retain, readonly) NSManagedObjectContext   *threadManagedObjectContext;
@property (nonatomic,assign) id   <XXStoreDelegate> delegate;

/*
 * 1.0 初始化数据Mode和DB文件存储的地方
 */
- (void) setStoreMode:(NSString *)dataMode
            StorePath:(NSString *)storePath;

- (NSURL *)applicationDocumentsDirectory;

- (void)saveContext ;
- (void) resetPersistentStore;

- (NSManagedObject *)objectWithID:(NSManagedObjectID *)objectID;
- (BOOL) existedObject:(NSManagedObjectID*)objectID;
- (void)insertObject:(NSManagedObject *)object;
- (void)deleteObject:(NSManagedObject *)object;
- (NSManagedObject*) insertNewObjectForEntityForName:(NSString*)entityName;
- (void)deleteObjectById:(NSManagedObjectID *)objectID;
- (NSEntityDescription*) entityForName:(NSString*)entityName;
- (NSArray *)executeFetchRequest:(NSFetchRequest *)request error:(NSError **)error;

#pragma mark - ThreadNSManagedObjectContext
- (void)saveContextOnThread;
- (NSManagedObject*) insertNewObjectForEntityForNameOnThread:(NSString*)entityName;
- (NSArray *)executeFetchRequestOnThread:(NSFetchRequest *)request error:(NSError **)error;

- (void) addObserverObject:(NSManagedObjectContext *)childMoc;

@end
