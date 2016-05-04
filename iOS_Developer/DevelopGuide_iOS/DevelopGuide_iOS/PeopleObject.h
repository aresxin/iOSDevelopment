//
//  PeopleObject.h
//  DevelopGuide_iOS
//
//  Created by xin on 12-3-27.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

/*
 * 自定义对象要想实现NSkeyedArchive和NSkeyedUnArchive,
 * 必须实现NSCoding协议
 */

#import <Foundation/Foundation.h>

@interface PeopleObject : NSObject <NSCoding>{
    NSString    *name_;
    int         arge_;
}
@property (nonatomic, copy) NSString    *name_;
@property (assign)  int arge_;
- (id) initWithName:(NSString *)name Arge:(NSInteger)arge;
@end
