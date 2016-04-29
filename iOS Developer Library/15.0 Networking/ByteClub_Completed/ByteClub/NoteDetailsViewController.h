//
//  NoteDetailsViewController.h
//  ByteClub
//
//  Created by Charlie Fulton on 7/28/13.
//  Copyright (c) 2013 Razeware. All rights reserved.
//

#import <UIKit/UIKit.h>

@class NoteDetailsViewController;
@class DBFile;

@protocol NoteDetailsViewControllerDelegate <NSObject>

- (void)noteDetailsViewControllerDidCancel:(NoteDetailsViewController*)controller;
- (void)noteDetailsViewControllerDoneWithDetails:(NoteDetailsViewController*)controller;

@end

@interface NoteDetailsViewController : UITableViewController

@property (nonatomic, weak) id<NoteDetailsViewControllerDelegate> delegate;
@property (nonatomic, strong) DBFile *note;
@property (nonatomic, strong) NSURLSession *session;
@end
