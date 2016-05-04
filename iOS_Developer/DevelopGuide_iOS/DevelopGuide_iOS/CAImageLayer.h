//
//  CAImageLayer.h
//  DevelopGuide_iOS
//
//  Created by yangjinxin on 13-5-23.
//
//

#import <QuartzCore/QuartzCore.h>
#import "CAImageLayerDelegate.h"
@interface CAImageLayer : CATiledLayer {
    UIImage     *image;
}
@property (nonatomic,retain) UIImage *image;
- (void) setDrawImage;
@end
