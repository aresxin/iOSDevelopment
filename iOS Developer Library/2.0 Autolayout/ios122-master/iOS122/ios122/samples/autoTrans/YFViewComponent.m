//
//  YFViewComponent.m
//  iOS122
//
//  Created by 颜风 on 15/10/6.
//  Copyright (c) 2015年 iOS122. All rights reserved.
//

#import "YFViewComponent.h"

/**
 *  预定义常量的定义.
 */
const NSString *  YFViewComponentSelfHolderWidthKey = @"YFViewComponentSelfHolderWidthKey";
const NSString *  YFViewComponentSelfHolderHeightKey = @"YFViewComponentSelfHolderHeightKey";
const NSString *  YFViewComponentSubViewsKey = @"YFViewComponentSubViewsKey";
const NSString *  YFViewComponentSubViewClassNameKey = @"YFViewComponentSubViewClassNameKey";
const NSString *  YFViewComponentSubViewPropNameKey = @"YFViewComponentSubViewPropNameKey";
const NSString *  YFViewComponentSubViewHolderWidthKey = @"YFViewComponentSubViewHolderWidthKey";
const NSString *  YFViewComponentSubViewHolderHeightKey = @"YFViewComponentSubViewHolderHeightKey";
const NSString *  YFViewComponentSubViewHolderRightKey = @"YFViewComponentSubViewHolderRightKey";
const NSString *  YFViewComponentSubViewHolderBottomKey = @"YFViewComponentSubViewHolderBottomKey";

@implementation YFViewComponent

- (instancetype)init
{
    self = [super init];
    
    if (nil != self) {
        UIView * holderView = self;
        
        NSDictionary * config = [[self class] subViewsConfig];
        
        CGFloat superHeight = [[config objectForKey: YFViewComponentSelfHolderHeightKey] floatValue];
        CGFloat superWidth = [[config objectForKey: YFViewComponentSelfHolderWidthKey] floatValue];;
        
        NSArray * locatArray = [config objectForKey: YFViewComponentSubViewsKey];
        
        [locatArray enumerateObjectsUsingBlock:^(NSDictionary * obj, NSUInteger idx, BOOL *stop) {
            NSString * classString = [obj objectForKey: YFViewComponentSubViewClassNameKey];
            
            Class viewClass = NSClassFromString(classString);
            
            if (YES != [viewClass  isSubclassOfClass:[UIView class]]) {
                return;
            }
            
            UIView * subView = [[viewClass alloc] init];
            [holderView addSubview: subView];
            
            NSString * viewKey = [obj objectForKey: YFViewComponentSubViewPropNameKey];
            
            [holderView setValue: subView forKey: viewKey];
            
            CGFloat subWidth = [[obj objectForKey: YFViewComponentSubViewHolderWidthKey] floatValue];
            CGFloat subHeight = [[obj objectForKey: YFViewComponentSubViewHolderHeightKey] floatValue];
            CGFloat subBottom = [[obj objectForKey: YFViewComponentSubViewHolderBottomKey] floatValue];
            CGFloat subRight = [[obj objectForKey: YFViewComponentSubViewHolderRightKey] floatValue];
            
            [subView makeConstraints:^(MASConstraintMaker *make) {
                UIView * superView = subView.superview;
                
                make.width.equalTo(superView).multipliedBy(subWidth / superWidth);
                make.height.equalTo(superView).multipliedBy(subHeight / superHeight);
                
                make.right.equalTo(superView).multipliedBy(subRight / superWidth);
                make.bottom.equalTo(superView).multipliedBy(subBottom / superHeight);
            }];
            
            /* 支持UILabel及其子类字体大小自适应. */
            if ([subView isKindOfClass:[UILabel class]]) {
                UILabel * tempLabel = (UILabel *)subView;
                tempLabel.font = [UIFont systemFontOfSize: 100.0];
                tempLabel.minimumScaleFactor = 0.001;
                tempLabel.adjustsFontSizeToFitWidth = YES;
                tempLabel.numberOfLines = 0;
            }
        }];
    }
    
    return self;
}


+ (NSDictionary *) subViewsConfig{
    return nil;
}

@end
