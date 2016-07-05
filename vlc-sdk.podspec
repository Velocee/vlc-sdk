#
#  Be sure to run `pod spec lint vlc-sdk.podspec' to ensure this is a
#  valid spec and to remove all comments including this before submitting the spec.
#
Pod::Spec.new do |s|

  s.name         = "vlc-sdk"
  s.version      = "2.2.1.5"
  s.summary      = "Velocee VlcSdk"

  s.description  = <<-DESC
                   Velocee SDK for iPhone.
                   DESC

  s.homepage     = "http://www.velocee.com"
  s.license      = {
    :type => 'Commercial',
    :text => <<-LICENSE
            (c) Velocee
    LICENSE
  }
  s.author       = { "elibabila" => "support@velocee.com" }
  s.platform     = :ios, "7.0"
  s.source        = { :git => "https://github.com/Velocee/vlc-sdk.git", :tag => "2.2.1.5" }
  

  s.source_files = '*.h'
  s.resource = 'VlcSdkRes.bundle'
  s.frameworks = "MediaPlayer", "SystemConfiguration", "AVFoundation", "JavaScriptCore", "CoreGraphics", "UIKit", "Foundation"
  s.libraries = "sqlite3.0", "VlcSdk"
  s.preserve_paths = 'libVlcSdk.a'
  s.xcconfig     = { 'LIBRARY_SEARCH_PATHS' => '"$(PODS_ROOT)/vlc-sdk"' }
  s.dependency "AFNetworking", "~> 2.0"
  s.dependency 'CocoaAsyncSocket', '~> 7.3'
#  s.dependency 'MBProgressHUD', '~> 0.9'
  s.dependency 'CocoaLumberjack', '~> 2.0'
#  s.dependency 'MBCircularProgressBar'
end
