//
//  VlcSdk.h
//  VlcSdk
//
//  Created by Velocee on 7/9/14.
//  Copyright (c) 2014 Velocee. All rights reserved.
//
#import <UIKit/UIKit.h>

#define LauncherSitesUpdatedNotification @"LauncherSitesUpdatedNotification"
#define VLCSDK_USE_PROGRESS_HUD 0

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



@interface VlcSdk : UIResponder<UITabBarControllerDelegate>

@property (copy, nonatomic) void (^backgroundSessionCompletionHandler)();

+(VlcSdk *)getObj;
-(id)setDelegate:(UIViewController <UIWebViewDelegate> *)view;
-(void)veloceeStart:(NSString *)key;
-(void)veloceeStart:(NSString *)key locale:(NSString *)locale;
-(void)veloceeDlComplete;
-(void) addToReadingList :(NSString*)pageUrl :(NSString*)pageTitle;
-(void) performFetch: (UIApplication *)application performFetchWithCompletionHandler:(void (^)(UIBackgroundFetchResult))completionHandler;
-(void) bgCompleteNotification: (void (^)())completionHandler;


/* helpers */
-(id)vlcGetData:(vlcDataType)type;
-(void)getCacheStatsParameters:(void (^)(NSString *s))completionBlock;


/* operations */
- (NSString*) GetCachedResourceUrl:(NSString *)originalUrl;
- (BOOL) GetCachedResourceUrlEx:(NSString **)originalUrl;
- (NSData*) GetCachedResourceData:(NSString *)originalUrl;
- (UINavigationController *) sendLogFile;
- (void) SetLogLevel:(VlcLogLevels) logLevel;
- (void) SetLocale:(NSString *)locale;

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

