//
//  MainViewController.m
//  BackgroundLocationTrackingExample
//
//  Created by Denis Lebedev on 12.08.12.
//  Copyright (c) 2012 Denis Lebedev. All rights reserved.
//

#import "MainViewController.h"

#import "DLLocationTracker.h"

@interface MainViewController ()

@property (nonatomic, strong) NSMutableArray *locations;
@property (nonatomic, strong) DLLocationTracker *locationTracker;

@end

@implementation MainViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.locationTracker = [[DLLocationTracker alloc] init];
    [self.locationTracker setLocationUpdatedInForeground:^ (CLLocation *location) {
        if (location) {
            [self.locations addObject:location];
            NSIndexPath *indexPath = [NSIndexPath indexPathForRow:0 inSection:0];
            [self.tableView insertRowsAtIndexPaths:[NSArray arrayWithObject:indexPath] withRowAnimation:UITableViewRowAnimationAutomatic];
        }
    }];
    [self.locationTracker setLocationUpdatedInBackground:^ (CLLocation *location) {
        UILocalNotification *notification = [[UILocalNotification alloc] init];
        notification.fireDate  = [NSDate dateWithTimeIntervalSinceNow:5];
        notification.alertBody = [NSString stringWithFormat:@"Main view New location: %@", location];
        notification.soundName = UILocalNotificationDefaultSoundName;
        [notification setTimeZone:[NSTimeZone defaultTimeZone]];
        [[UIApplication sharedApplication] scheduleLocalNotification:notification];
    }];
    [self.locationTracker startUpdatingLocation];

}

- (void)viewDidUnload {
    [super viewDidUnload];
    self.locationTracker = nil;
}


#pragma mark - Table view data source

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return [self.locations count];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *CellIdentifier = @"Cell";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    if (!cell) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:CellIdentifier];
    }
    
    CLLocation *location = [self.locations objectAtIndex:indexPath.row];
    cell.textLabel.text = [NSString stringWithFormat:@"%@", location.timestamp];
    cell.detailTextLabel.text = [NSString stringWithFormat:@"lat - %.3f lon - %.3f", location.coordinate.latitude, location.coordinate.longitude];
    return cell;
}

/*
// Override to support conditional editing of the table view.
- (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath
{
    // Return NO if you do not want the specified item to be editable.
    return YES;
}
*/

/*
// Override to support editing the table view.
- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath
{
    if (editingStyle == UITableViewCellEditingStyleDelete) {
        // Delete the row from the data source
        [tableView deleteRowsAtIndexPaths:@[indexPath] withRowAnimation:UITableViewRowAnimationFade];
    }   
    else if (editingStyle == UITableViewCellEditingStyleInsert) {
        // Create a new instance of the appropriate class, insert it into the array, and add a new row to the table view
    }   
}
*/

#pragma mark - Private

- (NSMutableArray *)locations {
    if (!_locations) {
        self.locations = [NSMutableArray array];
    }
    return _locations;
}

@end
