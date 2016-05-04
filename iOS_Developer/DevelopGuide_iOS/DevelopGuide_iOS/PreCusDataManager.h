//
//  PreCusDataManager.h
//  DevelopGuide_iOS
//
//  Created by yangjinxin on 13-4-3.
//
//

#import <Foundation/Foundation.h>
@class PreCustomer;
@class PreCustomerObject;

@interface PreCusDataManager : NSObject
+ (PreCusDataManager*)sharedInstance;
/// 查询所有数据
//- (PreCustomer *)
// save接口
- (PreCustomer *) insertPreCustomer:(PreCustomerObject *)preCus;
@end
