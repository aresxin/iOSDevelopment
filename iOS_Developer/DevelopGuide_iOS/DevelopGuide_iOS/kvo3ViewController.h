//
//  kvo3ViewController.h
//  DevelopGuide_iOS
//
//  Created by yangjinxin on 13-4-22.
//
//

#import <UIKit/UIKit.h>

@interface kvo3 : NSObject {
    NSString   *name;
    NSString   *num;

}
@property (nonatomic, retain)  NSString   *name;
@property (nonatomic, retain)  NSString   *num;
@end

@interface kvo3ViewController : UIViewController {
    kvo3  *k3;

}
@property (nonatomic, retain) kvo3 *k3;
@end
