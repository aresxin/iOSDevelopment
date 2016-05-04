//
//  XXInvokeQueue.h
//  DevelopGuide_iOS
//
//  Created by yangjinxin on 13-4-10.
//
//

#import <Foundation/Foundation.h>

@interface XXInvokeQueue : NSObject {
    NSMutableDictionary *invokeDic;  //保存NSInvocation
}

+ (id)shareInvok;
- (void)setInvok:(id)target sel:(SEL)sel key:(NSString*)key;//生成一个NSInvocation
- (void)removeInvok:(NSString*)key;              //删除一个NSInvocation
- (NSInvocation*)selectInvok:(NSString *)key;   //查询NSInvocation,如果没有返回空
@end
