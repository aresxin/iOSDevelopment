//
//  LLSModel.m
//  LocationShare
//
//  Created by yangjinxin on 15/4/29.
//  Copyright (c) 2015年 LINE Corporation. All rights reserved.
//

#import "LLSModel.h"
#import "NSObject+Property.h"

extern BOOL isValueNull(id value)
{
    if (!value){
        return YES;
    }
    
    if ([value isKindOfClass:[NSNull class]]) {
        return YES;
    }
    return NO;
}

NSString* const ModelErrorDomain = @"ModelErrorDomain";

@interface LLSModel () {
    NSMutableDictionary *_ignoreKeys;
}
@end

@implementation LLSModel
- (instancetype)init
{
    self = [super init];
    return self;
}

- (BOOL)isDummy;
{
    return NO;
}

+ (NSString *) className
{
    return NSStringFromClass(self);
}

+ (instancetype)objectFromObjDictionary:(NSDictionary *)dictionary
{
    return [[self alloc] initWithDictionary:dictionary withMapperFlag:NO error:nil];
}

/**
 *通过传入的对象获取对象
 **/
+ (instancetype)objectFromJsonDictionary:(NSDictionary*)dictionary
{
    return [[self alloc] initWithDictionary:dictionary  withMapperFlag:YES error:nil];
}


- (instancetype)initWithDictionary:(NSDictionary *)dictionaryValue withMapperFlag:(BOOL)flag error:(NSError **)error
{
    if (dictionaryValue == nil) {
        if (error != nil) {
            *error = [NSError errorWithDomain:ModelErrorDomain
                                         code:0
                                     userInfo:@{NSLocalizedDescriptionKey:@"The dictionay is nil."}];
        }
        return nil;
    }
    
    if (![dictionaryValue isKindOfClass:[NSDictionary class]] ) {
        if (error != nil) {
            *error = [NSError errorWithDomain:ModelErrorDomain
                                         code:0
                                     userInfo:@{NSLocalizedDescriptionKey:@"The object is not dictionary."}];
        }
        return nil;
    }
    
    self = [self init];
    
    [self mapperDictionayValue:dictionaryValue toObj:self  withMapperFlag:flag error:error];
    return self;
}


- (BOOL) mapperDictionayValue:(NSDictionary *)dictionaryValue toObj:(id)obj withMapperFlag:(BOOL)mapperFlag error:(NSError **)error
{
    NSArray *propertyInfoList = [[self getPropertyNameTypePairDictionay] allValues];
    
    for (ClassPropertyInfo *info in propertyInfoList){
        if (info == nil) {
            continue;
        }
        
        NSString *propertyName = info.propertyName;
        
        NSString *dateKeyName = propertyName;
        
        if (mapperFlag) {
            dateKeyName = [self getDataKeyName:propertyName];
        }
        
        id itemValue = [dictionaryValue objectForKey:dateKeyName];
        
        //handle primitives
        if (info.propertyType == nil && info.structName==nil) {
            [obj setValue:itemValue forKey:propertyName];
            
            //skip directly to the next key
            continue;
        }
        
        
        // handle nils
        if (isValueNull(itemValue)) {
            [obj setValue:nil forKey:propertyName];
            continue;
        }
        
        NSString *propertyType = NSStringFromClass(info.propertyType) ;
        if([propertyType isEqualToString:NSStringFromClass([NSString class])]) {
            [obj setValue:itemValue forKey:propertyName];
        }else if ([propertyType isEqualToString:NSStringFromClass([NSNumber class])]) {
            [obj setValue:itemValue forKey:propertyName];
        }else if ([propertyType isEqualToString:NSStringFromClass([NSArray class])]) {
            NSArray *objList = [self mapperObjListFromArray:itemValue withName:propertyName withMapperFlag:mapperFlag];
            if (objList != nil) {
                [obj setValue:objList forKey:propertyName];
            }
        }else if ([propertyType isEqualToString:NSStringFromClass([NSDictionary class])]) {
            [obj setValue:itemValue forKey:propertyName];
        }else if ([info.propertyType isSubclassOfClass:[LLSModel class]]){ //check if property is itself a KModelObj
            NSError* initErr = nil;
            id value = [[info.propertyType alloc] initWithDictionary:itemValue withMapperFlag:mapperFlag error:&initErr];
            [obj setValue:value forKey:propertyName];
        }else{
            [obj setValue:itemValue forKey:propertyName];
        }
    }
    return YES;
}

