//
//  ColoredTextLayer.m
//  DevelopGuide_iOS
//
//  Created by clay on 12-11-30.
//
//

#import "ColoredTextLayer.h"

@implementation ColoredTextLayer
@synthesize textNSArray = _textNSArray;
@synthesize colorNSArray = _colorNSArray;
@synthesize font = _font;
@synthesize lineSpace = _lineSpace;
@synthesize wordSpace = _wordSpace;

/*!
 *  @override
 */
- (id)init
{
    self = [super init];
    if (self) {
        [self.delegate release];
        self.delegate = nil;
        ColoredTextLayerDelegate * delegate = [[ColoredTextLayerDelegate alloc] init];
        self.delegate = delegate;
        //[delegate release];
        
        _textNSArray = [[NSMutableArray alloc] initWithCapacity:0];
        
        _colorNSArray = [[NSMutableArray alloc] initWithCapacity:0];
    }
    return self;
}

/*!
 *  set the <u><font color="red">layer</font></u> colored text
 *  @param texts texts array
 *  @param colors colors array
 *  @param font font
 *  @param lSpace space size between two lines
 *  @param wSpace space size between two words
 *  @return null
 */
- (void)setTexts:(NSArray *)texts
        inColors:(NSArray *)colors
        withFont:(UIFont *)font
       lineSpace:(NSInteger)lSpace
       wordSpace:(NSInteger)wSpace
{
    [self initTextsColorsArray:texts inColors:colors];
    _font = font;
    _lineSpace = lSpace;
    _wordSpace = wSpace;
    [self setNeedsDisplay];
}

/*!
 *  separate the string to words
 *  @param texts texts array
 *  @param colors colors array
 *  @return null
 */
- (void)initTextsColorsArray:(NSArray *)texts inColors:(NSArray *)colors
{
    for (int i = 0; i < texts.count; i++) {
        NSString * string = [texts objectAtIndex:i];
        UIColor * color = [colors objectAtIndex:i];
        NSArray * array = [string componentsSeparatedByCharactersInSet:[NSCharacterSet whitespaceCharacterSet]];
        array = [array filteredArrayUsingPredicate:[NSPredicate predicateWithFormat:@"SELF != ''"]];
        for (int i = 0; i < array.count; i++) {
            [_textNSArray addObject:[array objectAtIndex:i]];
            [_colorNSArray addObject:color];
        }
    }
}

/*!
 *  @override
 */
- (void)dealloc
{
    [_textNSArray release];
    [_colorNSArray release];
    [_font release];
    [super dealloc];
}

@end
