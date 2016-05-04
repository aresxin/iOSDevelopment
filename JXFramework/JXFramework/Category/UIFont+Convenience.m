//
//  UIFont+Convenience.m
//  SnapMovie
//
//  Created by CN40436 on 15/2/11.
//  Copyright (c) 2015年 LINE Corporation. All rights reserved.
//

#import "UIFont+Convenience.h"

//"HelveticaNeue-Italic",
//"HelveticaNeue-Bold",
//"HelveticaNeue-UltraLight",
//"HelveticaNeue-CondensedBlack",
//"HelveticaNeue-BoldItalic",
//"HelveticaNeue-CondensedBold",
//"HelveticaNeue-Medium",
//"HelveticaNeue-Light",
//"HelveticaNeue-Thin",
//"HelveticaNeue-ThinItalic",
//"HelveticaNeue-LightItalic",
//"HelveticaNeue-UltraLightItalic",
//"HelveticaNeue-MediumItalic",

@implementation UIFont (Convenience)

+ (UIFont *)helveticaFontOfSize:(CGFloat)fontSize;
{
    return [UIFont fontWithName:@"HelveticaNeue-Medium" size:fontSize];
}

+ (UIFont *)lightHelveticaFontOfSize:(CGFloat)fontSize;
{
    return [UIFont fontWithName:@"HelveticaNeue-Light" size:fontSize];
}

+ (UIFont *)fontWithName:(NSString *)fontName maxFontSize:(CGFloat)maxFontSize text:(NSString *)text rect:(CGRect)rect actualRect:(CGRect *)actualRect scale:(CGFloat)scale;
{
    if (!text || text.length == 0) {
        return [UIFont fontWithName:fontName size:maxFontSize*scale];
    }
    
    CGSize scaledSize = CGSizeMake(rect.size.width*scale, rect.size.height*scale);
    NSInteger fontSize = maxFontSize*scale;
    UIFont *font = [UIFont fontWithName:fontName size:fontSize];
    NSMutableDictionary *attributes = [NSMutableDictionary dictionaryWithObject:font forKey:NSFontAttributeName];
    BOOL succeed = NO;
    CGFloat x = 0.0, y = 0.0 , width = 0.0, height = 0.0;
    while (fontSize > 15) {
        CGSize size = [text sizeWithAttributes:attributes];
        if (size.width <= scaledSize.width && size.height <= scaledSize.height) {
            succeed = YES;
            width = size.width;
            height = size.height;
            break;
        }
        
        fontSize--;
        font = [UIFont fontWithName:fontName size:fontSize];
        attributes[NSFontAttributeName] = font;
    }
    
    if (succeed) {
        x = rect.origin.x*scale;
        y = rect.origin.y*scale;
        *actualRect = CGRectMake(x, y, width, height);
        return font;
    }
    return nil;
}
+ (UIFont *)fontWithName:(NSString *)fontName maxFontSize:(CGFloat)maxFontSize text:(NSString *)text drawSize:(CGSize)drawSize actualSize:(CGSize *)actualSize;
{
    if (!text || text.length == 0) {
        return [UIFont fontWithName:fontName size:maxFontSize];
    }
    
    NSInteger fontSize = maxFontSize;
    UIFont *font = [UIFont fontWithName:fontName size:fontSize];
    NSMutableParagraphStyle *paragraphStyle = [[NSParagraphStyle defaultParagraphStyle] mutableCopy];
    paragraphStyle.alignment = NSTextAlignmentCenter;
    NSMutableDictionary *attributes = [NSMutableDictionary dictionaryWithObjectsAndKeys:font,NSFontAttributeName,
                                       paragraphStyle,NSParagraphStyleAttributeName,
                                       [UIColor whiteColor],NSForegroundColorAttributeName,
                                       [UIColor whiteColor],NSStrokeColorAttributeName,nil];
    BOOL succeed = NO;
    while (fontSize > 12) {
        CGSize size = [text sizeWithAttributes:attributes];
        if (size.width < drawSize.width && size.height <= drawSize.height) {
            succeed = YES;
            *actualSize = size;
            break;
        }
        
        fontSize--;
        font = [UIFont fontWithName:fontName size:fontSize];
        attributes[NSFontAttributeName] = font;
    }
    
    if (succeed) {
        return font;
    }
    return nil;
}
@end


