//
//  RWLabel.m
//  DeviantArtBrowser
//
//  Created by Joshua Greene on 11/23/14.
//  Copyright (c) 2014 Razeware, LLC. All rights reserved.
//

#import "RWLabel.h"

@implementation RWLabel

- (void)setBounds:(CGRect)bounds {
  [super setBounds:bounds];
  
  // If this is a multiline label, need to make sure
  // preferredMaxLayoutWidth always matches the frame width
  // (i.e. orientation change can mess this up)
  
  if (self.numberOfLines == 0 && bounds.size.width != self.preferredMaxLayoutWidth) {
    self.preferredMaxLayoutWidth = self.bounds.size.width;
    [self setNeedsUpdateConstraints];
  }
}

@end
