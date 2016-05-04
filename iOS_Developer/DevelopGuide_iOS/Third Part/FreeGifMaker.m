

#import "FreeGifMaker.h"

@implementation FreeGifMaker

- (id)init
{
    if ((self = [super init])) 
    {
        frame = nil;
        timeDelay = 0.5f;
        homeDirectory = [NSString stringWithFormat:@"%@/Documents",NSHomeDirectory()];
        fileName = @"Default.gif";
        loopCount = 0;
        count = 0;
    }
    return self;
}

- (void)dealloc
{
    [super dealloc];
}

- (void)setFrameDelay:(CGFloat)delayTime
{
    timeDelay = delayTime;
}

- (void)setLoopCount:(NSInteger)loop
{
    loopCount = loop;
}

- (void)setGifFrame:(NSArray *)arrayFrame
{
    frame = [NSMutableArray arrayWithArray:arrayFrame];
}

//- (void)setGifFrame:(NSArray *)arrayFrame delay:(CGFloat)delay
//{
//    frame = [NSMutableArray arrayWithArray:arrayFrame];
//    timeDelay = delay;
//}

- (void)setGifFrame:(NSArray *)arrayFrame delay:(NSArray *)arrayDelay
{
    frame = [NSMutableArray arrayWithArray:arrayFrame];
    delay = [NSMutableArray arrayWithArray:arrayDelay];
}

- (void)setGifFileDirectory:(NSString *)directory
{
    homeDirectory = [NSString stringWithFormat:@"%@",directory];
}

- (void)setGifFileName:(NSString *)name
{
    fileName = [NSString stringWithFormat:@"%@",name];
}

- (void)saveAnimatedGif
{
    NSString *path = [homeDirectory stringByAppendingPathComponent:fileName];
    CGImageDestinationRef destination = CGImageDestinationCreateWithURL((CFURLRef)[NSURL fileURLWithPath:path],
                                                                        kUTTypeGIF,
                                                                        [frame count],
                                                                        NULL);
    

    NSDictionary *gifProperties = [NSDictionary dictionaryWithObject:[NSDictionary dictionaryWithObject:[NSNumber numberWithInt:loopCount] forKey:(NSString *)kCGImagePropertyGIFLoopCount]
                                                              forKey:(NSString *)kCGImagePropertyGIFDictionary];
    for (UIImage *obj in frame)
    {
//        NSDictionary *frameProperties = [NSDictionary dictionaryWithObject:[NSDictionary dictionaryWithObject:[NSNumber numberWithDouble:timeDelay] forKey:(NSString *)kCGImagePropertyGIFDelayTime]
//                                                                    forKey:(NSString *)kCGImagePropertyGIFDictionary];
        
        NSDictionary *frameProperties = [NSDictionary dictionaryWithObject:[NSDictionary dictionaryWithObject:[delay objectAtIndex:count] forKey:(NSString *)kCGImagePropertyGIFDelayTime]
                                                                    forKey:(NSString *)kCGImagePropertyGIFDictionary];
        
        CGImageDestinationAddImage(destination, obj.CGImage, (CFDictionaryRef)frameProperties);
        count++;
        
    }
    CGImageDestinationSetProperties(destination, (CFDictionaryRef)gifProperties);
    CGImageDestinationFinalize(destination);
    CFRelease(destination);
    count = 0;
    NSLog(@"%@",homeDirectory);
}

@end
