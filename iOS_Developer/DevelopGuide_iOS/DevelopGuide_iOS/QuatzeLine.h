//
//  QuatzeLine.h
//  DrawLine
//
//  Created by neusoft  on 11-7-6.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h> 

@interface QuatzeLine : UIView {

	CGPoint startPon;
	CGPoint movePon;
	CGFloat mywidth;
}
@property CGFloat mywidth;
@end
