//
//  StudentData.h
//  CoreData
//
//  Created by yangjinxin on 13-7-30.
//  Copyright (c) 2013年 xin. All rights reserved.
//

#import "DBModelMap.h"

@interface StudentData : DBModelMap
@property (nonatomic, strong) NSNumber *sId;
@property (nonatomic, strong) NSString *sName;
@end
