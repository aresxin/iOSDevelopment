//
//  nstimerViewController.h
//  nstimer
//
//  Created by scottlin on 09-7-8.
//  Copyright __MyCompanyName__ 2009. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface nstimerViewController : UIViewController {

	IBOutlet UILabel* label;
	NSTimer* timer;
}

@property(nonatomic,retain)UILabel* label;
@property(nonatomic,retain)NSTimer* timer;

-(IBAction)timerpause;

@end

