

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <ImageIO/ImageIO.h>
#import <MobileCoreServices/MobileCoreServices.h>

@interface FreeGifMaker : NSObject
{
    NSMutableArray *frame;
    NSMutableArray *delay;
    CGFloat timeDelay;
    NSString *homeDirectory;
    NSString *fileName;
    NSInteger loopCount;
    int count;
}

// 设置幀之间间隔时间
- (void)setFrameDelay:(CGFloat)delay;

// 设置循环次数（0为无限循环）
- (void)setLoopCount:(NSInteger)loop;

// 设置gif幀序列，数组值为UIImage
- (void)setGifFrame:(NSArray*)arrayFrame;
//- (void)setGifFrame:(NSArray*)arrayFrame delay:(CGFloat)delay;
- (void)setGifFrame:(NSArray *)arrayFrame delay:(NSArray *)delayArray;

// 设置保存位置文件夹
- (void)setGifFileDirectory:(NSString*)directory;

// 设置gif文件名称
- (void)setGifFileName:(NSString*)name;

// 保存gif文件
- (void)saveAnimatedGif;

@end
