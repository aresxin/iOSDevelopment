//
//  ColoredTextLayer.h
//  DevelopGuide_iOS
//
//  Created by clay on 12-11-30.
//
//

#import <QuartzCore/QuartzCore.h>
#import "ColoredTextLayerDelegate.h"

@interface ColoredTextLayer : CALayer {
    NSMutableArray *_textNSArray;
    NSMutableArray *_colorNSArray;
    UIFont         *_font;
    NSInteger      _lineSpace;
    NSInteger      _wordSpace;
}
@property (nonatomic, retain) NSMutableArray *textNSArray;
@property (nonatomic, retain) NSMutableArray *colorNSArray;
@property (nonatomic, retain) UIFont         *font;
@property (nonatomic, assign) NSInteger      lineSpace;
@property (nonatomic, assign) NSInteger      wordSpace;

/*!
 *  set the <u><font color="red">layer</font></u> colored text
 */
- (void)setTexts:(NSArray *)texts
        inColors:(NSArray *)colors
        withFont:(UIFont *)font
       lineSpace:(NSInteger)lSpace
       wordSpace:(NSInteger)wSpace;

/*!
 *  separate the string to words
 */
- (void)initTextsColorsArray:(NSArray *)texts inColors:(NSArray *)colors;
@end
