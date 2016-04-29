//
//  YFViewComponent.h
//  iOS122
//
//  Created by 颜风 on 15/10/6.
//  Copyright (c) 2015年 iOS122. All rights reserved.
//

#import <UIKit/UIKit.h>

/**
 *  预定义常量的声明.
 */
extern const NSString *  YFViewComponentSelfHolderWidthKey; //!< 同一设计图中,视图模块本身的宽度.
extern const NSString *  YFViewComponentSelfHolderHeightKey; //!< 同一设计图中,视图模块本身的高度.
extern const NSString *  YFViewComponentSubViewsKey; //!< 同一设计图中,模块的所有子视图.
extern const NSString *  YFViewComponentSubViewClassNameKey; //!< 子视图的类型.
extern const NSString *  YFViewComponentSubViewPropNameKey; //!< 子视图对应的属性,模块中应有属性与其对应,且可通过此属性访问对应的子视图.
extern const NSString *  YFViewComponentSubViewHolderWidthKey; //!< 同一设计图中,子视图的宽度.
extern const NSString *  YFViewComponentSubViewHolderHeightKey; //!< 同一设计图中,子视图的高度.
extern const NSString *  YFViewComponentSubViewHolderRightKey; //!< 同一设计图中,子视图的右内边距值(right).
extern const NSString *  YFViewComponentSubViewHolderBottomKey; //!< 同一设计图中,子视图的底部边距值(bottom).


@interface YFViewComponent : UIView

/**
 *  子视图配置信息.
 *
 *  子类应重写覆盖此方法.
 *
 一个示例:
 @{
 YFViewComponentSelfHolderWidthKey: @640.0,
 YFViewComponentSelfHolderHeightKey: @155.0,
 YFViewComponentSubViewsKey:
 @[@{
 YFViewComponentSubViewClassNameKey: NSStringFromClass([UIImageView class]) ,
 YFViewComponentSubViewPropNameKey: @"imageView", YFViewComponentSubViewHolderWidthKey: @160, YFViewComponentSubViewHolderHeightKey: @120, YFViewComponentSubViewHolderBottomKey: @140, YFViewComponentSubViewHolderRightKey: @180
 }]}
 *
 *  @return 返回子视图的配置信息.
 */
+ (NSDictionary *) subViewsConfig;

@end
