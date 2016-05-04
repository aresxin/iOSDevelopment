//
//  TapView.m
//  Test
//
//  Created by liu AISIDE on 12-3-27.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "TapView.h"

@implementation TapView
@synthesize editBeginBlcok;

- (id)initWithFrame:(CGRect)frame EditBeginBlcok:(EditBeginBlcok)editBeginBlcok1
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
        for (int i=0; i<4; i++) {
            UIButton *btn=[UIButton buttonWithType:UIButtonTypeRoundedRect];
            int row=i/2;
            int line=i%2;
            [btn setFrame:CGRectMake(line*100+50, row*100+50, 50  , 50)];
            [btn setTitle:[NSString stringWithFormat:@"按钮:%d",i] forState:UIControlStateNormal];
            btn.tag=i;
            [btn addTarget:self action:@selector(editBtn:) forControlEvents:UIControlEventTouchUpInside];
            [self addSubview:btn];
        }
        self.editBeginBlcok=editBeginBlcok1;
    }
    return self;
}

/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect
{
    // Drawing code
}
*/

-(IBAction)editBtn:(id)sender{
    UIButton *btn=(UIButton*)sender;
    //块变量的调用
    if (self.editBeginBlcok!=nil) {
        self.editBeginBlcok(btn.tag);
    }
}


@end
