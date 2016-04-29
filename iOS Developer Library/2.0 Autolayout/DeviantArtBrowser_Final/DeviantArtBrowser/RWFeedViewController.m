//
//  RWTableViewController.m
//  DeviantArtBrowser
//
//  Created by Joshua Greene on 4/1/14.
//  Copyright (c) 2014 Razeware, LLC. All rights reserved.
//

#import "RWFeedViewController.h"

#import <AFNetworking/UIKit+AFNetworking.h>
#import <MediaRSSParser/MediaRSSParser.h>
#import <MBProgressHUD/MBProgressHUD.h>

#import "RWDetailViewController.h"

#import "RWBasicCell.h"
#import "RWImageCell.h"

static NSString * const RWBasicCellIdentifier = @"RWBasicCell";
static NSString * const RWImageCellIdentifier = @"RWImageCell";

static NSString * const RWDeviantArtBaseURLString = @"http://backend.deviantart.com/rss.xml";

@implementation RWFeedViewController

#pragma mark - View Lifecycle

- (void)viewDidLoad {
  [super viewDidLoad];
  [self setUpParser];
  [self refreshData];
}

- (void)setUpParser {
  self.parser = [[RSSParser alloc] init];
}

- (void)viewWillAppear:(BOOL)animated {
  [super viewWillAppear:animated];
  [self deselectAllRows];
}

- (void)deselectAllRows {
  for (NSIndexPath *indexPath in [self.tableView indexPathsForSelectedRows]) {
    [self.tableView deselectRowAtIndexPath:indexPath animated:NO];
  }
}

#pragma mark - Refresh

- (IBAction)refreshData {
  [self.searchTextField resignFirstResponder];
  [self parseForQuery:self.searchTextField.text];
}

- (void)parseForQuery:(NSString *)query {
  [self showProgressHUD];
  
  __weak typeof(self) weakSelf = self;
  
  [self.parser parseRSSFeed:RWDeviantArtBaseURLString
                 parameters:[self parametersForQuery:query]
                    success:^(RSSChannel *channel) {
                      
                      [weakSelf convertItemsPropertiesToPlainText:channel.items];
                      [weakSelf setFeedItems:channel.items];
                      
                      [weakSelf reloadTableViewContent];
                      [weakSelf hideProgressHUD];
                      
                    } failure:^(NSError *error) {
                      
                      [weakSelf hideProgressHUD];
                      NSLog(@"Error: %@", error);
                    }];
}

- (void)showProgressHUD {
  [MBProgressHUD showHUDAddedTo:self.view animated:YES];
  [[MBProgressHUD HUDForView:self.view] setLabelText:@"Loading"];
}

- (NSDictionary *)parametersForQuery:(NSString *)query {
  if (query.length) {
    return @{@"q": [NSString stringWithFormat:@"by:%@", query]};
    
  } else {
    return @{@"q": @"boost:popular"};
  }
}

- (void)hideProgressHUD {
  [MBProgressHUD hideAllHUDsForView:self.view animated:YES];
}

- (void)convertItemsPropertiesToPlainText:(NSArray *)items {
  for (RSSItem *item in items) {
    NSCharacterSet *charSet = [NSCharacterSet whitespaceAndNewlineCharacterSet];
    item.title = [[item.title stringByConvertingHTMLToPlainText] stringByTrimmingCharactersInSet:charSet];
    item.mediaDescription = [[item.mediaDescription stringByConvertingHTMLToPlainText] stringByTrimmingCharactersInSet:charSet];
    item.mediaText = [[item.mediaText stringByConvertingHTMLToPlainText] stringByTrimmingCharactersInSet:charSet];
  }
}

- (void)reloadTableViewContent {
  dispatch_async(dispatch_get_main_queue(), ^{
    [self.tableView reloadData];
    [self.tableView scrollRectToVisible:CGRectMake(0, 0, 1, 1) animated:NO];
  });
}

#pragma mark - UITableViewDataSource

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
  return [self.feedItems count];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
  if ([self hasImageAtIndexPath:indexPath]) {
    return [self galleryCellAtIndexPath:indexPath];
  } else {
    return [self basicCellAtIndexPath:indexPath];
  }
}

- (BOOL)hasImageAtIndexPath:(NSIndexPath *)indexPath {
  RSSItem *item = self.feedItems[indexPath.row];
  RSSMediaThumbnail *mediaThumbnail = [item.mediaThumbnails firstObject];
  return mediaThumbnail.url != nil;
}

- (RWImageCell *)galleryCellAtIndexPath:(NSIndexPath *)indexPath {
  RWImageCell *cell = [self.tableView dequeueReusableCellWithIdentifier:RWImageCellIdentifier forIndexPath:indexPath];
  [self configureImageCell:cell atIndexPath:indexPath];
  return cell;
}

- (void)configureImageCell:(RWImageCell *)cell atIndexPath:(NSIndexPath *)indexPath {
  RSSItem *item = self.feedItems[indexPath.row];
  [self setTitleForCell:cell item:item];
  [self setSubtitleForCell:cell item:item];
  [self setImageForCell:(id)cell item:item];
}

