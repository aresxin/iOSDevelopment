#import "UILabel+ContentSize.h"
 
@implementation UILabel (ContentSize)

- (CGSize)contentSize {
   NSMutableParagraphStyle * paragraphStyle = [[NSMutableParagraphStyle alloc] init];
    paragraphStyle.lineBreakMode = self.lineBreakMode;
    paragraphStyle.alignment = self.textAlignment;
    
    NSDictionary * attributes = @{NSFontAttributeName : self.font,
                                  NSParagraphStyleAttributeName : paragraphStyle};
    
    CGSize contentSize = [self.text boundingRectWithSize:self.frame.size
                                              options:(NSStringDrawingUsesLineFragmentOrigin|NSStringDrawingUsesFontLeading)
                                           attributes:attributes
                                              context:nil].size;
    return contentSize;
}


-(float)resizeToFit{
    float height = [self expectedHeight];
    CGRect newFrame = [self frame];
    newFrame.size.height = height;
    [self setFrame:newFrame];
    return newFrame.origin.y + newFrame.size.height;
}

-(float)expectedHeight{
    [self setNumberOfLines:0];
    [self setLineBreakMode:UILineBreakModeWordWrap];
	
    CGSize maximumLabelSize = CGSizeMake(self.frame.size.width,9999);
    
    CGSize expectedLabelSize = [[self text] sizeWithFont:[self font]
									   constrainedToSize:maximumLabelSize
										   lineBreakMode:[self lineBreakMode]];
    return expectedLabelSize.height;
}

@end