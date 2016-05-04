//
//  Teacher.h
//  CoreData
//
//  Created by yangjinxin on 13-7-30.
//  Copyright (c) 2013年 xin. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreData/CoreData.h>


@interface Teacher : NSManagedObject

@property (nonatomic, retain) NSNumber * tId;
@property (nonatomic, retain) NSString * tName;

@end
