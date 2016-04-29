//
//  RWBasicCell.h
//  DeviantArtBrowser
//
//  Created by Joshua Greene on 11/23/14.
//  Copyright (c) 2014 Razeware, LLC. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "RWLabel.h"

@interface RWBasicCell : UITableViewCell
@property (nonatomic, weak) IBOutlet RWLabel *titleLabel;
@property (nonatomic, weak) IBOutlet RWLabel *subtitleLabel;
@end
