//
//  CoreSpotlightTableViewController.m
//  CorespotlightDemo
//
//  Created by Cocoon Jin on 15/7/25.
//  Copyright © 2015年 kdanmobile. All rights reserved.
//

#import "CoreSpotlightTableViewController.h"
#import "WebViewController.h"
#import <CoreSpotlight/CoreSpotlight.h>
#import "SFWebViewController.h"


@interface NSArray (Map)

- (NSArray *)mapObjectsUsingBlock:(id (^)(id obj, NSUInteger idx))block;

@end

@implementation NSArray (Map)

- (NSArray *)mapObjectsUsingBlock:(id (^)(id obj, NSUInteger idx))block {
    NSMutableArray *result = [NSMutableArray arrayWithCapacity:[self count]];
    [self enumerateObjectsUsingBlock:^(id obj, NSUInteger idx, BOOL *stop) {
        [result addObject:block(obj, idx)];
    }];
    return result;
}



@end

@interface CoreSpotlightTableViewController ()
@property (nonatomic, strong)NSMutableArray *tableData;
@property (nonatomic, strong)NSMutableArray *segueIdentifiers;
@end

@implementation CoreSpotlightTableViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    // Uncomment the following line to preserve selection between presentations.
    // self.clearsSelectionOnViewWillAppear = NO;
    
    // Uncomment the following line to display an Edit button in the navigation bar for this view controller.
    // self.navigationItem.rightBarButtonItem = self.editButtonItem;
    [self loadData];
    
    UIBarButtonItem *rightItem = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemRefresh target:self action:@selector(refreshData:)];
    self.navigationItem.rightBarButtonItem = rightItem;
}

- (void)loadData{
    self.tableData = [[[NSUserDefaults standardUserDefaults] objectForKey:@"tableData"] mutableCopy];
    if (!self.tableData){
        [self resetData];
    }
    else{
        self.segueIdentifiers = [[self.tableData mapObjectsUsingBlock:^id(NSString *obj, NSUInteger idx) {
            return [NSString stringWithFormat:@"%@SegueIdentifier",obj];
        }] mutableCopy];
    }
}

- (void)saveData{
    [[NSUserDefaults standardUserDefaults] setObject:self.tableData forKey:@"tableData"];
    [[NSUserDefaults standardUserDefaults] synchronize];
    NSMutableArray *seachableItems = [NSMutableArray new];
    [self.tableData enumerateObjectsUsingBlock:^(NSString *__nonnull obj, NSUInteger idx, BOOL * __nonnull stop) {
        CSSearchableItemAttributeSet *attributeSet = [[CSSearchableItemAttributeSet alloc] initWithItemContentType:@"views"];
        attributeSet.title = obj;
        attributeSet.contentDescription = [NSString stringWithFormat:NSLocalizedString(@"a easy way to open %@", nil),obj];
        UIImage *thumbImage = [UIImage imageNamed:[NSString stringWithFormat:@"icon_%@.png",obj]];
        attributeSet.thumbnailData = UIImagePNGRepresentation(thumbImage);//beta 1 there is a bug
        
        CSSearchableItem *item = [[CSSearchableItem alloc] initWithUniqueIdentifier:obj domainIdentifier:@"com.kdanmobile.CoreSpotlightDemo" attributeSet:attributeSet];
        [seachableItems addObject:item];
    }];
    
    [[CSSearchableIndex defaultSearchableIndex] indexSearchableItems:seachableItems
                                                   completionHandler:^(NSError * __nullable error) {
                                                       if (!error)
                                                           NSLog(@"%@",error.localizedDescription);
                                                   }];
}

- (void)saveDataForSearch {
    [[CSSearchableIndex defaultSearchableIndex] deleteAllSearchableItemsWithCompletionHandler:^(NSError * _Nullable error) {
        
    }];
    
    
    [[CSSearchableIndex defaultSearchableIndex] deleteSearchableItemsWithDomainIdentifiers:@[@"txt"] completionHandler:^(NSError * _Nullable error) {
        
    }];
}


