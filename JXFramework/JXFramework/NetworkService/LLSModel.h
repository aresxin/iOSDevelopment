//
//  LLSModel.h
//  LocationShare
//
//  Created by yangjinxin on 15/4/29.
//  Copyright (c) 2015年 LINE Corporation. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "LLSDataManager.h"


@class KeyMapper;
extern BOOL isValueNull(id value);

@interface LLSModel : NSObject

- (BOOL)isDummy;

- (void) setJSONIgnoreKeys:(NSArray *)keys;

- (instancetype)init;
+ (NSString *) className;
/**
 *将传入的对象字典映射为对象
 **/
+ (instancetype)objectFromObjDictionary:(NSDictionary*)dictionary;


/**
 *将传入的Json字典映射为对象
 **/
+ (instancetype)objectFromJsonDictionary:(NSDictionary*)dictionary;

/**
 将列表中的数据映射为对象的列表(需要在子类中重写此方法)
 **/
- (NSArray *)mapperObjListFromArray:(NSArray *)objList withName:(NSString*)propertyName withMapperFlag:(BOOL)mapperFlag;

/**
 *通过对象获取对应的字典信息
 **/
- (NSDictionary *)getObjDictionaryFromObj;

/**
 *通过对象获取对应的字典信息
 **/
- (NSDictionary *)getJsonDictionaryFromObj;

//将传入对象的值合并到当前对象上，对象类型要相同
//可以在子类中创建-merge<Key>FromModel:方法设定合并的规则，如果不是实现此方法，默认为替换指定的属性.
- (void)mergeValueFromModel:(LLSModel *)model;

- (NSString *)description;

+(KeyMapper *)keyMapper;

+(NSDictionary *)invalidKeys;
@end


@interface KeyMapper : NSObject
-(instancetype)initWithDictionary:(NSDictionary*)map;

- (NSString *)getDataKeyName:(NSString *)objPropertyName;
@end