- (NSString *) getDataKeyName:(NSString *)propertyName
{
    id mapper = [[self class] keyMapper];
    
    if (mapper == nil) {
        return propertyName;
    }
    
    if ([mapper isKindOfClass:[KeyMapper class]] == NO) {
        return propertyName;
    }
    
    KeyMapper *keyMapper = (KeyMapper *)mapper;
    
    NSString *dataKey = [keyMapper getDataKeyName:propertyName];
    return dataKey == nil?propertyName:dataKey;
}

- (BOOL) isDataKeyName:(NSString *)propertyName
{
    NSDictionary *invalidKeys = [[self class] invalidKeys];
    if (invalidKeys == nil) {
        return YES;
    }
    
    BOOL isInvalid  = [[invalidKeys objectForKey:propertyName] boolValue];
    if (!isInvalid) {
        return YES;
    }
    
    return NO;
}

- (BOOL) isIgnoreKey:(NSString *)propertyName
{
    if (!_ignoreKeys || ![[_ignoreKeys allKeys] count]) {
        return NO;
    }
    
    BOOL isIgnore  = [[_ignoreKeys objectForKey:propertyName] boolValue];
    if (isIgnore) {
        return YES;
    }
    
    return NO;
}


- (NSArray *)mapperObjListFromArray:(NSArray *)objList withName:(NSString*)propertyName withMapperFlag:(BOOL)mapperFlag
{
    return objList;
}

- (NSDictionary *)getObjDictionaryFromObj
{
    return [self getDictionayWithMapperFlag:NO];
}

/**
 *通过对象获取对应的字典信息
 **/
- (NSDictionary *)getJsonDictionaryFromObj
{
    return [self getDictionayWithMapperFlag:YES];
}


- (NSDictionary *)getDictionayWithMapperFlag:(BOOL)mapperFlag
{
    NSMutableDictionary *propertiesDictionay = [NSMutableDictionary dictionary];
    
    
    NSDictionary *dictionaryValue = [self getPropertyNameValuePairDictionay];
    
    NSArray *propertyInfoList = [[self getPropertyNameTypePairDictionay] allValues];
    
    
    for (ClassPropertyInfo *info in propertyInfoList){
        if (info == nil) {
            continue;
        }
        
        NSString *propertyName = info.propertyName;
        // check is need change property to dictionary
        if (![self isDataKeyName:propertyName]) {
            continue;
        }
        
        if ([self isIgnoreKey:propertyName]) {
            continue;
        }
        
        NSString *dataKeyName = propertyName;
        
        if (mapperFlag) {
            dataKeyName = [self getDataKeyName:propertyName];
        }
        
        id itemValue = [dictionaryValue objectForKey:propertyName];
        
        //handle primitives
        if (info.propertyType == nil && info.structName==nil) {
            [propertiesDictionay setValue:itemValue forKey:propertyName];
            continue;
        }
        
        
        // handle nils
        if (isValueNull(itemValue)) {
            continue;
        }
        
        NSString *propertyType = NSStringFromClass(info.propertyType) ;
        if([propertyType isEqualToString:NSStringFromClass([NSString class])]) {
            [propertiesDictionay setValue:itemValue forKey:dataKeyName];
        }else if ([propertyType isEqualToString:NSStringFromClass([NSNumber class])]) {
            [propertiesDictionay setValue:itemValue forKey:dataKeyName];
        }else if ([propertyType isEqualToString:NSStringFromClass([NSArray class])]) {
            
            NSMutableArray *list = [NSMutableArray array];
            for (id obj in itemValue) {
                if ([obj isKindOfClass:[LLSModel class]]) {
                    LLSModel *kModel = (LLSModel *)obj;
                    NSDictionary *dictionay = [kModel getObjDictionaryFromObj];
                    
                    if (dictionay != nil) {
                        [list addObject:dictionay];
                    }
                }else{
                    [list addObject:obj];
                }
            }
            
            if ([list count] > 0) {
                [propertiesDictionay setValue:list forKey:dataKeyName];
            }
            
        }else if ([propertyType isEqualToString:NSStringFromClass([NSDictionary class])]) {
            [propertiesDictionay setValue:itemValue forKey:dataKeyName];
        }else if ([info.propertyType isSubclassOfClass:[LLSModel class]]){ //check if property is itself a KModelObj
            id value = [itemValue getObjDictionaryFromObj];
            [propertiesDictionay setValue:value forKey:dataKeyName];
        }else{
            if ([info.structName isEqualToString:@"BOOL"]) {
                NSNumber *numberBOOL = [NSNumber numberWithBool:NO];
                if ([itemValue boolValue]) {
                    numberBOOL = [NSNumber numberWithBool:YES];
                }
                [propertiesDictionay setValue:numberBOOL forKey:dataKeyName];
            } else{
                [propertiesDictionay setValue:itemValue forKey:dataKeyName];
            }
            
        }
    }
    
    _ignoreKeys = nil;
    
    return propertiesDictionay;
    
}

