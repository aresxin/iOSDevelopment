//
//  DSPAFocusVideoViewController.h
//  DevelopGuide_iOS
//
//  Created by yangjinxin on 13-8-13.
//
//

#import <UIKit/UIKit.h>

@interface DSPAFocusVideoViewController : UIViewController {
    // data
    NSArray               *videoList_;
    
    // UI
    IBOutlet UIScrollView *scrollV_;
}

- (id) initFocusVideos:(NSArray *)videoList
                 frame:(CGRect)rect;
@end
