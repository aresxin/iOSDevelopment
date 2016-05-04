//
//  UIImageCategory.h
//  CategorySample
//
//  Created by yile on 3/29/09.
//  Copyright 2009 Quoord. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface UIImage (Category)
/*
 * Resizes an image.
 */
- (UIImage*)transformWidth:(CGFloat)width 
					height:(CGFloat)height;
/*
 * 用颜色将图片遮罩
 */
+(UIImage *)colorizeImage:(UIImage *)baseImage withColor:(UIColor *)theColor;

/*
 * 用图片将图片遮罩
 */
+(UIImage *)maskImage:(UIImage *)baseImage withImage:(UIImage *)theMaskImage;

/*
 * 根据颜色和size生产image
 */
+(UIImage *)imageWithColor:(UIColor *)color andSize:(CGSize)size;

/*
 * 根据rect矩形截图图片
 */
- (UIImage *)imageAtRect:(CGRect)rect;

/*
 * 缩放image到targetSize
 */
- (UIImage *)imageByScalingProportionallyToMinimumSize:(CGSize)targetSize;

/*
 * 缩放image到targetSize
 */
- (UIImage *)imageByScalingProportionallyToSize:(CGSize)targetSize;

/*
 * 缩放image到targetSize
 */
- (UIImage *)imageByScalingToSize:(CGSize)targetSize;

/*
 * 图片旋转的角度
 */
- (UIImage *)imageRotatedByRadians:(CGFloat)radians;

/*
 * 图片旋转的角度
 */
- (UIImage *)imageRotatedByDegrees:(CGFloat)degrees;

/*
 * 给图片画倒影
 */
- (UIImage *)addImageReflection:(CGFloat)reflectionFraction;

/*
 * 压缩图片
 */
- (UIImage *)compressedImage;
/*
 * 
 */
- (CGFloat)compressionQuality;
/*
 *
 */
- (NSData *)compressedData;
/*
 *
 */
- (NSData *)compressedData:(CGFloat)compressionQuality;
@end
