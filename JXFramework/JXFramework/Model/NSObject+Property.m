//
//  NSObject+Property.m
//  JXFramework
//
//  Created by yangjinxin on 15/4/16.
//  Copyright (c) 2015年 yangjinxin. All rights reserved.
//

#import "NSObject+Property.h"

#import "NSObject+Property.h"
#import <objc/runtime.h>


@implementation ClassPropertyInfo

@synthesize propertyName;
@synthesize propertyType;
@synthesize structName;

@end

@implementation NSObject (Property)

- (NSDictionary *)getPropertyNameValuePairDictionay
{
    NSMutableDictionary *props = [NSMutableDictionary dictionary];
    Class currentClass = [self class];
    
    while (currentClass != [NSObject class]) {
        NSDictionary *propertyDic = [self getNameAndValueDicFromClass:currentClass];
        if (propertyDic != nil) {
            [props addEntriesFromDictionary:propertyDic];
        }
        currentClass = [currentClass superclass];
    }
    
    return props;
}


- (NSDictionary *)getNameAndValueDicFromClass:(Class)class
{
    NSMutableDictionary *props = [NSMutableDictionary dictionary];
    unsigned int outCount, i;
    objc_property_t *properties = class_copyPropertyList(class, &outCount);
    for (i = 0; i<outCount; i++)
    {
        objc_property_t property = properties[i];
        const char* char_f = property_getName(property);
        NSString *propertyName = [NSString stringWithUTF8String:char_f];
        id propertyValue = [self valueForKey:(NSString *)propertyName];
        if (propertyValue){
            [props setObject:propertyValue forKey:propertyName];
        }
        
    }
    free(properties);
    return props;
}


- (NSDictionary *) getPropertyNameTypePairDictionay
{
    NSMutableDictionary *props = [NSMutableDictionary dictionary];
    Class currentClass = [self class];
    while (currentClass != [NSObject class]) {
        NSDictionary *propertyDic = [self getPropertyNameAndTypeFromClass:currentClass];
        if (propertyDic != nil) {
            [props addEntriesFromDictionary:propertyDic];
        }
        currentClass = [currentClass superclass];
    }
    return props;
    
}

- (NSDictionary *)getPropertyNameAndTypeFromClass:(Class)class
{
    NSMutableDictionary *props = [NSMutableDictionary dictionary];
    unsigned int outCount;
    objc_property_t *properties = class_copyPropertyList(class, &outCount);
    NSScanner* scanner = nil;
    NSString* propertyType = nil;
    for (unsigned int i = 0; i < outCount; i++) {
        
        ClassPropertyInfo* classPropertyInfo = [[ClassPropertyInfo alloc] init];
        
        //get property name
        objc_property_t property = properties[i];
        const char *propertyName = property_getName(property);
        classPropertyInfo.propertyName = @(propertyName);
        
        
        //get property attributes
        const char *attrs = property_getAttributes(property);
        NSString* propertyAttributes = @(attrs);
        NSArray* attributeItems = [propertyAttributes componentsSeparatedByString:@","];
        
        //ignore read-only properties
        if ([attributeItems containsObject:@"R"]) {
            continue; //to next property
        }
        
        //check for 64b BOOLs
        if ([propertyAttributes hasPrefix:@"Tc,"]) {
            //mask BOOLs as structs so they can have custom convertors
            classPropertyInfo.structName = @"BOOL";
        }
        
        scanner = [NSScanner scannerWithString: propertyAttributes];
        
        [scanner scanUpToString:@"T" intoString:nil];
        [scanner scanString:@"T" intoString:nil];
        
        //check if the property is an instance of a class
        if ([scanner scanString:@"@\"" intoString:&propertyType]) {
            
            [scanner scanUpToCharactersFromSet:[NSCharacterSet characterSetWithCharactersInString:@"\"<"]
                                    intoString:&propertyType];
            
            classPropertyInfo.propertyType = NSClassFromString(propertyType);
        }
        //check if the property is a structure
        else if ([scanner scanString:@"{" intoString: &propertyType]) {
            [scanner scanCharactersFromSet:[NSCharacterSet alphanumericCharacterSet]
                                intoString:&propertyType];
            classPropertyInfo.structName = propertyType;
        }
        //the property must be a primitive
        else {
            
            //the property contains a primitive data type
            [scanner scanUpToCharactersFromSet:[NSCharacterSet characterSetWithCharactersInString:@","]
                                    intoString:&propertyType];
            
            //get the full name of the primitive type
            NSDictionary *primitivesNames = @{@"f":@"float", @"i":@"int", @"d":@"double", @"l":@"long", @"c":@"BOOL", @"s":@"short", @"q":@"long",@"I":@"NSInteger", @"Q":@"NSUInteger", @"B":@"BOOL", @"@?":@"Block"};
            propertyType = [primitivesNames objectForKey:propertyType];
            //classPropertyInfo.propertyType = NSClassFromString(propertyType);
        }
        
        //add the property object to the temp index
        if (classPropertyInfo) {
            [props setValue:classPropertyInfo forKey:classPropertyInfo.propertyName];
            
        }
    }
    free(properties);
    return props;
    
}

// 设定一个属性的值
- (void) setPropertyValue:(NSDictionary *)propertyDic
{
    if (!propertyDic && [propertyDic count] > 0)
    {
        return;
    }
    
    NSString *key = [[propertyDic allKeys] objectAtIndex:0];
    id value = [propertyDic objectForKey:key];
    
    const char *char_propertyName = [key cStringUsingEncoding:NSUTF8StringEncoding];
    objc_property_t property = class_getProperty([self class], char_propertyName);
    if (property != NULL)
    {
        [self setValue:value forKey:key];
    }
}


@end

