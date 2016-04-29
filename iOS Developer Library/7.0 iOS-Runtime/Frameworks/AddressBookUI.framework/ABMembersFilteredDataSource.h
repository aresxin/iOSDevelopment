/* Generated by RuntimeBrowser
   Image: /System/Library/Frameworks/AddressBookUI.framework/AddressBookUI
 */

@class <ABMembersDataSourceDelegate>, <ABStyleProvider>, NSArray, NSMapTable, NSString;

@interface ABMembersFilteredDataSource : NSObject <UITableViewDelegate, UITableViewDataSource> {
    void *_addressBook;
    <ABMembersDataSourceDelegate> *_delegate;
    BOOL _isInPopover;
    NSMapTable *_records;
    NSMapTable *_sectionTitles;
    <ABStyleProvider> *_styleProvider;
}

@property void* addressBook;
@property(copy,readonly) NSString * debugDescription;
@property <ABMembersDataSourceDelegate> * delegate;
@property(copy,readonly) NSString * description;
@property(readonly) unsigned int hash;
@property BOOL isInPopover;
@property(readonly) NSArray * records;
@property(retain) <ABStyleProvider> * styleProvider;
@property(readonly) Class superclass;

- (void)addRecords:(id)arg1 toSection:(int)arg2;
- (void*)addressBook;
- (unsigned int)count;
- (void)dealloc;
- (id)delegate;
- (BOOL)isInPopover;
- (int)numberOfSectionsInTableView:(id)arg1;
- (id)records;
- (void)removeAllRecords;
- (void)scrollViewWillBeginDragging:(id)arg1;
- (id)sectionArrayAtIndex:(int)arg1;
- (void)setAddressBook:(void*)arg1;
- (void)setDelegate:(id)arg1;
- (void)setIsInPopover:(BOOL)arg1;
- (void)setStyleProvider:(id)arg1;
- (void)setTitle:(id)arg1 forSection:(int)arg2;
- (id)styleProvider;
- (id)tableView:(id)arg1 cellForRowAtIndexPath:(id)arg2;
- (void)tableView:(id)arg1 didSelectRowAtIndexPath:(id)arg2;
- (float)tableView:(id)arg1 heightForHeaderInSection:(int)arg2;
- (float)tableView:(id)arg1 heightForRowAtIndexPath:(id)arg2;
- (int)tableView:(id)arg1 numberOfRowsInSection:(int)arg2;
- (id)tableView:(id)arg1 titleForHeaderInSection:(int)arg2;
- (void)tableView:(id)arg1 willDisplayCell:(id)arg2 forRowAtIndexPath:(id)arg3;
- (id)titleForSection:(int)arg1;
- (id)viewForFooterInTableView:(id)arg1;
- (id)viewForHeaderInTableView:(id)arg1;

@end