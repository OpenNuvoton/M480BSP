# OTAServerDemo Android App Component Description (for SCA / SBOM)

This document provides component metadata for the **OTAServerDemo Android application** under `Utilities/androidApp`, so it can be used directly in downstream SBOM generation (CycloneDX format).

## 1) Component Identity

- Component name (`name`): `OTAServerDemo Android App`
- Component type (`type`): `application`
- Supplier / author: `Nuvoton Technology Corporation`
- Version: `2.1.2` (identified from `app/build.gradle`)
- Package / application ID: `com.nuvoton.otaserverdemo`
- License: `Apache-2.0` for Nuvoton-owned portions, unless otherwise noted
- Evidence path: `Utilities/androidApp`
- Key source and configuration files:
  - `Utilities/androidApp/LICENSE.md`
  - `Utilities/androidApp/OTAServerDemo/OTAServerDemo/app/build.gradle`
  - `Utilities/androidApp/OTAServerDemo/OTAServerDemo/build.gradle`
  - `Utilities/androidApp/OTAServerDemo/OTAServerDemo/settings.gradle`
  - `Utilities/androidApp/OTAServerDemo/OTAServerDemo/app/src/main/AndroidManifest.xml`
  - `Utilities/androidApp/OTAServerDemo/OTAServerDemo/app/src/main/java/com/nuvoton/otaserverdemo/MainActivityWifi.kt`
- Binary artifacts:
  - `Utilities/androidApp/OTA_Update_App.apk`
  - `Utilities/androidApp/OTAServerDemo/OTAServerDemo/app/debug/app-debug.apk`
  - `Utilities/androidApp/OTAServerDemo/OTAServerDemo/app/libs/otaserver-debug.aar`
  - `Utilities/androidApp/OTAServerDemo/OTAServerDemo/app/libs/otaserver-release.aar`
  - `Utilities/androidApp/OTAServerDemo/OTAServerDemo/otaserver-debug/otaserver-debug2.aar`
  - `Utilities/androidApp/OTAServerDemo/OTAServerDemo/app/otaserver-libs.zip`

## 2) Evidence for Version and License

Primary evidence in this repository:

- `Utilities/androidApp/LICENSE.md`
  - Copyright notice shows `Copyright (c) 2026 Nuvoton Technology Corporation.`
  - License text states that Nuvoton-owned portions are licensed under Apache License, Version 2.0, unless otherwise noted.
  - SHA-256: `782b920914870fa3f01b09b842f4c847b3bdb3c9bf08773dc51bdc6cfd8d0d11`
- `Utilities/androidApp/OTAServerDemo/OTAServerDemo/app/build.gradle`
  - Application ID: `com.nuvoton.otaserverdemo`
  - Version code: `1`
  - Version name: `2.1.2`
  - Compile SDK: `28`
  - Target SDK: `28`
  - Min SDK: `21`
  - SHA-256: `83d17a226cba467deaaca5581776ff04627bb419e66588da62698145bc6c0719`
- `Utilities/androidApp/OTAServerDemo/OTAServerDemo/app/src/main/AndroidManifest.xml`
  - Manifest package: `com.nuvoton.otaserverdemo`
  - Declares `MainActivityWifi` launcher activity.
  - SHA-256: `4623cd26157174b04ddcafb436f7f16f2b25a4912781b71e575bcd316a6e4ea0`
- `Utilities/androidApp/OTAServerDemo/OTAServerDemo/gradle/wrapper/gradle-wrapper.properties`
  - Gradle distribution URL: `https://services.gradle.org/distributions/gradle-6.5-all.zip`
  - SHA-256: `8a1082e5fa19ab3b784244617eeae35d7cc4ae0e4660b4eb2dc20dea30f6f5ca`
- `Utilities/androidApp/OTAServerDemo/OTAServerDemo/gradle/wrapper/gradle-wrapper.jar`
  - SHA-256: `381dff8aa434499aa93bc25572b049c8c586a67faff2c02f375e4f23e17e49de`
  - SHA-1: `636cf935a0fd1451657a4112974b3500cce3ab84`

## 3) License Handling Guidance

For CycloneDX output, use SPDX license ID directly for the Nuvoton-owned Android application component:

- `licenses[0].license.id = Apache-2.0`

The local `LICENSE.md` explicitly notes that third-party software, libraries, tools, and other components may be subject to separate license terms. Treat the Maven/Android dependencies and the Gradle wrapper as separate third-party components where your SBOM policy requires dependency-level reporting.

