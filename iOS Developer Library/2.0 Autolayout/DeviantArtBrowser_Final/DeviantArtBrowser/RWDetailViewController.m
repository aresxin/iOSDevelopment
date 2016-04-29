//
//  RWDetailViewController.m
//  DeviantArtBrowser
//
//  Created by Joshua Greene on 5/9/14.
//  Copyright (c) 2014 Razeware, LLC. All rights reserved.
//

#import "RWDetailViewController.h"
#import <MediaRSSParser/MediaRSSModels.h>

#import <AFNetworking/UIKit+AFNetworking.h>

@implementation RWDetailViewController

#pragma mark - View Lifecycle

- (void)viewDidLoad {
  [super viewDidLoad];
  [self setImageViewImage];
  [self setTextViewText];
}

- (void)setImageViewImage {
  RSSMediaContent *mediaContent = [self.item.mediaContents firstObject];
  [self.imageView setImageWithURL:mediaContent.url];
}

- (void)setTextViewText {
  NSMutableAttributedString *text = [[NSMutableAttributedString alloc] init];
  [self addTitleTo:text];
  [self addDescriptionTextTo:text];
  self.label.attributedText = text;
}

- (void)addTitleTo:(NSMutableAttributedString *)mutableString {
  NSString *title = self.item.title.length ? self.item.title : NSLocalizedString(@"[No Title]", nil);
  
  NSDictionary *attributes = @{NSFontAttributeName: [UIFont boldSystemFontOfSize:18.0f]};
  NSAttributedString *attTitle = [[NSAttributedString alloc] initWithString:title attributes:attributes];
  
  [mutableString appendAttributedString:attTitle];
}

- (void)addDescriptionTextTo:(NSMutableAttributedString *)mutableString {
  NSString *text = self.item.mediaText ?: self.item.mediaDescription;
  
  if (!text.length > 0) {
    return;
    
  } else {
    text = [NSString stringWithFormat:@"\n%@", text];
    
  }
  
  NSDictionary *attributes = @{NSFontAttributeName: [UIFont systemFontOfSize:15.0f]};
  NSAttributedString *attText = [[NSAttributedString alloc] initWithString:text attributes:attributes];
  
  [mutableString appendAttributedString:attText];
}

@end
