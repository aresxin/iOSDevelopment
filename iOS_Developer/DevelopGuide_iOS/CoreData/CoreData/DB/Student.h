//
//  Student.h
//  CoreData
//
//  Created by yangjinxin on 13-7-30.
//  Copyright (c) 2013年 xin. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreData/CoreData.h>


@interface Student : NSManagedObject

@property (nonatomic, retain) NSNumber * sId;
@property (nonatomic, retain) NSString * sName;

@end
