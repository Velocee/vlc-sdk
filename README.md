vlc-sdk
=======

###Installation

You can install install the SDK either manually or with CocoaPods (preffered).

#####Using CocoaPods

Add the following line to the podfile:
```
pod "vlc-sdk", :git => "https://github.com/Velocee/vlc-sdk.git", :tag => "2.0.34"
```

#####Manualy

1. Download vlc-sdk as a zip file and extract it somewhere. Drag the SDK resources (libVlcSdk.a, VlcSdk.h and VlcSdkRes.bundle) to the project or add them by right clicking the Project Navigator and selecting ‘Add files to...“ . It is recommended to use “Copy Items..” and “Create groups…”.
2. Verify libVlcSdk.a id added to the project settings “Build Phases” / ”Link Binary With Libraries”.
4. Verify VlcSdkRes.bundle is added to the project settings “Build Phases” / “Copy Bundle Resources”.
5. Add the following frameworks/libraries to the project settings “Build Phases” / “Link Binary With Libraries”:
    - MediaPlayer.framework
    - SystemConfiguration.framework
    - AVFoundation.framework
    - JavaScriptCore.framework
    - CoreGraphics.framework
    - UIKit.framework
    - Foundation.framework
    - libsqlite3.0.dylib
6. In the project settings, add ”-ObjC” to “Other Linker Flags” located in “Build Settings” / “Linking”.


###Post Installation


1. In the project settings, enable “Background fetch” located in “Capabilities” / “Background Modes”.
2. In your application delegate, create or edit the performFetchWithCompletionHandler method to include the following line:
```
-(void)application:(UIApplication *)application performFetchWithCompletionHandler:(void (^)(UIBackgroundFetchResult))completionHandler {
[[VlcSdk getObj] performFetch: (UIApplication *)application performFetchWithCompletionHandler:(void (^)(UIBackgroundFetchResult))completionHandler];
}
```
In your application delegate, create or edit handleEventsForBackgroundURLSession to include the following line:
```
- (void)application:(UIApplication *)application handleEventsForBackgroundURLSession:(NSString *)identifier completionHandler:(void (^)())completionHandler {
    [[VlcSdk getObj]bgCompleteNotification:completionHandler];
}
```

###Usage

Get the sdk instance by calling [VlcSdk getObj] which returns a singleton. All methods are called from this object.


#####Initializing


The library requires a one time initialization upon application startup. You should call the method “veloceeStart” preferably in your application delegate / didFinishLaunchingWithOptions:

1. Add the sdk’s header file to your application delegate (#import “VlcSdk.h”).
2. Call [[VlcSdk getObj] veloceeStart: <your SDK key> ].


#####Using Within a WebView

The Velocee SDK provides an WebView delegate for the application’s WebView to use. In order to use Velocee’s WebView delegate you should use the SDK’s setDelegate method instead of the web view one. In case the application has a webview delegate it will be chained.

1. Add the sdk’s header file to your controller (#import “VlcSdk.h”).
2. call ```[webView setDelegate:[[VlcSdk getObj]setDelegate:self]];```


#####Using Within a Different View

In order to use Velocee’s cache from non-webview view the application must change the relevant urls to serve the content locally with a ‘http://127.0.0.1:8080/?url’ format. For example ‘http://www.foe.com/videos/1234/master.m3u8’ should change to
‘http://127.0.0.1:8080/?url=http://www.foe.com/videos/1234/master.m3u8’ . This applies for all cached resources (images/videos/etc).
The SDK provides a conversion method ‘GetCachedResourceUrl’ for convenience. It receives the URL (as NSString) and returns the resource-from-cache URL (as NSString). In case the input URL cannot be found in the cache the method returns the input unchanged. For example,
```
NSString *cachedUrl = [[VlcSdk getObj]GetCachedResourceUrl:inputUrl];
```
