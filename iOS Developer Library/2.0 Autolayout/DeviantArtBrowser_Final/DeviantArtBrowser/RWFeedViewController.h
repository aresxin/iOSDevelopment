//
//  RWTableViewController.h
//  DeviantArtBrowser
//
//  Created by Joshua Greene on 4/1/14.
//  Copyright (c) 2014 Razeware, LLC. All rights reserved.
//

#import <UIKit/UIKit.h>

@class RSSParser;

@interface RWFeedViewController : UIViewController <UITextFieldDelegate>
@property (nonatomic, strong) RSSParser *parser;
@property (nonatomic, copy) NSArray *feedItems;
@property (nonatomic, weak) IBOutlet UITextField *searchTextField;
@property (nonatomic, weak) IBOutlet UITableView *tableView;
- (IBAction)refreshData;
@end
