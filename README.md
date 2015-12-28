vlc-sdk
=======

###Receiving a SDK Key

Request a SDK key online at [http://app.velocee.com/generic](http://app.velocee.com/generic)



###Installation


You can install the SDK either manually or with CocoaPods (preferred).

#####Using CocoaPods

Add the following line to the podfile:
```
pod "vlc-sdk", :git => "https://github.com/Velocee/vlc-sdk.git", :tag => "2.0.99"
```

#####Manually

1. Download vlc-sdk as a zip file and extract it somewhere. Drag the SDK resources (libVlcSdk.a, VlcSdk.h and VlcSdkRes.bundle) to the project or add them by right clicking the Project Navigator and selecting “Add files to...“ . It is recommended to use “Copy Items..” and “Create groups…”
2. Verify libVlcSdk.a id added to the project settings “Build Phases” / ”Link Binary With Libraries”
3. Verify VlcSdkRes.bundle is added to the project settings “Build Phases” / “Copy Bundle Resources”
4. Add the following frameworks/libraries to the project settings “Build Phases” / “Link Binary With Libraries”:
    - MediaPlayer.framework
    - SystemConfiguration.framework
    - AVFoundation.framework
    - JavaScriptCore.framework
    - CoreGraphics.framework
    - UIKit.framework
    - Foundation.framework
    - libsqlite3.0.dylib
5. In the project settings, add ”-ObjC” to “Other Linker Flags” located in “Build Settings” / “Linking”


#####Third Party Libraries

The SDK uses the following third party libraries which must be added manually.

AFNetworking
```
https://github.com/AFNetworking/AFNetworking
```

CocoaAsyncSocket
```
https://github.com/robbiehanson/CocoaAsyncSocket
```

CocoaLumberjack
```
https://github.com/CocoaLumberjack/CocoaLumberjack
```


###Post Installation


1. In the project settings, enable “Background fetch” located in “Capabilities” / “Background Modes”
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


Get the sdk instance by calling [VlcSdk getObj] which returns a singleton. All methods are called using this object.


#####Resource Support

Supported resources are images (all types) and HTML5 videos.


#####Initializing


The library requires a one time initialization upon application startup. You should call the method “veloceeStart” preferably in your application delegate / didFinishLaunchingWithOptions:

1. Add the sdk’s header file to your application delegate (#import “VlcSdk.h”)
2. Call [[VlcSdk getObj] veloceeStart: <your SDK key> ]


#####Using Within a WebView

The Velocee SDK provides an WebView delegate for the application’s WebView to use. In order to use Velocee’s WebView delegate you should use the SDK’s setDelegate method instead of the web view one. In case the application has a webview delegate it will be chained.

1. Add the sdk’s header file to your controller (#import “VlcSdk.h”)
2. call ```[webView setDelegate:[[VlcSdk getObj]setDelegate:self]];```


#####Getting Cached Videos From Within a Different View

In order to use Velocee’s cache from non-webview view the application must change the relevant video urls to serve the content locally. The SDK provides several conversion methods for convenience: 
* ```- (NSString*) GetCachedResourceUrl:(NSString *)originalUrl``` receives the URL (as NSString) and returns the resource-from-cache URL.
* ```- (NSURL*) GetCachedResourceUrlUrl:(NSURL *)originalUrl``` is similar to the above but receives and returns a NSURL instead of NSString.
Both methods returns the input unchanged in case the input URL cannot be found in the cache. 
* ```- (BOOL) GetCachedResourceUrlEx:(NSString **)originalUrl``` - returns wherever resource was cached and alter an input URL string.


#####Labeling The Data

Your application data needs to be labeled in order to fine tune Velocee's recommendation algorithm. Any text can be used as a label. In order to set the current label use the SetTag method ```- (void) SetTag:(NSString *)tag```.
Once a label is set it affects all resources until a new label is set or the application is idle for a period of time.
