//
//  JSONAutoSerializer.m
//  TestOCRuntimeProgramming
//
//  Created by freeZn on 11-12-13.
//  Copyright (c) 2011年 __MyCompanyName__. All rights reserved.
//

#import "JSONAutoSerializer.h"
#import <Foundation/NSObjCRuntime.h>
#import <objc/runtime.h>
#import "JSON.h"

@implementation JSONAutoSerializer
static JSONAutoSerializer *_sharedSerializer = nil;

- (NSString *)serializeObject:(id)theObject
{
    NSString *className = NSStringFromClass([theObject class]);
    
    const char *cClassName = [className UTF8String];
    
    id theClass = objc_getClass(cClassName);
    
    unsigned int outCount, i;
    
    objc_property_t *properties = class_copyPropertyList(theClass, &outCount);
    
    NSMutableArray *propertyNames = [[NSMutableArray alloc] initWithCapacity:1];
    
    for (i = 0; i < outCount; i++) {
        
        objc_property_t property = properties[i];
        
        NSString *propertyNameString = [[NSString alloc] initWithCString:property_getName(property) encoding:NSUTF8StringEncoding]; 
        
        [propertyNames addObject:propertyNameString];
        
        [propertyNameString release];
        
        NSLog(@"－－－%s %s\n", property_getName(property), property_getAttributes(property));
        
    }
    
    NSMutableDictionary *finalDict = [[NSMutableDictionary alloc] initWithCapacity:1];
    
    // 遍历属性名数组
    for(NSString *key in propertyNames)
    {
        SEL selector = NSSelectorFromString(key);
        id value = [theObject performSelector:selector];
        
        if (value == nil)
        {
            value = [NSNull null];
        }
        
        [finalDict setObject:value forKey:key];
    }
    
    [propertyNames release];
    
   // NSString *retString = [[CJSONSerializer serializer] serializeDictionary:finalDict];
    NSString *retString = [finalDict  JSONRepresentation];
    [finalDict release];
    
    return retString;

}

+ (JSONAutoSerializer *)sharedSerializer
{
    if (_sharedSerializer == nil)
    {
        
        _sharedSerializer = [[JSONAutoSerializer alloc] init];
    
    }
    

    return _sharedSerializer;
}

- (id)init
{
    self = [super init];
    
    if (self)
    {
        
        
    
    }

    return self;
}

- (void)dealloc
{
    [super dealloc];

}

@end