- (void)resetData{
    [[CSSearchableIndex defaultSearchableIndex] deleteAllSearchableItemsWithCompletionHandler:^(NSError * __nullable error) {
        if (!error)
            NSLog(@"%@",error.localizedDescription);
    }];
    self.tableData = [@[@"Image",@"屌丝",@"Web"] mutableCopy];
    self.segueIdentifiers = [[self.tableData mapObjectsUsingBlock:^id(NSString *obj, NSUInteger idx) {
        return [NSString stringWithFormat:@"%@SegueIdentifier",obj];
    }] mutableCopy];
    [self saveData];
}

- (void)deleteDataAtIndex:(NSInteger)index{
    NSString *identifier = [self.tableData[index] copy];
    [[CSSearchableIndex defaultSearchableIndex] deleteSearchableItemsWithIdentifiers:@[identifier] completionHandler:^(NSError * __nullable error) {
        if (!error)
            NSLog(@"%@",error.localizedDescription);
    }];
    [self.tableData removeObjectAtIndex:index];
    [self.segueIdentifiers removeObjectAtIndex:index];
}

#pragma mark - Actions
-(void)refreshData:(id)sender{
    [self resetData];
    [self.tableView reloadData];
}

#pragma mark - Table view data source
- (CGFloat)tableView:(nonnull UITableView *)tableView heightForRowAtIndexPath:(nonnull NSIndexPath *)indexPath{
    return 60.0;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return self.tableData.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"CoreSpotlightIdentifier" forIndexPath:indexPath];
    
    // Configure the cell...
    cell.textLabel.text = self.tableData[indexPath.row];
    cell.imageView.image = [UIImage imageNamed:[NSString stringWithFormat:@"icon_%@.png",self.tableData[indexPath.row]]];
    return cell;
}

- (void)tableView:(nonnull UITableView *)tableView didSelectRowAtIndexPath:(nonnull NSIndexPath *)indexPath{
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
    
    NSURL *url = [NSURL URLWithString:@"https://cloud.kdanmobile.com/members/sign_in"];
    SFSafariViewController *safariVC = [[SFSafariViewController alloc] initWithURL:url];
    [self presentViewController:safariVC
                       animated:YES completion:^{
                           
                       }];
    
    //[self performSegueWithIdentifier:self.segueIdentifiers[indexPath.row] sender:indexPath];
}

// Override to support conditional editing of the table view.
- (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath {
    // Return NO if you do not want the specified item to be editable.
    return YES;
}

// Override to support editing the table view.
- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath {
    if (editingStyle == UITableViewCellEditingStyleDelete) {
        // Delete the row from the data source
        [self deleteDataAtIndex:indexPath.row];
        [self saveData];
        [tableView deleteRowsAtIndexPaths:@[indexPath] withRowAnimation:UITableViewRowAnimationFade];
    } else if (editingStyle == UITableViewCellEditingStyleInsert) {
        // Create a new instance of the appropriate class, insert it into the array, and add a new row to the table view
    }   
}

/*
// Override to support rearranging the table view.
- (void)tableView:(UITableView *)tableView moveRowAtIndexPath:(NSIndexPath *)fromIndexPath toIndexPath:(NSIndexPath *)toIndexPath {
}
*/

/*
// Override to support conditional rearranging of the table view.
- (BOOL)tableView:(UITableView *)tableView canMoveRowAtIndexPath:(NSIndexPath *)indexPath {
    // Return NO if you do not want the item to be re-orderable.
    return YES;
}
*/

- (void)showViewControllerWithIdentifier:(NSString *)identifier{
    NSString *segueIdentifier = [NSString stringWithFormat:@"%@SegueIdentifier",identifier];
    [self performSegueWithIdentifier:segueIdentifier sender:nil];
}

@end

