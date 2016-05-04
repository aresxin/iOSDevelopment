//
//  CAImageLayer.m
//  DevelopGuide_iOS
//
//  Created by yangjinxin on 13-5-23.
//
//

#import "CAImageLayer.h"

@implementation CAImageLayer
@synthesize image;
- (id)init
{
    self = [super init];
    if (self) {
        [self.delegate release];
        self.delegate = nil;
        NSString *path = [[NSBundle mainBundle] pathForResource:@"PeeringFrog_Placeholder" ofType:@"png"];
        NSData   *data = [NSData dataWithContentsOfFile:path];
        image          = [[UIImage alloc] initWithData:data];
        
        CAImageLayerDelegate * layerDelegate = [[CAImageLayerDelegate alloc] init];
        self.delegate = layerDelegate;
        //[delegate release];
        self.levelsOfDetail = 4;
        self.levelsOfDetailBias = 4;
        
       
    }
    return self;
}

- (void) setDrawImage
{
    
}

@end
