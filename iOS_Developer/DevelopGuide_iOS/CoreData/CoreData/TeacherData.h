//
//  TeacherData.h
//  CoreData
//
//  Created by yangjinxin on 13-7-30.
//  Copyright (c) 2013年 xin. All rights reserved.
//

#import "DBModelMap.h"

@interface TeacherData : DBModelMap
@property (nonatomic, strong) NSNumber *tId;
@property (nonatomic, strong) NSString *tName;
@end
