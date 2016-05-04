//
//  ImageLayerViewController.h
//  DevelopGuide_iOS
//
//  Created by yangjinxin on 13-5-23.
//
//

#import <UIKit/UIKit.h>
#import "CAImageLayer.h"
@interface ImageLayerViewController : UIViewController <UIScrollViewDelegate>
{
    UIView  *showV;
    CAImageLayer *imageLayer;
}

@end
