//
//  StudentData.m
//  CoreData
//
//  Created by yangjinxin on 13-7-30.
//  Copyright (c) 2013年 xin. All rights reserved.
//

#import "StudentData.h"
#import "Student.h"
@implementation StudentData
@synthesize sId;
@synthesize sName;

- (id) init
{
    self = [super init];
    if (self) {
        entityName = @"Student";
    }
    
    return self;
}


- (void) convertFromDBData:(Student *)data
{
    self.sId             = data.sId;
    self.sName           = data.sName;
    self.managedObjectID = data.objectID;
}

- (void) convertToDBData:(Student *)data
{
    data.sId   = self.sId;
    data.sName = self.sName;
}


@end
