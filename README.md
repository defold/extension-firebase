[![Actions Status Alpha](https://github.com/defold/extension-firebase/actions/workflows/bob.yml/badge.svg)](https://github.com/defold/extension-firebase/actions)

# Firebase
Firebase is Google's app platform that helps you quickly develop high-quality apps and grow your business. This repository contains the core components required by the various products included in Firebase. It is not intended for use on its own.

---

### Configure Android Gradle dependencies
The Gradle dependencies used by this extension need to match the ones specified in the [Release Notes](https://firebase.google.com/support/releases)
* Add Gradle dependencies to `extension/manifests/android/build.gradle`


### Configure Swift Package Manager dependencies
The Swift package dependencies used by this extension need to match the ones specified in the [Release Notes](https://firebase.google.com/support/releases)

* Add iOS Swift package dependencies to `firebase/manifests/ios/SwiftPackages.json`
* Add macOS Swift package dependencies to `firebase/manifests/osx/SwiftPackages.json`

All Firebase extensions used in a project must declare the same `firebase-ios-sdk` version, otherwise the build fails with conflicting requirements.
