//
//  Note.m
//  UIImageFun

#import "Note.h"
@implementation Note
- (id)initWithText:(NSString *)text fontSize:(float)fontSize noteChrome:(UIImage *)img edgeInsets:(UIEdgeInsets)insets  maximumWidth:(CGFloat)width topLeftCorner:(CGPoint)corner
{
    if (self = [super init])
    {
#define LARGE_NUMBER 10000 // just a large (but arbitrary) number because we don't want to impose any vertical constraint on our note size
        _text = [NSString stringWithString:text];
        CGSize computedSize = [text sizeWithFont:[UIFont systemFontOfSize:fontSize] constrainedToSize:CGSizeMake(width, LARGE_NUMBER) lineBreakMode:NSLineBreakByWordWrapping];
        UILabel *textLabel = [[UILabel alloc] init];
        textLabel.font = [UIFont systemFontOfSize:fontSize];
        textLabel.text = self.text;
        textLabel.numberOfLines = 0; // unlimited number of lines
        textLabel.lineBreakMode = NSLineBreakByWordWrapping;
        textLabel.frame = CGRectMake(insets.left, insets.top, computedSize.width , computedSize.height);
        _noteView = [[UIImageView alloc] initWithFrame:CGRectMake(corner.x, corner.y, textLabel.bounds.size.width+insets.left+insets.right, textLabel.bounds.size.height+insets.top+insets.bottom)];
        _noteView.image = [img resizableImageWithCapInsets:insets];
        [_noteView addSubview:textLabel];
    }
    return self;
}
@end