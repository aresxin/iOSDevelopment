//
//  XXThread.h
//  DevelopGuide_iOS
//
//  Created by yangjinxin on 13-4-10.
//
//

#import <Foundation/Foundation.h>

@interface XXThread : NSObject {
    NSOperationQueue   *taskQueue;
}
- (void) creatNewOperationSelector:(SEL)sel
                          toTarget:(id)target
                        withObject:(id)object;
@end
