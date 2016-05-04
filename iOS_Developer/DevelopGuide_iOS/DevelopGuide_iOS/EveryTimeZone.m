//
//  EveryTimeZone.m
//  timeZoneViewer
//
//  Created by wang.pp on 11-12-19.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#import "EveryTimeZone.h"


@implementation EveryTimeZone

//获取所有时区以及时区时间
+(NSArray*) getAllTimeWithZone
{
    NSMutableArray* arrayTZ = [[NSMutableArray alloc] init];
    
    NSDate *nowDate = [NSDate new];
    NSDateFormatter *formatter	=  [[NSDateFormatter alloc] init];
   [formatter	setDateFormat:@"yyyy/MM/dd HH:mm:ss"];
   //	根据时区名字获取当前时间，如果该时区不存在，默认获取系统当前时区的时间
   //	NSTimeZone* timeZone = [NSTimeZone timeZoneWithName:@"Europe/Andorra"];	
  //	[formatter setTimeZone:timeZone];
   //获取所有的时区名字
  NSArray *array = [NSTimeZone knownTimeZoneNames];
   //	NSLog(@"array:%@",array);
   //for循环
  //	for(int i=0;i<[array count];i++)
  //	{
  //		NSTimeZone* timeZone = [NSTimeZone timeZoneWithName:[array objectAtIndex:i]];
  //		[formatter setTimeZone:timeZone];
  //		NSString *locationTime = [formatter stringFromDate:nowDate];
   //		NSLog(@"时区名字:%@   : 时区当前时间: %@",[array objectAtIndex:i],locationTime);
  //		//NSLog(@"timezone name is:%@",[array objectAtIndex:i]);
  //	}	
  //快速枚举法
    
 
    
  for(NSString *timeZoneName in array){
      
      NSMutableDictionary* dict = [[NSMutableDictionary alloc] init];
      
      [formatter setTimeZone:[NSTimeZone timeZoneWithName:timeZoneName]];
      
      [dict setValue:[formatter stringFromDate:nowDate] forKey:timeZoneName];
      
      [arrayTZ  addObject:dict];
      
       NSLog(@"%@,%@",timeZoneName,[formatter stringFromDate:nowDate]);
      
      [dict release];
   }
    
    
   [formatter release];
   [nowDate release];
    
  return [arrayTZ autorelease];
    
}

// 根据时区名获取时区时间
+(NSString*) getTimeWithSpecialZone:(NSString*)zoneName
{
    NSDate* nowDate = [NSDate new];
    
    NSDateFormatter* formatter = [[NSDateFormatter alloc] init];
    
    [formatter setDateFormat:@"yyyy/MM/dd HH:mm:ss"];
    
    NSTimeZone* timezone = [NSTimeZone timeZoneWithName:zoneName];
    
    [formatter setTimeZone:timezone];
    
    NSString* locationTime = [formatter stringFromDate:nowDate];
    
    [formatter release];
    [nowDate release];
    
    return locationTime;    
}

@end