## 4) Functional / Technical Scope

The Android app is an OTA server demo utility for the Secure OTA sample workflow. It includes:

- Kotlin Android application source for `MainActivityWifi`.
- Android resources and launcher assets.
- Pre-built APK artifacts.
- Pre-built OTA server AAR artifacts.
- Gradle wrapper and Android Gradle project files used to build the application.

## 5) Suggested CycloneDX Field Mapping

Recommended component fields:

- `type`: `application`
- `bom-ref`: `pkg:generic/otaserverdemo-android@2.1.2?source=vendored&path=Utilities/androidApp`
- `name`: `OTAServerDemo Android App`
- `version`: `2.1.2`
- `scope`: `required`
- `author`: `Nuvoton Technology Corporation`
- `purl`: `pkg:generic/otaserverdemo-android@2.1.2`
- `description`: `Nuvoton OTAServerDemo Android application and related pre-built APK/AAR artifacts under Utilities/androidApp.`
- `licenses[0].license.id`: `Apache-2.0`
- `properties` (recommended custom properties):
  - `src_path = Utilities/androidApp`
  - `bsp:file-path = Utilities/androidApp`
  - `integration = vendored_source_and_binary`
  - `bsp:component-origin = first-party`
  - `bsp:component-source = Nuvoton Technology Corporation`
  - `bsp:evidence-file = Document/SBOM/components/sca_androidapp.json`
  - `bsp:evidence-path = Utilities/androidApp`
  - `bsp:license-file = Utilities/androidApp/LICENSE.md`
  - `bsp:application-id = com.nuvoton.otaserverdemo`
  - `bsp:version-code = 1`
  - `bsp:version-evidence = Utilities/androidApp/OTAServerDemo/OTAServerDemo/app/build.gradle (versionName 2.1.2)`
  - `bsp:gradle-distribution = gradle-6.5-all`
  - `bsp:build-tool = Android Gradle Plugin 4.1.1`
  - `bsp:kotlin-version = 1.3.61`

## 6) Suggested BOM-Ref and purl

Suggested values:

- `bom-ref`: `pkg:generic/otaserverdemo-android@2.1.2?source=vendored&path=Utilities/androidApp`
- `purl`: `pkg:generic/otaserverdemo-android@2.1.2`

## 7) CycloneDX JSON Component Example

```json
{
  "type": "application",
  "bom-ref": "pkg:generic/otaserverdemo-android@2.1.2?source=vendored&path=Utilities/androidApp",
  "name": "OTAServerDemo Android App",
  "version": "2.1.2",
  "scope": "required",
  "author": "Nuvoton Technology Corporation",
  "purl": "pkg:generic/otaserverdemo-android@2.1.2",
  "description": "Nuvoton OTAServerDemo Android application and related pre-built APK/AAR artifacts under Utilities/androidApp.",
  "licenses": [
    {
      "license": {
        "id": "Apache-2.0"
      }
    }
  ],
  "properties": [
    { "name": "src_path", "value": "Utilities/androidApp" },
    { "name": "bsp:file-path", "value": "Utilities/androidApp" },
    { "name": "integration", "value": "vendored_source_and_binary" },
    { "name": "bsp:component-origin", "value": "first-party" },
    { "name": "bsp:component-source", "value": "Nuvoton Technology Corporation" },
    { "name": "bsp:evidence-file", "value": "Document/SBOM/components/sca_androidapp.json" },
    { "name": "bsp:evidence-path", "value": "Utilities/androidApp" },
    { "name": "bsp:license-file", "value": "Utilities/androidApp/LICENSE.md" },
    { "name": "bsp:application-id", "value": "com.nuvoton.otaserverdemo" },
    { "name": "bsp:version-code", "value": "1" },
    { "name": "bsp:version-evidence", "value": "Utilities/androidApp/OTAServerDemo/OTAServerDemo/app/build.gradle (versionName 2.1.2)" }
  ]
}
```

## 8) Binary and File Hashes

- `Utilities/androidApp/LICENSE.md`
  - SHA-256: `782b920914870fa3f01b09b842f4c847b3bdb3c9bf08773dc51bdc6cfd8d0d11`
