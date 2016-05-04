//
//  DataManager.h
//  ToyotaSalesService
//
//  Created by yangjinxin on 13-7-29.
//  Copyright (c) 2013年 xin. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface DataManager : NSObject
+ (DataManager*) sharedInstance;

/*
 * 1.0 从DB中查询数据
 */
- (void) asyncFetchRequestEntiry:(NSString *)entiryName
                    fetchRequest:(NSFetchRequest *)fetchRequest
               CompletionHandler:(void (^)(NSArray *results))block;

- (NSArray *) fetchRequestEntiry:(NSString *)entiryName
                    fetchRequest:(NSFetchRequest *)fetchRequest;

/*
 * 2.0 从DB中删除数据
 */
- (void) deleteObject:(NSManagedObjectID *)objectID;
- (void) deleteMultiObject:(NSArray*)objectIDs;

/*
 * 3.0 批量插入数据 
 * 可主线程中调用
 * 可子线程调用
 */
- (void) insertMultiObject:(NSArray *)objects
                    entity:(NSString *)entityName;
/*
 * 3.0 批量插入数据
 * 此方法是异步执行的
 */
- (void) asyncInsertMultiObject:(NSArray *)objects
                         entity:(NSString *)entityName;

@end
