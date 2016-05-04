//
//  LocationViewController.h
//  DevelopGuide_iOS
//
//  Created by neusoft  on 11-12-20.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "CoreLocationMgr.h"

@interface LocationViewController : UIViewController <didFinishLocation>{
    UITextView      *infoTextView_;
}
@property   (nonatomic, retain) IBOutlet    UITextView  *infoTextView;
- (IBAction) actionStartLocationButton:(id)sender;
@end
