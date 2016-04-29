//
//  YFAutoLayoutCell.m
//  iOS122
//
//  Created by 颜风 on 15/9/22.
//  Copyright (c) 2015年 iOS122. All rights reserved.
//

#import <SDWebImage/UIImageView+WebCache.h>

#import "YFAutoLayoutCell.h"
#import "YFAutoLayoutCellModel.h"

@interface YFAutoLayoutCell ()
@property (strong, nonatomic) UIImageView * imgView;
@property (strong, nonatomic) UILabel * introLabel;

@end

@implementation YFAutoLayoutCell

- (instancetype)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier
{
    self = [super initWithStyle:style reuseIdentifier:reuseIdentifier];
    
    if (nil != self) {
        [self setupView];
    }
    
    return self;
}

/**
 *  初始化视图.
 */
- (void) setupView
{
    self.imgView = [[UIImageView alloc] init];
    self.introLabel = [[UILabel alloc] init];
    
    [self.contentView addSubview: self.imgView];
    [self.contentView addSubview: self.introLabel];
    
    self.introLabel.numberOfLines = 0;
    
    [self.imgView makeConstraints:^(MASConstraintMaker *make) {
        make.top.left.equalTo(8);
        make.size.equalTo(CGSizeMake(60, 60));
        make.bottom.lessThanOrEqualTo(-8).priorityHigh();
    }];
    
    [self.introLabel makeConstraints:^(MASConstraintMaker *make) {
        make.left.equalTo(self.imgView.right).offset(8);
        make.top.equalTo(self.imgView);
        make.right.equalTo(-8);
        make.bottom.equalTo(-8);
    }];
}

- (void)setModel:(YFAutoLayoutCellModel *)model
{
    _model = model;
    
    [self.imgView sd_setImageWithURL: [NSURL URLWithString: model.img]];
    self.introLabel.text = self.model.intro;
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated {
    [super setSelected:selected animated:animated];

    // Configure the view for the selected state
}

@end
