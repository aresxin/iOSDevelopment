//
//  XXInvokeQueue.m
//  DevelopGuide_iOS
//
//  Created by yangjinxin on 13-4-10.
//
//

#import "XXInvokeQueue.h"

@implementation XXInvokeQueue

static XXInvokeQueue *invokQueue = nil;
+(id)shareInvok
{
    @synchronized(self) { 
        if(!invokQueue)
        {
            invokQueue=[[XXInvokeQueue alloc]init];
            
        }

    }
    return invokQueue;
}

-(id)init
{
    self = [super init];
    if (self)
    {
        invokeDic = [[NSMutableDictionary alloc] init];

    }
    
    return self;
}

-(void)setInvok:(id)target sel:(SEL)sel key:(NSString*)key
{
    if(target == nil) return;
    NSMethodSignature *sig=[target methodSignatureForSelector:sel];
    NSInvocation *invo=[NSInvocation invocationWithMethodSignature:sig];
    [invo setTarget:target];
    [invo setSelector:sel];
    [invokeDic setValue:invo forKey:key];
}

-(void)removeInvok:(NSString*)key
{
    [invokeDic removeObjectForKey:key];
}

-(NSInvocation*)selectInvok:(NSString *)key
{
    return [invokeDic valueForKey:key];
}

-(void)dealloc
{
    [invokeDic release];
    [super dealloc];
}
@end
