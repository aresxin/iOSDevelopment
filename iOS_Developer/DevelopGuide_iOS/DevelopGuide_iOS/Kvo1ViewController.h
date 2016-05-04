//
//  Kvo1ViewController.h
//  DevelopGuide_iOS
//
//  Created by yangjinxin on 13-4-22.
//
//

#import <UIKit/UIKit.h>
@interface kvo1 : NSObject {
    NSString   *name;
    NSString   *num;
}
@property (nonatomic, retain)  NSString   *name;
@property (nonatomic, retain)  NSString   *num;
@end

@interface Kvo1ViewController : UIViewController {
    kvo1  *k1;
}
@property (nonatomic, retain) kvo1 *k1;
@end
