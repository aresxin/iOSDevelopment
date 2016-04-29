/* Generated by RuntimeBrowser
   Image: /System/Library/Frameworks/MediaPlayer.framework/MediaPlayer
 */

@class MPMediaItem, MPMediaQuery, NSArray, NSString;

@interface MPMediaPlaylist : MPMediaItemCollection {
    NSArray *_representativeArtists;
    MPMediaQuery *_seedTracksQuery;
}

@property(getter=music_seedItem,readonly) MPMediaItem * music_seedItem;
@property(readonly) NSString * name;
@property(readonly) unsigned long long persistentID;
@property(readonly) unsigned int playlistAttributes;
@property(readonly) NSArray * seedItems;

+ (void)_createFilterableDictionary;
+ (BOOL)_isValidPlaylistProperty:(id)arg1;
+ (id)activeGeniusPlaylist;
+ (BOOL)canFilterByProperty:(id)arg1;

- (void).cxx_destruct;
- (int)_sortPlaylistByName:(id)arg1;
- (id)artworkCatalogsWithMaximumCount:(unsigned int)arg1;
- (BOOL)canPlayUsingNetworkType:(int)arg1;
- (unsigned int)count;
- (void)encodeWithCoder:(id)arg1;
- (BOOL)existsInLibrary;
- (void)generateGeniusArtworkWithImageSize:(struct CGSize { float x1; float x2; })arg1 completionHandler:(id)arg2 queue:(id)arg3;
- (unsigned int)hash;
- (id)initWithCoder:(id)arg1;
- (id)initWithMultiverseIdentifier:(id)arg1;
- (id)initWithPersistentID:(unsigned long long)arg1;
- (BOOL)isCloudMix;
- (BOOL)isEqual:(id)arg1;
- (id)items;
- (unsigned int)mediaTypes;
- (id)multiverseIdentifier;
- (id)music_seedItem;
- (id)name;
- (unsigned long long)persistentID;
- (unsigned int)playlistAttributes;
- (id)representativeArtists;
- (id)representativeItem;
- (id)seedItems;
- (id)seedTracksQuery;
- (id)valueForProperty:(id)arg1;

@end