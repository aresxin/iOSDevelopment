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


/*
 * 2.0 从DB中删除数据
 */
- (void) deleteObject:(NSManagedObjectID *)objectID;
- (void) deleteMultiObject:(NSArray*)objectIDs;
@end
