//
//  PeopleObject.m
//  DevelopGuide_iOS
//
//  Created by xin on 12-3-27.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "PeopleObject.h"

@implementation PeopleObject
@synthesize name_;
@synthesize arge_;

- (id) init {
    self = [super init];
    if (self) {
        self.name_ = nil;
        self.arge_ = -1;
    }
    return self;
}

- (id) initWithName:(NSString *)name Arge:(NSInteger)arge {
    self = [super init];
    if (self) {
        self.name_ = name;
        self.arge_ = arge;
    }
    return self;
}

// 从coder获取数据（解码）
- (id) initWithCoder: (NSCoder *)coder  
{  
    if (self = [super init])  
    {  
        self.name_ = [coder decodeObjectForKey:@"name_"];
        self.arge_ = [coder decodeIntForKey:@"arge_"];
    }  
    return self;  
}  

// 将数据放进coder中 （编码）
- (void) encodeWithCoder: (NSCoder *)coder  
{  
    [coder encodeObject:name_ forKey:@"name_"];
    [coder encodeInt:arge_ forKey:@"arge_"];
}  

- (void) dealloc 
{
    [name_ release];
    [super dealloc];
}

@end
