//
//  DBModelMap.h
//  ToyotaSalesService
//
//  Created by yangjinxin on 13-6-13.
//  Copyright (c) 2013年 xin. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "JsonAndObjectTransformProtocol.h"

#import "NSObject+PropertyListing.h"


@interface DBModelMap : NSObject <JsonAndObjectTransformProtocol> {
    __strong NSString   *entityName;
    __strong NSString   *uniqueId;
    
}
@property (nonatomic, retain) NSManagedObjectID * managedObjectID;

#pragma mark -
#pragma mark webService json mapping
// 将Model打包成json字典
+ (NSArray *)packageJsonData:(NSArray *)dataModel;
// 将json字典解析成model并到数据库
+ (NSArray *)decoderJsonData:(NSArray *)dataModel isSaveDB:(BOOL)save;

#pragma mark -
#pragma mark DB mapping
- (void) convertFromDBData:(NSManagedObject *)data;
- (void) convertToDBData:(NSManagedObject *)data;
// 将数据库数据转换为Map数据
+ (NSArray *) getMapDatasFromDBModels:(NSArray *)models;

- (BOOL) isHasExisted;
- (void) saveToDB;
- (NSManagedObject *) insertToDB;
- (void) upDateToDB;
- (void) deleteFromDB;
@end
