//
//  DrawText.m
//  DrawLine
//
//  Created by neusoft  on 11-7-11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "DrawText.h"


@implementation DrawText


- (id)initWithFrame:(CGRect)frame {
    
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code.
    }
    return self;
}

//#define kTextString "Hello From Quartz"
//#define kTextStringLength strlen(kTextString)
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect {
	NSString *h = @"13dasdsadasds";
	//char *string[15] = 
	char *draw = (char *)[h cStringUsingEncoding:NSUTF8StringEncoding];
	//char *draw = [h cString];
	NSLog(@"%s",draw);
	CGContextRef context = UIGraphicsGetCurrentContext();
    // Drawing code.
	CGContextSetRGBFillColor(context, 1.0, 1.0, 1.0, 1.0);
	CGContextSetRGBStrokeColor(context, 1.0, 0.0, 0.0, 1.0);
	
	// Some initial setup for our text drawing needs.
	// First, we will be doing our drawing in Helvetica-36pt with the MacRoman encoding.
	// This is an 8-bit encoding that can reference standard ASCII characters
	// and many common characters used in the Americas and Western Europe.
	CGContextSelectFont(context, "Helvetica", 36.0, kCGEncodingMacRoman);
	// Next we set the text matrix to flip our text upside down. We do this because the context itself
	// is flipped upside down relative to the expected orientation for drawing text (much like the case for drawing Images & PDF).
	CGContextSetTextMatrix(context, CGAffineTransformMakeScale(1.0, -1.0));
	// And now we actually draw some text. This screen will demonstrate the typical drawing modes used.
	//设定描绘的方式和位置
	CGContextSetTextDrawingMode(context, kCGTextFill);
	CGContextShowTextAtPoint(context, 10.0, 30.0, draw,strlen(draw));
	
	CGContextSetTextDrawingMode(context, kCGTextStroke);
	CGContextShowTextAtPoint(context, 10.0, 70.0, "Hello From Quartz", strlen("Hello From Quartz"));
	
	CGContextSetTextDrawingMode(context, kCGTextFillStroke);
	CGContextShowTextAtPoint(context, 10.0, 110.0, "Hello From Quartz", strlen("Hello From Quartz"));
	
	// Now lets try the more complex Glyph functions. These functions allow you to draw any glyph available in a font,
	// but provide no assistance with converting characters to glyphs or layout, and as such require considerably more knowledge
	// of text to use correctly. Specifically, you need to understand Unicode encoding and how to interpret the information
	// present in the font itself, such as the cmap table.
	// To get you started, we are going to do the minimum necessary to draw a glyphs into the current context.
	//创建字体
	CGFontRef helvetica = CGFontCreateWithFontName((CFStringRef)@"Helvetica");
	CGContextSetFont(context, helvetica);
	CGContextSetFontSize(context, 12.0);
	CGContextSetTextDrawingMode(context, kCGTextFill);
	// Next we'll display lots of glyphs from the font. 
	CGGlyph start = 0;
	for(int y = 0; y < 20; ++y)
	{
		CGGlyph glyphs[32];
		for(int i = 0; i < 32; ++i)
		{
			glyphs[i] = start + i;
		}
		start += 32;
		CGContextShowGlyphsAtPoint(context, 10.0, 150.0 + 12 * y, glyphs, 32);
	}
	CGFontRelease(helvetica);
	
}


- (void)dealloc {
    [super dealloc];
}


@end
