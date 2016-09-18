//
//  VlcSdk.h
//  VlcSdk
//
//  Created by Velocee on 7/9/14.
//  Copyright (c) 2014 Velocee. All rights reserved.
//

#ifndef VLCSDK_H
#define VLCSDK_H

#import <UIKit/UIKit.h>
#import <WebKit/WebKit.h>

// auto generated sdk version
#define VELOCEE_SDK_VERSION @"AUTO_GEN"

#define LauncherSitesUpdatedNotification @"LauncherSitesUpdatedNotification"
#define VLCSDK_USE_PROGRESS_HUD 0
#define VLCSDK_MOTION_CONFIDENCE    2

typedef enum {
    vdata_clientId,
    vdata_whiteLabel,
//    vdata_settings_url,
    vdata_network_mode,
    vdata_feedback_url,
    vdata_should_bypass,
    vdata_cellular_sync_enabled,
    vdata_sync_permitted,
    vdata_auto_sync_started,
    vdata_battery_level_above_min,
    vdata_is_on_dev_server,
    vdata_is_on_prod_server,
    vdata_cache_stats_url
//    vdata_cache_stats_parameters
//    vdata_server_address
}vlcDataType;


typedef enum
{
    VlcLogCriticalLevel,
    VlcLogErrorLevel,
    VlcLogWarningLevel,
    VlcLogInfoLevel,
    VlcLogDebugLevel
} VlcLogLevels;


typedef enum {
    VlcWl_Prefix,
    VlcWl_Regex,
    VlcWl_FileExtension,
    VlcWl_Suffix
} VlcWhiteListTypes;



typedef enum
{
    vlcMotionStationary,
    vlcMotionWalking,
    vlcMotionRunning,
    vlcMotionCycling,
    vlcMotionAutomotive
} vlcMotionStates;

typedef enum
{
    vlcAudioCtrlNone,
    vlcAudioCtrlIdle,
    vlcAudioCtrlUpdatingGroup,
    vlcAudioCtrlGroupUpdated,
    vlcAudioCtrlPLaylistUpdated
} vlcAudioCtrlStates;


@interface vlcMediaInfo : NSObject
    @property (nonatomic, assign) NSString *title;
    @property (nonatomic, assign) NSString *author;
    @property (nonatomic, assign) int length;
    @property (nonatomic, assign) NSString *playlistURL;
@end


@protocol VlcAudioProtocol;
@protocol VlcMotionProtocol;


@interface VlcSdk : UIResponder<UITabBarControllerDelegate>

@property (copy, nonatomic) void (^backgroundSessionCompletionHandler)();

+(VlcSdk *)getObj;
-(id)setDelegate:(UIViewController <UIWebViewDelegate> *)view;
-(void) setWkWebView:(WKWebView *)wkWebView;
-(void) wkOnNewPage:(WKWebView *)wkWebView;
-(id)setWebViewDelegate:(NSObject <UIWebViewDelegate> *)delegate;
-(void)veloceeStart:(NSString *)key;
-(void)veloceeStart:(NSString *)key locale:(NSString *)locale;
-(void)veloceeDlComplete;
-(void) addToReadingList :(NSString*)pageUrl :(NSString*)pageTitle;
-(void) performFetch: (UIApplication *)application performFetchWithCompletionHandler:(void (^)(UIBackgroundFetchResult))completionHandler;
-(void) bgCompleteNotification: (void (^)())completionHandler;
-(void) setPrefixWhiteList: (NSArray *)whitelist;
-(void) setWhiteList: (NSArray *)whitelist;

/* helpers */
- (BOOL) isNetworkConnected;
-(id)vlcGetData:(vlcDataType)type;
-(void)getCacheStatsParameters:(void (^)(NSString *s))completionBlock;


/* operations */
- (NSString*) GetCachedResourceUrl:(NSString *)originalUrl;
- (NSURL*) GetCachedResourceUrlUrl:(NSURL *)originalUrl;
- (BOOL) GetCachedResourceUrlEx:(NSString **)originalUrl;
- (NSData*) GetCachedResourceData:(NSString *)originalUrl;
- (UINavigationController *) sendLogFile;
- (void) SetLogLevel:(VlcLogLevels) logLevel;
- (void) SetLocale:(NSString *)locale;
- (void) SetTag:(NSString *)tag;
- (BOOL) GetAudioStatus;
- (void) flushResources;