- (void)setImageForCell:(RWImageCell *)cell item:(RSSItem *)item {
  RSSMediaThumbnail *mediaThumbnail = [item.mediaThumbnails firstObject];
  
  // mediaThumbnails are generally ordered by size,
  // so get the second mediaThumbnail, which is a
  // "medium" sized image
  
  if (item.mediaThumbnails.count >= 2) {
    mediaThumbnail = item.mediaThumbnails[1];
  } else {
    mediaThumbnail = [item.mediaThumbnails firstObject];
  }
  
  [cell.customImageView setImage:nil];
  [cell.customImageView setImageWithURL:mediaThumbnail.url];
}

- (RWBasicCell *)basicCellAtIndexPath:(NSIndexPath *)indexPath {
  RWBasicCell *cell = [self.tableView dequeueReusableCellWithIdentifier:RWBasicCellIdentifier forIndexPath:indexPath];
  [self configureBasicCell:cell atIndexPath:indexPath];
  return cell;
}

- (void)configureBasicCell:(RWBasicCell *)cell atIndexPath:(NSIndexPath *)indexPath {
  RSSItem *item = self.feedItems[indexPath.row];
  [self setTitleForCell:cell item:item];
  [self setSubtitleForCell:cell item:item];
}

- (void)setTitleForCell:(RWBasicCell *)cell item:(RSSItem *)item {
  NSString *title = item.title ?: NSLocalizedString(@"[No Title]", nil);
  [cell.titleLabel setText:title];
}

- (void)setSubtitleForCell:(RWBasicCell *)cell item:(RSSItem *)item {
  NSString *subtitle = item.mediaText ?: item.mediaDescription;
  
  // Some subtitles can be really long, so only display the
  // first 200 characters
  if (subtitle.length > 200) {
    subtitle = [NSString stringWithFormat:@"%@...", [subtitle substringToIndex:200]];
  }
  
  [cell.subtitleLabel setText:subtitle];
}

#pragma mark - UITableViewDelegate

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
  if ([self hasImageAtIndexPath:indexPath]) {
    return [self heightForImageCellAtIndexPath:indexPath];
  } else {
    return [self heightForBasicCellAtIndexPath:indexPath];
  }
}

- (CGFloat)heightForImageCellAtIndexPath:(NSIndexPath *)indexPath {
  static RWImageCell *sizingCell = nil;
  static dispatch_once_t onceToken;
  dispatch_once(&onceToken, ^{
    sizingCell = [self.tableView dequeueReusableCellWithIdentifier:RWImageCellIdentifier];
  });
  
  [self configureImageCell:sizingCell atIndexPath:indexPath];
  return [self calculateHeightForConfiguredSizingCell:sizingCell];
}

- (CGFloat)heightForBasicCellAtIndexPath:(NSIndexPath *)indexPath {
  static RWBasicCell *sizingCell = nil;
  static dispatch_once_t onceToken;
  dispatch_once(&onceToken, ^{
    sizingCell = [self.tableView dequeueReusableCellWithIdentifier:RWBasicCellIdentifier];
  });
  
  [self configureBasicCell:sizingCell atIndexPath:indexPath];
  return [self calculateHeightForConfiguredSizingCell:sizingCell];
}

- (CGFloat)calculateHeightForConfiguredSizingCell:(UITableViewCell *)sizingCell {
  
  sizingCell.bounds = CGRectMake(0.0f, 0.0f, CGRectGetWidth(self.tableView.frame), CGRectGetHeight(sizingCell.bounds));
  
  [sizingCell setNeedsLayout];
  [sizingCell layoutIfNeeded];
  
  CGSize size = [sizingCell.contentView systemLayoutSizeFittingSize:UILayoutFittingCompressedSize];
  return size.height + 1.0f; // Add 1.0f for the cell separator height
}

- (CGFloat)tableView:(UITableView *)tableView estimatedHeightForRowAtIndexPath:(NSIndexPath *)indexPath {
  if ([self isLandscapeOrientation]) {
    if ([self hasImageAtIndexPath:indexPath]) {
      return 140.0f;
    } else {
      return 120.0f;
    }
  } else {
    if ([self hasImageAtIndexPath:indexPath]) {
      return 235.0f;
    } else {
      return 155.0f;
    }
  }
}

- (BOOL)isLandscapeOrientation {
  return UIInterfaceOrientationIsLandscape([UIApplication sharedApplication].statusBarOrientation);
}

#pragma mark - UITextFieldDelegate

- (BOOL)textFieldShouldReturn:(UITextField *)textField {
  [self refreshData];
  return NO;
}

#pragma mark - Navigation

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
  NSIndexPath *indexPath = [self.tableView indexPathForSelectedRow];
  RSSItem *item = self.feedItems[indexPath.row];
  
  RWDetailViewController *viewController = [segue destinationViewController];
  viewController.item = item;
}

@end
