vlc-sdk
=======

###Receiving a SDK Key

Request a SDK key online at [http://app.velocee.com/generic](http://app.velocee.com/generic)



###Installation


You can install the SDK either manually or with CocoaPods (preferred).

#####Using CocoaPods

Add the following line to the podfile:
```
pod "vlc-sdk", :git => "https://github.com/Velocee/vlc-sdk.git", :tag => "2.1.7"
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


###Audio Plus

Audio+ enables playing user adapted audio content. The module provides a player and retrieves the user specific audio content; it does not include a user interface code. Audio+ plays the track through the current available audio interface and fully supports bluetooth.

#####Implementation Notes

The Audio+ is initialized with Velocee’s SDK initialization; no additional initialization required. When audio playing is needed the following should be followed:

Call audioPlay or audioPlayAtIndex 
Show audio interface screen and update it accordingly (see below)
Call to audioPause, audioPrev & audioNext upon user request

The API provides several methods for getting the audio data, mostly for updating the user interface. Implementors should call the audioRegisterPlaybackEvents to be notified of events where onTrackStart method reflects a new audio track starts playing; Once such a notification arrives, the audio track information can be retrieved via the audioGetMediaInfo call. 
Querying the  audioGetProgress returns the current playing progress and should be called periodically (preferably using a timer or thread). 


#####Properties

The Audio+ module will show the relevant track name/track author in the “Now playing info canter” of OSX and will continue to play in the background (if the host app set the background mode/audio capability), and will resume playing from the last stopped point between application launches.


#####API

```
-(void) audioPlay
```
Starts playback.

```
-(void) audioPrev
```
Starts playback of the previous track in the playlist.

```
-(void) audioNext
```
Starts playback of the next track in the playlist.

```
-(void) audioPause
```
Pauses playback.

```
-(void) audioPlayAtIndex:(int) index
```
Starts playback of a specific track.

```
-(BOOL) audioIsPlaying
```
Returns whether the mediaplayer is playing.

```
-(int) audioGetProgress
```
Gets the current playback position in milliseconds.

```
- (vlcMediaInfo *) audioGetMediaInfo
```
Returns track information using the vlcMediaInfo interface. The interface has four properties:
	NSString *title: current track name
	NSString *author: current tracks author
	int length: length of track, in millisec
	NSArray *playlistURL: array of strings with track names

```
- (void) audioRegisterPlaybackEvents
```
Register for playback events.

```
- (void) audioUnregisterPlaybackEvents
```
Unregister for playback events.
The playback events are defined in VlcAudioProtocol which has two methods:

```
- (void) onTrackStart:(NSString *)title :(NSString *)author :(int)timeInMilli
```
Triggered when a new track is started.

```
- (void) onPlaylistLoaded:(NSArray *)titles
```
Triggered when new playlist is loaded from the server.

