//
//  SEImage.h
//  TimerTest
//  Author：seven
//  Created by seven on 08-9-17.
//  Copyright 2008 sz. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <ImageIO/ImageIO.h>

@interface SEImage : NSObject {

}

+ (void) drawImage:(CGContextRef)context Image:(CGImageRef)aImage 
              Rect:(CGRect)rect;

+(void)drawImage:(CGContextRef) context
		   Image:(CGImageRef)aImage
		 AtPoint:(CGPoint)aPoint;

+(void)drawImage:(CGContextRef) context
		   Image:(CGImageRef)aImage
		 AtPoint:(CGPoint)aPoint
		   FlipX:(BOOL)aFlipX;

+(void)drawImage:(CGContextRef) context 
		   Image:(CGImageRef)aImage 
		 AtPoint:(CGPoint)aPoint
			Zoom:(float)aZoom
		   FlipX:(BOOL)aFlipX;

+(void)drawImage:(CGContextRef) context 
		   Image:(CGImageRef)aImage 
		 AtPoint:(CGPoint)aPoint
			Zoom:(float)aZoom;

+(void)drawImage:(CGContextRef) context 
		   Image:(CGImageRef)aImage 
		 AtPoint:(CGPoint)aPoint
   RolateAtPoint:(CGPoint)aRolatePoint
		  Rolate:(float)aRolate;

+(void)drawImage:(CGContextRef) context 
		   Image:(CGImageRef)aImage 
		 AtPoint:(CGPoint)aPoint
   RolateAtPoint:(CGPoint)aRolatePoint
		  Rolate:(float)aRolate
		   FlipX:(BOOL)aFlipX;


+(void)drawImage:(CGContextRef) context 
		   Image:(CGImageRef)aImage 
		 AtPoint:(CGPoint)aPoint
   RolateAtPoint:(CGPoint)aRolatePoint
		  Rolate:(float)aRolate
			Zoom:(float)aZoom;


+(void)drawImage:(CGContextRef) context 
		   Image:(CGImageRef)aImage 
		 AtPoint:(CGPoint)aPoint
   RolateAtPoint:(CGPoint)aRolatePoint
		  Rolate:(float)aRolate
			Zoom:(float)aZoom
		   FlipX:(BOOL)aFlipX;


//Grid

+(void)drawGrid:(CGContextRef) context
	   DrawRect:(CGRect)aRect
	   GridSize:(CGSize)aSize;

/*
 很适合图片处理应用里为图片添加百叶窗效果，或者拼图游戏里使用。处理方法为：
 
 +(NSDictionary*)SeparateImage:(UIImage*)image ByX:(int)x andY:(int)y cacheQuality:(float)quality;
 
 NSDictionary*：返回字典，UIImageView格式，不仅含有 Image 还含有 Rect。
 image: 图片资源，要求为UIImage格式。x: y:分别表示要切成几行和列，最小值为1。
 quality：处理后保存的小图片的质量。（0，1］有效，小于或为0不保存，大于1时会被强强制为1。
 切割后的小图片保存位置为 Homedirectory， 可以通过 nslog(@"%@",NSHomedirectory()); 查出。
 */ 
//
+(NSDictionary*)SeparateImage:(UIImage*)image ByX:(int)x andY:(int)y cacheQuality:(float)quality;


/***********************************************/
//当获取或者存储图片时需要改变图片的属性时，比如，压缩，方向，dpi等，采用 Image I/O可以提高效率
/***********************************************/
/*压缩图片的方法，会在制定目录生成一张压缩图片：
 compression压缩质量，0-1
 orientation图片的方向
 */
+ (NSData *) getCompressionImageToFileName:(NSString *)fileName
                               compression:(float)com
                               orientation:(UIImageOrientation)ori
                              writeCGImage:(CGImageRef)image;

/*
 获得CGContextRef，设定压缩质量，dpi等存储到指定路径
 */
+ (void) saveImage:(CGContextRef) bitmap
              path:(NSString *)strpath
              type:(int)formattype
               dpi:(int)ndpi;
@end
