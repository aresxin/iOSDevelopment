//
//  RWDetailViewController.h
//  DeviantArtBrowser
//
//  Created by Joshua Greene on 5/9/14.
//  Copyright (c) 2014 Razeware, LLC. All rights reserved.
//

#import <UIKit/UIKit.h>

@class RSSItem;

@interface RWDetailViewController : UIViewController
@property (nonatomic, strong) RSSItem *item;
@property (nonatomic, weak) IBOutlet UIImageView *imageView;
@property (nonatomic, weak) IBOutlet UILabel *label;
@end
