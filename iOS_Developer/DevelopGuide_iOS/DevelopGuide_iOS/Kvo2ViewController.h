//
//  Kvo2ViewController.h
//  DevelopGuide_iOS
//
//  Created by yangjinxin on 13-4-22.
//
//

#import <UIKit/UIKit.h>
@interface kvo2 : NSObject {
    NSString   *name;
    NSString   *num;
}
@property (nonatomic, retain)  NSString   *name;
@property (nonatomic, retain)  NSString   *num;
@end

@interface Kvo2ViewController : UIViewController {
    kvo2  *k2;
}
@property (nonatomic, retain) kvo2 *k2;
@end
