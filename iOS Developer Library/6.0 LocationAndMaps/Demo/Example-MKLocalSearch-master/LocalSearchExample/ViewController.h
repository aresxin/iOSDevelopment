//
//  ViewController.h
//  LocalSearchExample
//
//  Created by Jeffrey Sambells on 2013-01-28.
//  Copyright (c) 2013 Jeffrey Sambells. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <MapKit/MapKit.h>
#import <CoreLocation/CoreLocation.h>

@interface ViewController : UIViewController
@property (strong, nonatomic) IBOutlet UISearchBar *ibSearchBar;
@property (strong, nonatomic) IBOutlet MKMapView *ibMapView;
@end
