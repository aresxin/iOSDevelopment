//
//  MapViewController.m
//  DevelopGuide_iOS
//
//  Created by xin on 12-5-8.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "MapViewController.h"
#import "CustomAnnotation.h"

@implementation MapViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)didReceiveMemoryWarning
{
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

#pragma mark - View lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
//    [self createMapPoint:_mapView coordinateX:37.786996 coordinateY:-122.419281 
//                   Title:@"my annotation" Subtitle:@"sub content"];
//    [self createMapPoint:_mapView coordinateX:37.786996 coordinateY:-122.477989 
//                   Title:@"my annotation1" Subtitle:@"sub content1"];

    [self gotoLocation];
    
    NSMutableArray *annotations = [NSMutableArray array];
    
    CLLocationCoordinate2D q;
    q.latitude = 37.786996;
    q.longitude = -122.419281;
    CustomAnnotation *annot1 = [[CustomAnnotation alloc] initWithCoords:q 
                                                              withTitle:@"title1"
                                                           withSubTitle:@"subtitle 1"];
    [annotations addObject:annot1];
    [annot1 release];
    
    CLLocationCoordinate2D q1;
    q1.latitude = 37.786996;
    q1.longitude = -122.477989;
    CustomAnnotation *annot2 = [[CustomAnnotation alloc] initWithCoords:q1 
                                                              withTitle:@"title2"
                                                           withSubTitle:@"subtitle 2"];
    [annotations addObject:annot2];
    [annot2 release];

    [_mapView addAnnotations:annotations];
    
    /*
     确保所有annotation都在mapView的可视区域内
     */
    MKMapRect flyTo = MKMapRectNull;
    for (id <MKAnnotation> annotation in annotations) {
        MKMapPoint annotationPoint = MKMapPointForCoordinate(annotation.coordinate);
        MKMapRect pointRect = MKMapRectMake(annotationPoint.x, annotationPoint.y, 0, 0);
        if (MKMapRectIsNull(flyTo)) {
            flyTo = pointRect;
        } else {
            flyTo = MKMapRectUnion(flyTo, pointRect);
        }
    }
    
    // Position the map so that all overlays and annotations are visible on screen.
    _mapView.visibleMapRect = flyTo;

}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}

#pragma mark -
#pragma mare createPoint
/*
 设定mapView的显示中心区域
 */
- (void)gotoLocation
{
    // start off by default in San Francisco
    MKCoordinateRegion newRegion;
    newRegion.center.latitude = 37.786996;
    newRegion.center.longitude = -122.419281 ;
    newRegion.span.latitudeDelta = 0.112872;
    newRegion.span.longitudeDelta = 0.109863;
    
    [_mapView setRegion:newRegion animated:YES];
}

/*
 将annotation添加到mapview
 */
-(void) createMapPoint:(MKMapView *)mapView coordinateX:(double)coorX coordinateY:(double)coorY
				  Title:(NSString*)title Subtitle:(NSString*)subtitle{
	
	
	if ([title length] <= 0 || [subtitle length] <= 0) 
    {
        return;
    }
    
	if(mapView!=nil)
    {
		
		//set POI lat and lng
		CLLocationCoordinate2D p1;
		CustomAnnotation *annot;
		
		if(coorX && coorY)
        {
			
			p1.latitude=coorX;
			p1.longitude = coorY;
			annot = [[CustomAnnotation alloc] initWithCoords:p1 withTitle:title 
                                                withSubTitle:subtitle];
			
			            
			[mapView addAnnotation:annot];
			[annot release];
			
		}
		
	}
	return;
}	

#pragma mark -
#pragma mark detail button action
- (void) showDetails:(UIButton*)btn
{
    NSLog(@"detail button action down button tag is %d",btn.tag);
    NSLog(@"经度，纬度 是 %f and %f",_selCoordinate.latitude, 
          _selCoordinate.longitude);
    
    // 根据经度纬度取得真实地址
    MKReverseGeocoder *geocoder = [[MKReverseGeocoder alloc] 
                                   initWithCoordinate:_selCoordinate];
    geocoder.delegate = self;
    [geocoder start]; 
}

#pragma mark -
#pragma mark MKMapViewDelegate
- (MKAnnotationView *)mapView:(MKMapView *)theMapView viewForAnnotation:(id <MKAnnotation>)annotation
{
        
    // handle our two custom annotations
    //
    if ([annotation isKindOfClass:[CustomAnnotation class]]) // for Golden Gate Bridge
    {
        /*test start*/
        static int tagNum = 1;
        /*test end*/
        // try to dequeue an existing pin view first
        static NSString* customAnnotation = @"customAnnotationIdentifier";
        MKPinAnnotationView* pinView = (MKPinAnnotationView *)
        [_mapView dequeueReusableAnnotationViewWithIdentifier:customAnnotation];
        if (!pinView)
        {
            // if an existing pin view was not available, create one
            MKPinAnnotationView* annotationView = [[[MKPinAnnotationView alloc]
                                                   initWithAnnotation:annotation reuseIdentifier:customAnnotation] autorelease];
            annotationView.pinColor = MKPinAnnotationColorGreen;
            annotationView.animatesDrop = YES;
            annotationView.canShowCallout = YES;
            
            // add a detail disclosure button to the callout which will open a new view controller page
            //
            // note: you can assign a specific call out accessory view, or as MKMapViewDelegate you can implement:
            // - (void)mapView:(MKMapView *)mapView annotationView:(MKAnnotationView *)view calloutAccessoryControlTapped:(UIControl *)control;
            //
            UIButton* rightButton = [UIButton buttonWithType:UIButtonTypeDetailDisclosure];
            rightButton.tag = tagNum;
            [rightButton addTarget:self
                            action:@selector(showDetails:)
                  forControlEvents:UIControlEventTouchUpInside];
            annotationView.rightCalloutAccessoryView = rightButton;
            
            
            UIImageView *sfIconView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"SFIcon.png"]];
            annotationView.leftCalloutAccessoryView = sfIconView;
            [sfIconView release];
            
            tagNum++;
            
            return annotationView;
        }
        else
        {
            pinView.annotation = annotation;
        }
        return pinView;
    }
    return nil;
}

- (void)mapView:(MKMapView *)mapView didSelectAnnotationView:(MKAnnotationView *)view
{
    NSLog(@"MKAnnotView is %@",view.annotation.title);
    _selCoordinate = view.annotation.coordinate;
}

#pragma mark - 
#pragma mark MKReverseGeocoderDelegate
- (void)reverseGeocoder:(MKReverseGeocoder *)geocoder didFindPlacemark:(MKPlacemark *)placemark 
{
    NSString *streetAddress = placemark.thoroughfare;
    NSLog(@"streetAddress is ---%@",streetAddress);
    NSString *city = placemark.locality;
    NSLog(@"city is ---%@",city);
    NSString *state = placemark.administrativeArea;
    NSLog(@"state is ---%@",state);
    NSString *zip = placemark.postalCode;
    NSLog(@"zip is ---%@",zip);
    // Do something with information
    geocoder.delegate = nil;
    [geocoder autorelease];
}
// There are at least two types of errors:
//   - Errors sent up from the underlying connection (temporary condition)
//   - Result not found errors (permanent condition).  The result not found errors
//     will have the domain MKErrorDomain and the code MKErrorPlacemarkNotFound
- (void)reverseGeocoder:(MKReverseGeocoder *)geocoder didFailWithError:(NSError *)error
{
    NSLog(@"Error resolving coordinates: %@", [error localizedDescription]);
    geocoder.delegate = nil;
    [geocoder autorelease];
}

@end
