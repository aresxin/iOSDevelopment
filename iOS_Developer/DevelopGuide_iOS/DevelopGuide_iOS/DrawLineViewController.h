//
//  DrawLineViewController.h
//  DrawLine
//
//  Created by neusoft  on 11-7-6.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "QuatzeLine.h"
#import "DrawLine.h"

@interface DrawLineViewController : UIViewController {

	QuatzeLine *lineView;
    
    DrawLine  *drawLineV;
}
- (IBAction) setNeedPlay:(id)sender;
@end

