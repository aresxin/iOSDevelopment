//
//  PhotoCell.h
//  DropShare
//
//  Created by Charles Fulton on 7/11/13.
//  Copyright (c) 2013 RayWenderlich.com. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface PhotoCell : UITableViewCell

@property (nonatomic, strong) IBOutlet UIImageView *thumbnailImage;
@property (nonatomic, strong) IBOutlet UILabel *fileName;

@end
