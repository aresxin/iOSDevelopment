//
//  TapView.h
//  Test
//
//  Created by liu AISIDE on 12-3-27.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>


typedef void (^EditBeginBlcok)(int tag);//定义块类型EditBeginBlcok: 开始编辑时的回调

@interface TapView : UIView{

    EditBeginBlcok editBeginBlcok;
}
@property(nonatomic,assign)EditBeginBlcok editBeginBlcok;
- (id)initWithFrame:(CGRect)frame EditBeginBlcok:(EditBeginBlcok)editBeginBlcok1;

@end
