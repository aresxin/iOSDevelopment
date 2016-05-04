//
//  JOSNParse.m
//  DevelopGuide_iOS
//
//  Created by neusoft  on 11-12-20.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#import "JOSNParse.h"
#import "JSON.h"

@implementation JOSNParse

+ (NSArray *) parseJOSNData:(NSData *)data withRootKey:(NSString *)key
{
    NSString *josnString = [[NSString alloc] initWithData:data 
                                                 encoding:NSUTF8StringEncoding];
    // 解析json
    NSMutableDictionary *dic = [josnString JSONValue];
    NSArray *jsonArray = [dic objectForKey:key];
    [josnString release];
    
    if ([jsonArray count] > 0) {
         return jsonArray;
    }
    return nil;
}

+ (NSString *) parseJOSN
{
    // 得到资源文件路径
    NSString *path = [[NSBundle mainBundle] pathForResource:@"test" ofType:@"json"];
    
    // 得到json源文件字符串
    NSString *jsonString = [[NSString alloc] initWithContentsOfFile:path encoding:NSUTF8StringEncoding error:nil];
    
    
    // 解析json
    NSMutableDictionary *dic = [jsonString JSONValue];
    NSArray *jsonArray = [dic objectForKey:@"result"];
    
    NSMutableString *json = [[NSMutableString alloc] init];
    
    for (int i = 0; i < [jsonArray count]; i++) {
        NSDictionary *_dic = [jsonArray objectAtIndex:i];
        
        NSDictionary *meeting = [_dic objectForKey:@"meeting"];
        
        [json appendString:[NSString stringWithFormat:@"地址是：%@  创建者是：%@ \n",[meeting objectForKey:@"addr"],[meeting objectForKey:@"creator"]]];
    }
    
    NSLog(@"parse josn string is ---%@",json);
    return [json autorelease];
}
@end
