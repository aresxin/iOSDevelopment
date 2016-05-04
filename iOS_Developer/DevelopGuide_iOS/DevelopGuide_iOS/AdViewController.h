//
//  AdViewController.h
//  DevelopGuide_iOS
//
//  Created by xin on 12-4-24.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <iAd/iAd.h>

@interface AdViewController : UIViewController <ADBannerViewDelegate> {
    ADBannerView *adView;
}
@property (nonatomic, retain) ADBannerView *adView;
@end
