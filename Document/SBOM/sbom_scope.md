# Introduction

The MCU BSP SBOM package consists of two CycloneDX SBOM files: a Product SBOM and a Test Sample SBOM. The Product SBOM includes components that are included in, linked with, deployed to, or reasonably expected to be integrated into the final product firmware/software. The Test Sample SBOM includes components used only for examples, demonstrations, validation, or testing and not included in the product runtime unless explicitly integrated by the user.

This scope is based on the directories present in the current checkout.

# Product SBOM

Used for CRA compliance, product vulnerability management, and customer product integration risk assessment.

## Scope

Drivers, middleware, libraries, startup code, boot code, binaries, and source components that are compiled, linked, flashed, deployed, or reasonably expected to be integrated into the product by customers.

## Evidence

```text
.
└── Library
    ├── CMSIS
    ├── Device
    ├── FWUpdate
    ├── SmartcardLib
    ├── StdDriver
    └── UsbHostLib
```

# Test Sample SBOM

Used for transparent disclosure and internal/customer evaluation, but labeled as non-product runtime dependency.

## Scope

Sample code, demo projects, host-side test tools, sample validation scripts, test harnesses, and third-party components used by sample code.

## Evidence

```text
.
├── SampleCode
└── ThirdParty
```

## Third-Party Component Evidence

| Component | Evidence path | SCA metadata |
| --- | --- | --- |
| FatFs | `ThirdParty/FatFs` | `Document/SBOM/components/sca_fatfs.json` |
| FreeRTOS-Kernel | `ThirdParty/FreeRTOS` | `Document/SBOM/components/sca_freertos.json` |
| LibMAD | `ThirdParty/LibMAD` | `Document/SBOM/components/sca_libmad.json` |
| libjpeg | `ThirdParty/libjpeg` | `Document/SBOM/components/sca_libjpeg.json` |
| lwIP | `ThirdParty/lwIP` | `Document/SBOM/components/sca_lwip.json` |
| mbed TLS | `ThirdParty/mbedtls-2.13.0` | `Document/SBOM/components/sca_mbedtls.json` |
| paho.mqtt.embedded-c | `ThirdParty/paho.mqtt.embedded-c` | `Document/SBOM/components/sca_paho_mqtt_embedded_c.json` |
| uIP | `ThirdParty/uip-0.9` | `Document/SBOM/components/sca_uip.json` |
