//
//  NSObject+PropertyListing.m
//  DevelopGuide_iOS
//
//  Created by clay on 13-1-9.
//
//

#import "NSObject+PropertyListing.h"

@implementation NSObject (PropertyListing)
/* 获取对象的所有属性 */
- (NSMutableDictionary *)properties_aps
{
    NSMutableDictionary *props = [NSMutableDictionary dictionary];
    unsigned int outCount, i;
    objc_property_t *properties = class_copyPropertyList([self class], &outCount);
    for (i = 0; i<outCount; i++)
    {
        objc_property_t property = properties[i];
        const char* char_f =property_getName(property);
        NSString *propertyName = [NSString stringWithUTF8String:char_f];
        id propertyValue = [self valueForKey:(NSString *)propertyName];
        if (propertyValue) [props setObject:propertyValue forKey:propertyName];
    }
    free(properties);
    return props;
}

/* 获取对象keys */
- (NSArray *) getAllKeys
{
    NSMutableArray *keys = [NSMutableArray array];
    unsigned int outCount, i;
    objc_property_t *properties = class_copyPropertyList([self class], &outCount);
    for (i = 0; i<outCount; i++)
    {
        objc_property_t property = properties[i];
        const char* char_f =property_getName(property);
        NSString *propertyName = [NSString stringWithUTF8String:char_f];
        
        [keys addObject:propertyName];
    }
    free(properties);
    return keys;

}

/* 获取对象的所有方法 */
-(void)printMothList
{
    unsigned int mothCout_f =0;
    Method* mothList_f = class_copyMethodList([self class],&mothCout_f);
    for(int i=0;i<mothCout_f;i++)
    {
        Method temp_f = mothList_f[i];
        //IMP imp_f = method_getImplementation(temp_f);
        //SEL name_f = method_getName(temp_f);
        const char* name_s =sel_getName(method_getName(temp_f));
        int arguments = method_getNumberOfArguments(temp_f);
        const char* encoding =method_getTypeEncoding(temp_f);
        NSLog(@"方法名：%@,参数个数：%d,编码方式：%@",[NSString stringWithUTF8String:name_s],
              arguments,
              [NSString stringWithUTF8String:encoding]);
    }
    free(mothList_f);
}

- (void) getPropertiesFrom:(NSMutableDictionary *)propertyDic
{
    if (!propertyDic)
    {
        return;
    }
    
    unsigned int outCount, i;
    objc_property_t *properties = class_copyPropertyList([self class], &outCount);
    for (i = 0; i<outCount; i++)
    {
        objc_property_t property = properties[i];
        const char* char_f =property_getName(property);
        // get 属性名
        NSString *propertyName = [NSString stringWithUTF8String:char_f];
        // 从字典里取出值
        id value = [propertyDic objectForKey:propertyName];
        // 如果字典里有这个值给对象赋值
        if (value)
        {
            [self setValue:value forKey:propertyName];
        }
    }
    
    free(properties);
}

- (id) getPropertiesValue:(NSString *)propertyName
{
    id propertyValue = nil;
    
    unsigned int outCount, i;
    objc_property_t *properties = class_copyPropertyList([self class], &outCount);
    for (i = 0; i<outCount; i++)
    {
        objc_property_t property = properties[i];
        const char* char_f =property_getName(property);
        // get 属性名
        NSString *name = [NSString stringWithUTF8String:char_f];
       
        if ([name isEqualToString:propertyName])
        {
            propertyValue = [self valueForKey:(NSString *)propertyName];
            
            break;
        }
    }
    
    free(properties);

    
    return propertyValue;
}

// 根据字符串获得属性值
- (id) getPropertyValue:(NSString *)propertyName
{
    if (!propertyName)
    {
        return nil;
    }
    
    id propertyValue = nil;
    const char *char_propertyName = [propertyName cStringUsingEncoding:NSUTF8StringEncoding];
    objc_property_t property = class_getProperty([self class], char_propertyName);
    //
    //    const char* char_f =property_getName(property);
    //    // get 属性名
    //    NSString *name = [NSString stringWithUTF8String:char_f];
    
    if (property != NULL) {
        propertyValue = [self valueForKey:(NSString *)propertyName];
    }
    
    return propertyValue;
}

// 设定一个属性的值
- (void) setPropertyValue:(NSMutableDictionary *)propertyDic
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