- `Utilities/androidApp/OTA_Update_App.apk`
  - SHA-256: `eb76dee752cc6441a5426b9b51f32588cfc6e3a57a7a11a57cf66c2d4af89d97`
  - SHA-1: `1cb6d32f34c82f2d576b0d6df48cb1f770b15631`
- `Utilities/androidApp/OTAServerDemo/OTAServerDemo/app/debug/app-debug.apk`
  - SHA-256: `94ff0fe849a47b96ee44d42a3c787e62e60d68515b15d25adefc503f12dbffc2`
  - SHA-1: `0afe8d96fee093394f9cd291ebfbbdbaac1defa8`
- `Utilities/androidApp/OTAServerDemo/OTAServerDemo/app/libs/otaserver-debug.aar`
  - SHA-256: `12a5eca514e692241eaab2ed65704f1a5b114246ef4644a6e14b5a9dbb3a187c`
- `Utilities/androidApp/OTAServerDemo/OTAServerDemo/app/libs/otaserver-release.aar`
  - SHA-256: `b445989fa1dd14212bedc95e0b0c3218bf0abd6ed30c8221a0d134eef778ff12`
- `Utilities/androidApp/OTAServerDemo/OTAServerDemo/otaserver-debug/otaserver-debug2.aar`
  - SHA-256: `cfb909222c8d6d9376e1a9da591d3e16a5382b2992006c4994bac3bbcfc70654`
- `Utilities/androidApp/OTAServerDemo/OTAServerDemo/app/otaserver-libs.zip`
  - SHA-256: `e22076e81bbad680d6b7197bc9ad9009cb48f891fb0fb3c84820f19f5b965153`
- `Utilities/androidApp/OTAServerDemo/OTAServerDemo/gradle/wrapper/gradle-wrapper.jar`
  - SHA-256: `381dff8aa434499aa93bc25572b049c8c586a67faff2c02f375e4f23e17e49de`
  - SHA-1: `636cf935a0fd1451657a4112974b3500cce3ab84`
- `Utilities/androidApp/OTAServerDemo/OTAServerDemo/gradlew`
  - SHA-256: `8c4c04dd98db1f00d49456dd162418a39312c5cb13d6865d783deb483bd1ed22`
- `Utilities/androidApp/OTAServerDemo/OTAServerDemo/gradlew.bat`
  - SHA-256: `0008d785920c9ff5cab17403e0270ccc7ceee8e169b6d67a82d96a5475fec5c9`
- `Utilities/androidApp/OTAServerDemo/OTAServerDemo/app/src/main/java/com/nuvoton/otaserverdemo/MainActivityWifi.kt`
  - SHA-256: `652d181f7871d05036fe992289ae477960d1c56ce4cc7f4e23b186e62cebd8b9`

## 9) Third-Party Dependency Notes

The Gradle build files reference third-party build/runtime dependencies, including:

- Gradle wrapper / Gradle distribution `6.5-all`.
- Android Gradle Plugin `4.1.1`.
- Kotlin Gradle plugin / Kotlin stdlib `1.3.61`.
- AndroidX AppCompat `1.1.0`, Core KTX `1.2.0`, ConstraintLayout `1.1.3`.
- Material Dialogs `2.8.1`.
- ACRA `4.9.2`.
- OkHttp MockWebServer `3.9.0`.
- `com.snatik:storage:2.1.0`.
- `com.orhanobut:logger:2.1.1`.
- `com.nabinbhandari.android:permissions:3.8`.
- Spongy Castle core/prov `1.58.0.0`.
- JUnit `4.12`, AndroidX test JUnit `1.1.1`, Espresso Core `3.2.0`.

These dependencies should be represented as separate components if generating a dependency-level Android SBOM.

## 10) Compliance Notes

- Keep `Utilities/androidApp/LICENSE.md` with the distributed Android app materials.
- The local license applies to Nuvoton-owned portions only; third-party dependencies and build tools require their own license records.
- `Utilities/androidApp/OTAServerDemo/OTAServerDemo/app/debug/output.json` records `versionName` as `1.0`, while `app/build.gradle` records `versionName "2.1.2"`. Treat `app/build.gradle` as the source version evidence and review pre-built APK metadata if binary-level release version traceability is required.
- `gradle-wrapper.jar` is a third-party Gradle component. In this repository, it is also covered by `SBOM/tools/binary-license-database.json` as Apache-2.0 with SHA-256 `381dff8aa434499aa93bc25572b049c8c586a67faff2c02f375e4f23e17e49de`.
