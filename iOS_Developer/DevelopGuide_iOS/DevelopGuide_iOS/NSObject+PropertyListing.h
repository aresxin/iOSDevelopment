//
//  NSObject+PropertyListing.h
//  DevelopGuide_iOS
//
//  Created by clay on 13-1-9.
//
//

#import <Foundation/Foundation.h>
#import <objc/runtime.h>

@interface NSObject (PropertyListing)
/* 获取对象的所有属性 */
- (NSMutableDictionary *)properties_aps;
/* 获取对象的所有方法 */
-(void)printMothList;
/* 从字典里获取对象的值 */
- (void) getPropertiesFrom:(NSMutableDictionary *)propertyDic;
/* 根据字符传获得对应属性的值  */
- (id)   getPropertiesValue:(NSString *)propertyName;
- (id) getPropertyValue:(NSString *)propertyName;
- (void) setPropertyValue:(NSMutableDictionary *)propertyDic;

/*获取对象的key值数组*/
- (NSArray *) allKeys;
@end
