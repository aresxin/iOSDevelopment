//
//  CustomerDetailViewController.m
//  DevelopGuide_iOS
//
//  Created by clay on 13-1-17.
//
//

#import "CustomerDetailViewController.h"

@interface CustomerDetailViewController ()

@end

@implementation CustomerDetailViewController

- (id)initWithStyle:(UITableViewStyle)style
{
    self = [super initWithStyle:style];
    if (self) {
        // Custom initialization
        isOpen = NO;
    }
    return self;
}

- (void) dealloc
{
    [super dealloc];
}

- (void)viewDidLoad
{
    [super viewDidLoad];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark - action button
- (void) actionMoreButton:(UIButton *)btn
{
    isOpen = YES;
    [self.tableView reloadData];
}

- (void) actionHidenButton:(UIButton *)btn
{
    isOpen = NO;
    [self.tableView reloadData];
}

#pragma mark - Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    // Return the number of sections.
    NSInteger sectionCount = 0;
    
    isOpen ? (sectionCount = 2) : (sectionCount = 1);
    return sectionCount;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    // Return the number of rows in the section.
    return 10;
}

- (CGFloat)tableView:(UITableView *)tableView heightForFooterInSection:(NSInteger)section
{
    return 30;
}

- (UIView *)tableView:(UITableView *)tableView viewForFooterInSection:(NSInteger)section
{
    UIButton *button = nil;
    button = [UIButton buttonWithType:UIButtonTypeCustom];
    [button setFrame:CGRectMake(0, 5, 100, 20)];
    [button setBackgroundColor:[UIColor redColor]];
    
    switch (section) {
        case 0:
        {
            if (isOpen)
            {
                return nil;
            }
            
            [button setTitle:@"更多" forState:UIControlStateNormal];
            [button addTarget:self action:@selector(actionMoreButton:)
             forControlEvents:UIControlEventTouchUpInside];
            return button;
        }
            break;
        case 1:
        {
            [button setTitle:@"隐藏" forState:UIControlStateNormal];
            [button addTarget:self action:@selector(actionHidenButton:)
             forControlEvents:UIControlEventTouchUpInside];
            return button;
        }
            
            break;
            
        default:
            break;
    }
    
    return nil;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *CellIdentifier = @"Cell";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    // Configure the cell...
    if (cell == nil) {
        cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier] autorelease];
    }
    
    // Configure the cell.
    cell.textLabel.text = @"text";
    
    return cell;
}


#pragma mark - Table view delegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
}

@end
