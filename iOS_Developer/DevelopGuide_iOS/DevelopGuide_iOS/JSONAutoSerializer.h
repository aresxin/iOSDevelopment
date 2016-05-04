//
//  JSONAutoSerializer.h
//  TestOCRuntimeProgramming
//
//  Created by freeZn on 11-12-13.
//  Copyright (c) 2011年 __MyCompanyName__. All rights reserved.
//

/*
 * JSONAutoSerializer职责将对象封装成json格式
 * 单列模式
 * 1.将对象转换为字典
 * 2.调用NSObject+SBJSON.h的JSONRepresentation对象序列化方法将字典转换为json格式
 */

#import <Foundation/Foundation.h>

@interface JSONAutoSerializer : NSObject

+ (JSONAutoSerializer *)sharedSerializer;
- (NSString *)serializeObject:(id)theObject;
@end
