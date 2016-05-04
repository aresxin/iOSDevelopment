//
//  NSObject+Property.h
//  JXFramework
//
//  Created by yangjinxin on 15/4/16.
//  Copyright (c) 2015年 yangjinxin. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface ClassPropertyInfo : NSObject
/** The name of the declared property*/
@property (copy, nonatomic) NSString* propertyName;

/** A property class type  */
@property (assign, nonatomic) Class propertyType;

/** Struct name if a struct */
@property (strong, nonatomic) NSString* structName;

@end

@interface NSObject (Property)

/* 获取对象的所有属性和值的字典*/
- (NSDictionary *) getPropertyNameValuePairDictionay;

/* 获取对象的所有属性和属性类型的字典*/
- (NSDictionary *) getPropertyNameTypePairDictionay;

- (void) setPropertyValue:(NSDictionary *)propertyDic;

@end

