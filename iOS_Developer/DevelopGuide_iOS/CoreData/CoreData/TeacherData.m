//
//  TeacherData.m
//  CoreData
//
//  Created by yangjinxin on 13-7-30.
//  Copyright (c) 2013年 xin. All rights reserved.
//

#import "TeacherData.h"
#import "Teacher.h"
@implementation TeacherData
@synthesize tId;
@synthesize tName;

- (id) init
{
    self = [super init];
    if (self) {
        entityName = @"Teacher";
    }
    
    return self;
}

- (void) convertFromDBData:(Teacher *)data
{
    self.tId             = data.tId;
    self.tName           = data.tName;
    self.managedObjectID = data.objectID;
}

- (void) convertToDBData:(Teacher *)data
{
    data.tId   = self.tId;
    data.tName = self.tName;
}


@end