- (void)mergeValueFromModel:(LLSModel *)model
{
    NSDictionary *targetPropertyinfoDic = [self getPropertyNameTypePairDictionay];
    NSArray *targetkeyList = [targetPropertyinfoDic allKeys];
    
    NSDictionary *sourcePropertyInfoDic = [model getPropertyNameTypePairDictionay];
    NSArray *sourceKeyList = [sourcePropertyInfoDic allKeys];
    
    for (NSString *key in targetkeyList) {
        
        if ([sourceKeyList containsObject:key] == NO) {
            continue;
        }
        
        SEL selector = selectorWithCapitalizedKeyPattern("merge", key, "FromModel:");
        if (![self respondsToSelector:selector]) {
            if (model != nil) {
                [self setValue:[model valueForKey:key] forKey:key];
            }
            continue;
        }
        
        NSInvocation *invocation = [NSInvocation invocationWithMethodSignature:[self methodSignatureForSelector:selector]];
        invocation.target = self;
        invocation.selector = selector;
        
        [invocation setArgument:&model atIndex:2];
        [invocation invoke];
    }
    
}

- (instancetype)copyWithZone:(NSZone *)zone {
    NSDictionary *objDic = [self getObjDictionaryFromObj];
    return [[self.class allocWithZone:zone] initWithDictionary:objDic withMapperFlag:NO error:NULL];
}

- (NSString *)description
{
    NSDictionary *nameAndValueDic = [self getObjDictionaryFromObj];
    return [NSString stringWithFormat:@"<%@: %p> %@", self.class, self, nameAndValueDic];
}

- (void)setValue:(id)value forUndefinedKey:(NSString *)key
{
    NSLog(@"%s[%d] undefined key[%@]", __FILE__, __LINE__, key);
}

- (void)setValue:(id)value forKey:(NSString *)key
{
    if (value == nil || [value isKindOfClass:[NSNull class]])
    {
        return;
    }
    [super setValue:value forKey:key];
}


SEL selectorWithCapitalizedKeyPattern(const char *prefix, NSString *key, const char *suffix) {
    NSUInteger prefixLength = strlen(prefix);
    NSUInteger suffixLength = strlen(suffix);
    
    NSString *initial = [key substringToIndex:1].uppercaseString;
    NSUInteger initialLength = [initial maximumLengthOfBytesUsingEncoding:NSUTF8StringEncoding];
    
    NSString *rest = [key substringFromIndex:1];
    NSUInteger restLength = [rest maximumLengthOfBytesUsingEncoding:NSUTF8StringEncoding];
    
    char selector[prefixLength + initialLength + restLength + suffixLength + 1];
    memcpy(selector, prefix, prefixLength);
    
    BOOL success = [initial getBytes:selector + prefixLength maxLength:initialLength usedLength:&initialLength encoding:NSUTF8StringEncoding options:0 range:NSMakeRange(0, initial.length) remainingRange:NULL];
    if (!success){
        return NULL;
    }
    
    success = [rest getBytes:selector + prefixLength + initialLength maxLength:restLength usedLength:&restLength encoding:NSUTF8StringEncoding options:0 range:NSMakeRange(0, rest.length) remainingRange:NULL];
    if (!success) {
        return NULL;
    }
    
    memcpy(selector + prefixLength + initialLength + restLength, suffix, suffixLength);
    selector[prefixLength + initialLength + restLength + suffixLength] = '\0';
    
    return sel_registerName(selector);
}

+(KeyMapper *)keyMapper
{
    return nil;
}

+(NSDictionary *)invalidKeys
{
    return nil;
}

- (void) setJSONIgnoreKeys:(NSArray *)keys
{
    if (![keys count]) {
        return;
    }
    
    _ignoreKeys = [NSMutableDictionary dictionary];
    
    for (NSString *key in keys) {
        [_ignoreKeys setObject:@"YES" forKey:key];
    }
    
}

@end


@interface KeyMapper()
@property (nonatomic, strong) NSMutableDictionary *modleToDataMap;
@end

@implementation KeyMapper
@synthesize modleToDataMap;

-(instancetype)initWithDictionary:(NSDictionary*)map
{
    self = [super init];
    if (self) {
        modleToDataMap = [NSMutableDictionary dictionaryWithDictionary:map];
    }
    return self;
}


- (NSString *)getDataKeyName:(NSString *)objPropertyName
{
    if (modleToDataMap == nil) {
        return nil;
    }
    
    return [modleToDataMap objectForKey:objPropertyName];
    
}

@end



