[![Actions Status Alpha](https://github.com/defold/extension-firebase/actions/workflows/bob.yml/badge.svg)](https://github.com/defold/extension-firebase/actions)

![](https://img.shields.io/badge/Firebase%20CPP%20SDK-8.8.0-green)
![](https://img.shields.io/badge/Firebase%20iOS%20SDK-8.10.0-green)


# Firebase
Firebase is Google's mobile platform that helps you quickly develop high-quality apps and grow your business. This repository contains the core components required by the various products included in Firebase. It is not intended for use on its own.

---

## Development notes
Use this guide when setting up or upgrading this core extension and the extensions for each of the Firebase products (such as analytics and remote config). The extensions are using the [Firebase C++ SDK](https://firebase.google.com/docs/cpp/setup) and the [Firebase iOS SDK](https://github.com/firebase/firebase-ios-sdk).

* Firebase C++ SDK download link: https://firebase.google.com/download/cpp
* Firebase C++ SDK direct download link: https://dl.google.com/firebase/sdk/cpp/firebase_cpp_sdk_8.8.0.zip

### Copy includes
Copy header files from `firebase_cpp_sdk/include`.


### Configure Android Gradle dependencies
The Gradle dependencies used by this extension need to match the ones specified in the Firebase C++ SDK.

* Add Gradle dependencies to `extension/manifests/android/build.gradle`
   * Specified in `firebase_cpp_sdk/Android/firebase_dependencies.gradle` -> [`firebaseDependenciesMap`](https://github.com/firebase/firebase-cpp-sdk/blob/v7.3.0/release_build_files/Android/firebase_dependencies.gradle)
   * Or in [`firebase_cpp_sdk/readme.md`](https://raw.githubusercontent.com/firebase/firebase-cpp-sdk/v7.3.0/release_build_files/readme.md)


#### Copy Android C++ library dependencies
Android C++ libraries should be copied from the Firebase C++ SDK to your extension.

* Copy libs from Firebase C++ SDK
   * `firebase_cpp_sdk/libs/android/armeabi-v7a/c++/*`
   * `firebase_cpp_sdk/libs/android/arm64-v8a/c++/*`


#### Copy iOS dependencies
Setup for iOS is made without CocoaPods using a direct download of the Firebase iOS SDK. It is important to use a version of the iOS SDK matching the iOS dependencies in `firebase_cpp_sdk/readme.md`.

* Firebase iOS SDK direct download link: https://github.com/firebase/firebase-ios-sdk/releases/download/8.10.0/Firebase.zip

* Copy frameworks from iOS SDK. Check the included `firebase_ios_sdk/README.md` to learn which frameworks you need (most Firebase products require the frameworks for Firebase Analytics as well as the frameworks specific to the product). Note that Defold doesn't support `*.xcframework` files. You need to unpack/open all the `*.framework` files from `*.xcframework` and put to folders according to architecture.
   * `firebase_ios_sdk/FirebaseProduct/*.xcframework/ios-arm64_armv7/*.framework` -> `extension/lib/ios`
   * `firebase_ios_sdk/FirebaseProduct/*.xcframework/ios-arm64_i386_x86_64-simulator/*.framework` -> `extension/lib/x86_64-ios`

* Copy libs from the Firebase C++ SDK
   * `firebase_cpp_sdk/libs/ios/device-arm64/` -> `extension/lib/arm64-ios/`
   * `firebase_cpp_sdk/libs/ios/device-armv7/` -> `extension/lib/armv7-ios/`
   * `firebase_cpp_sdk/libs/ios/simulator-x86_64/` -> `extension/lib/x86_64-ios/`
