//
//  MapViewController.h
//  DevelopGuide_iOS
//
//  Created by xin on 12-5-8.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <MapKit/MapKit.h>
@interface MapViewController : UIViewController <MKMapViewDelegate,MKReverseGeocoderDelegate>{
    IBOutlet MKMapView *_mapView;
    CLLocationCoordinate2D _selCoordinate;
}
- (void) gotoLocation;
-(void) createMapPoint:(MKMapView *)mapView coordinateX:(double)coorX coordinateY:(double)coorY
                 Title:(NSString*)title Subtitle:(NSString*)subtitle;
@end