/* audio */
- (void) EnableAudio:(BOOL)enable;  /* for internal user */
- (void) _audioUpdateClientGroupBySite:(NSString *)site_id; /* for internal use */
- (void) StartAudio;
- (void) audioPlay;
- (void) audioPause;
- (void) audioNext;
- (void) audioPrev;
- (void) audioPlayNewList;
- (BOOL) audioIsPlaying;
- (void) audioSetProgress;
- (int) audioGetProgress;
- (void) audioPlayAtIndex:(int)index;
- (void) audioRegisterPlaybackEvents:(id<VlcAudioProtocol>) receiver;
- (void) audioUnregisterPlaybackEvents;
- (vlcMediaInfo *) audioGetMediaInfo;
- (void) audioSeekToTime:(int)seconds;
- (NSArray *) audioGetPlaylists;
- (NSDate*) audioGetLastPlayListUpdate;
- (vlcAudioCtrlStates) audioGetCurrentState;
- (void) audioSaveCurrentPlayState;
- (NSString*) audioGetCurrentPlaylistSource;
//- (UIViewController*) getPLayerViewController;
- (UIViewController*) getPLayerViewControllerWithSourceName:(NSString*)source andSiteUrl:(NSString*)sourceUrl;
- (UIViewController*) getPLayerViewControllerWithSourceName:(NSString*)source andSiteUrl:(NSString*)sourceUrl isSdk:(BOOL)isSdk siteId:(NSString*)siteId siteChanged:(BOOL)siteChanged;
/*
 * Get Custom player with custom nib and properties
 */
- (UIViewController*) getCustomPlayerViewControllerWithSourceName:(NSString*)source andSiteUrl:(NSString*)sourceUrl andBundle:(NSBundle*)bundle andNibName:(NSString*)nibName progressColor:(UIColor*)progressColor playlistCells:(NSArray*)playlistCells;
/*****************/
- (UIButton *) getAudioButton;
- (void) getShortUrlForUrl :(NSString*)longUrlStr :(void (^)(NSString *responseObj))onSuccess onFail:(void (^)())onFail;
- (NSInteger) audioGetNewItemsCount;
/*
 * Private methods
 */
- (void) _audioUpdatePlayerSourceId:(NSString *)sourceId sourceName:(NSString*)sourceName;
- (void) _audioSetShowPLayerOnLauncherLoad:(BOOL)value;
- (BOOL) _audioGetShowPLayerOnLauncherLoad;
- (UIView*) _audioGetBadgeViewWithParentView:(UIView*)parent internal:(BOOL)internal;
- (void)_audioSetBadgeWithBadgeView:(UIView*)badgeView value:(NSInteger)value;

/* motion */
- (BOOL) motionStartDetection:(id<VlcMotionProtocol>) receiver;
- (void) motionStopDetection;


/* dialogs */
-(UIViewController *)getMoviesViewController;
-(UIViewController *)getDeviceInfoViewController;
-(UIViewController *)getSyncCacheViewController:(UIView *)view;
-(UIViewController *)getSiteSelectionViewController;
-(UIViewController *)getReadingListViewController;
-(UIAlertView *)getCacheReportViewController;
-(UIViewController *) getLogViewController;


@end

@interface NSObject (VlcWebView)

@property (nonatomic, strong) NSObject *veloceeWebViewDelegate;

@end



@protocol VlcAudioProtocol <NSObject>

@optional

- (void) onTrackStart:(NSString *)title :(NSString *)author :(int)timeInSec;
- (void) onListLoaded:(NSArray *)titles;

@end


@protocol VlcMotionProtocol <NSObject>

@required
- (void) onMotionDetetion:(vlcMotionStates) newState;
@optional
- (void) onMotionLogEvents:(NSString *)message;

@end

#endif


