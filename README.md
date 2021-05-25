# Firebase
Firebase is Google's mobile platform that helps you quickly develop high-quality apps and grow your business. This repository contains the core components required by the various products included in Firebase. It is not intended for use on its own.

---

## Development notes
Use this guide when setting up or upgrading this core extension and the extensions for each of the Firebase products (such as analytics and remote config). The extensions are using the [Firebase C++ SDK](https://firebase.google.com/docs/cpp/setup). Current version: 7.3.0.

* Download link: https://firebase.google.com/download/cpp
* Direct download link: https://dl.google.com/firebase/sdk/cpp/firebase_cpp_sdk_7.3.0.zip


### Copy includes
Copy header files from `firebase_cpp_sdk/include`.


### Copy Android Java JAR dependencies
The dependencies used by this extension need to match the ones specified in `firebase_cpp_sdk/Android/firebase_dependencies.gradle` -> `firebaseDependenciesMap -> 'analytics'`. Also specified in `readme.md` in the root of the unzipped `firebase_cpp_sdk_7.3.0.zip`.


#### Copy Android C++ library dependencies
Copy libs from `firebase_cpp_sdk/libs/android/armeabi-v7a/c++/*` and `firebase_cpp_sdk/libs/android/arm64-v8a/c++/*`


#### Copy iOS dependencies
Setup for iOS is made without CocoaPods using a direct download of the [Firebase iOS SDK from GitHub](https://github.com/firebase/firebase-ios-sdk/releases). It is important to use a version of the iOS SDK matching the iOS dependencies in `readme.md` in the root of the unzipped `firebase_cpp_sdk_7.3.0.zip` file.

* Copy frameworks from iOS SDK. Note that Defold doesn't support `*.xcframework` files. You need to unpack all the `*.framework` files from `*.xcframework` and put to folders according to architecture.
* Copy libs from CPP SDK. From `firebase_cpp_sdk/libs/ios/device-arm64/`, `firebase_cpp_sdk/libs/ios/device-armv7/` and `firebase_cpp_sdk/libs/ios/simulator-x86_64/`.
