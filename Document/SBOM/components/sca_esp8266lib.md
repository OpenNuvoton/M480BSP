# Esp8266Lib Third-Party Component Description (for SCA / SBOM)

This document provides component metadata for the **Esp8266Lib** source code under `SampleCode/SecureApplication/SecureOTADemo/Esp8266Lib`, so it can be used directly in downstream SBOM generation (CycloneDX format).

## 1) Component Identity

- Component name (`name`): `Esp8266Lib`
- Component type (`type`): `library`
- Supplier / author: `Tilen Majerle`
- Bundled third-party code: `Protothreads` by `Adam Dunkels` / `Swedish Institute of Computer Science`
- Version: `2.3.0` (identified from `esp8266.h`)
- License: `MIT AND BSD-3-Clause`
- Evidence path: `SampleCode/SecureApplication/SecureOTADemo/Esp8266Lib`
- Key implementation files:
  - `SampleCode/SecureApplication/SecureOTADemo/Esp8266Lib/esp8266.c`
  - `SampleCode/SecureApplication/SecureOTADemo/Esp8266Lib/esp8266.h`
  - `SampleCode/SecureApplication/SecureOTADemo/Esp8266Lib/buffer.c`
  - `SampleCode/SecureApplication/SecureOTADemo/Esp8266Lib/buffer.h`
  - `SampleCode/SecureApplication/SecureOTADemo/Esp8266Lib/esp8266_config_template.h`
  - `SampleCode/SecureApplication/SecureOTADemo/Esp8266Lib/esp8266_ll_template.c`
  - `SampleCode/SecureApplication/SecureOTADemo/Esp8266Lib/esp8266_ll_template.h`
  - `SampleCode/SecureApplication/SecureOTADemo/Esp8266Lib/pt/*.h`

## 2) Evidence for Version and License

Primary evidence in this repository:

- `SampleCode/SecureApplication/SecureOTADemo/Esp8266Lib/esp8266.h`
  - Header shows `\version v2.3.0`
  - Header shows `\license MIT`
  - Header copyright notice shows `Copyright (c) 2016 Tilen Majerle`
  - Include guard value shows `#define ESP_H 230`
  - SHA-256: `ca3d07da6104476cccec0385808de2d706698c75eb00ccafd63ca7af65d38f8e`
- `SampleCode/SecureApplication/SecureOTADemo/Esp8266Lib/buffer.h`
  - Header shows `\license MIT`
  - Header copyright notice shows `Copyright (c) 2016 Tilen Majerle`
  - Include guard value shows `#define BUFFER_H 110`
  - SHA-256: `f5bcbaabd4274d316f9cf9e8dd543f7aba619dad62501bba898ebf7644ae0a28`
- `SampleCode/SecureApplication/SecureOTADemo/Esp8266Lib/pt/pt.h`
  - Header identifies Protothreads / Contiki code
  - Header copyright notice shows `Copyright (c) 2004-2005, Swedish Institute of Computer Science.`
  - Header author shows `Adam Dunkels <adam@sics.se>`
  - BSD 3-Clause style license text is present in the header
  - Revision ID shows `pt.h,v 1.7 2006/10/02 07:52:56`
  - SHA-256: `0645bfeca462492f139611fabe83f47bcee3337ee56db4f43886ad8e2665d2d4`
- `SampleCode/SecureApplication/SecureOTADemo/Esp8266Lib/pt/lc.h`
  - Header identifies Protothreads code
  - BSD 3-Clause style license text is present in the header
  - Revision ID shows `lc.h,v 1.2 2005/02/24 10:36:59`
  - SHA-256: `2c6d0a32c14721fb6b357717f81658267842cf0be94c5c4853840cd55103a0ee`

## 3) License Handling Guidance

The Esp8266Lib directory contains two license families:

- ESP8266 AT parser, buffer, configuration template, and low-level template source files from Tilen Majerle use the MIT license text.
- The bundled `pt/` Protothreads headers use a BSD 3-Clause style license text from the Swedish Institute of Computer Science.

For CycloneDX output, use an SPDX expression for the combined vendored source component:

- `licenses[0].expression = MIT AND BSD-3-Clause`

Audit note: `esp8266_ll_template.h` contains a Doxygen line `\license GNU GPL v3`, but the same file also embeds the full MIT license text, and `esp8266_ll_template.c` embeds the MIT license text. Treat this as inconsistent upstream metadata that should be reviewed by product compliance if that template header is distributed or used.

## 4) Functional / Technical Scope

Esp8266Lib provides an embedded C parser and control layer for ESP8266 modules using AT commands, including:

- ESP8266 initialization and reset control through a low-level callback interface.
- AT command handling for basic device control, Wi-Fi configuration, TCP/IP connections, and related status parsing.
- UART send/receive integration hooks through `esp8266_ll_template.*`.
- Cyclic buffer support through `buffer.*`.
- Cooperative command/state handling through bundled Protothreads headers in `pt/`.

## 5) Suggested CycloneDX Field Mapping

Recommended component fields:

- `type`: `library`
- `bom-ref`: `pkg:generic/esp8266lib@2.3.0?source=vendored&path=SampleCode/SecureApplication/SecureOTADemo/Esp8266Lib`
- `name`: `Esp8266Lib`
- `version`: `2.3.0`
- `scope`: `required`
- `author`: `Tilen Majerle; Adam Dunkels / Swedish Institute of Computer Science (bundled Protothreads)`
- `purl`: `pkg:generic/esp8266lib@2.3.0`
- `description`: `Esp8266Lib is a vendored embedded C ESP8266 AT command parser and support library, including Tilen Majerle ESP8266/buffer sources and bundled Protothreads headers.`
- `licenses[0].expression`: `MIT AND BSD-3-Clause`
- `properties` (recommended custom properties):
  - `bsp:file-path = SampleCode/SecureApplication/SecureOTADemo/Esp8266Lib`
  - `src_path = SampleCode/SecureApplication/SecureOTADemo/Esp8266Lib`
  - `integration = vendored_source`
  - `bsp:component-origin = third-party`
  - `bsp:component-source = Tilen Majerle ESP8266 AT commands parser; bundled Protothreads by Adam Dunkels / SICS`
  - `bsp:evidence-file = Document/SBOM/components/sca_esp8266lib.json`
  - `bsp:evidence-path = SampleCode/SecureApplication/SecureOTADemo/Esp8266Lib`
  - `bsp:version-evidence = SampleCode/SecureApplication/SecureOTADemo/Esp8266Lib/esp8266.h (\version v2.3.0)`
  - `bsp:license-note = esp8266_ll_template.h contains conflicting Doxygen license metadata: \license GNU GPL v3, while the embedded full license text is MIT.`

## 6) Suggested BOM-Ref and purl

Suggested values:

- `bom-ref`: `pkg:generic/esp8266lib@2.3.0?source=vendored&path=SampleCode/SecureApplication/SecureOTADemo/Esp8266Lib`
- `purl`: `pkg:generic/esp8266lib@2.3.0`

## 7) CycloneDX JSON Component Example

```json
{
  "type": "library",
  "bom-ref": "pkg:generic/esp8266lib@2.3.0?source=vendored&path=SampleCode/SecureApplication/SecureOTADemo/Esp8266Lib",
  "name": "Esp8266Lib",
  "version": "2.3.0",
  "scope": "required",
  "author": "Tilen Majerle; Adam Dunkels / Swedish Institute of Computer Science (bundled Protothreads)",
  "purl": "pkg:generic/esp8266lib@2.3.0",
  "description": "Esp8266Lib is a vendored embedded C ESP8266 AT command parser and support library, including Tilen Majerle ESP8266/buffer sources and bundled Protothreads headers.",
  "licenses": [
    {
      "expression": "MIT AND BSD-3-Clause"
    }
  ],
  "properties": [
    { "name": "bsp:file-path", "value": "SampleCode/SecureApplication/SecureOTADemo/Esp8266Lib" },
    { "name": "src_path", "value": "SampleCode/SecureApplication/SecureOTADemo/Esp8266Lib" },
    { "name": "integration", "value": "vendored_source" },
    { "name": "bsp:component-origin", "value": "third-party" },
    { "name": "bsp:component-source", "value": "Tilen Majerle ESP8266 AT commands parser; bundled Protothreads by Adam Dunkels / SICS" },
    { "name": "bsp:evidence-file", "value": "Document/SBOM/components/sca_esp8266lib.json" },
    { "name": "bsp:evidence-path", "value": "SampleCode/SecureApplication/SecureOTADemo/Esp8266Lib" },
    { "name": "bsp:version-evidence", "value": "SampleCode/SecureApplication/SecureOTADemo/Esp8266Lib/esp8266.h (\\version v2.3.0)" },
    { "name": "bsp:license-note", "value": "esp8266_ll_template.h contains conflicting Doxygen license metadata: \\license GNU GPL v3, while the embedded full license text is MIT." }
  ]
}
```

## 8) File Hashes

- `SampleCode/SecureApplication/SecureOTADemo/Esp8266Lib/buffer.c`
  - SHA-256: `6e133d48a468162400888d9bde7e09d9e1f7a53ce340d4af066298955c8acef5`
- `SampleCode/SecureApplication/SecureOTADemo/Esp8266Lib/buffer.h`
  - SHA-256: `f5bcbaabd4274d316f9cf9e8dd543f7aba619dad62501bba898ebf7644ae0a28`
- `SampleCode/SecureApplication/SecureOTADemo/Esp8266Lib/esp8266.c`
  - SHA-256: `11dba0985ed6ac678adb1bdba15ee86ddea268a2d74a556643dab0351e6b5702`
- `SampleCode/SecureApplication/SecureOTADemo/Esp8266Lib/esp8266.h`
  - SHA-256: `ca3d07da6104476cccec0385808de2d706698c75eb00ccafd63ca7af65d38f8e`
- `SampleCode/SecureApplication/SecureOTADemo/Esp8266Lib/esp8266_config_template.h`
  - SHA-256: `85357e4bdc9398104dfc5d8e379bb4438cf777a2a39c4526b98de67fdda870ec`
- `SampleCode/SecureApplication/SecureOTADemo/Esp8266Lib/esp8266_ll_template.c`
  - SHA-256: `55e6b9c66b4c15e7e603ca01a5f15025ecec6ba8a06926e7f5155a34c49fdd39`
- `SampleCode/SecureApplication/SecureOTADemo/Esp8266Lib/esp8266_ll_template.h`
  - SHA-256: `1f172faf0c59310d73091eed631c73be325b3509a9903dd6a978074630c47e83`
- `SampleCode/SecureApplication/SecureOTADemo/Esp8266Lib/pt/lc-addrlabels.h`
  - SHA-256: `46b511e142bedcf935d3a43b1d79e73a822cb1da46df0eb94217dcd1ddf57d4a`
- `SampleCode/SecureApplication/SecureOTADemo/Esp8266Lib/pt/lc-switch.h`
  - SHA-256: `9e52f82a7e6c0137d787ea8caad20a6aa49e7329f83042b4b3b800d208649d64`
- `SampleCode/SecureApplication/SecureOTADemo/Esp8266Lib/pt/lc.h`
  - SHA-256: `2c6d0a32c14721fb6b357717f81658267842cf0be94c5c4853840cd55103a0ee`
- `SampleCode/SecureApplication/SecureOTADemo/Esp8266Lib/pt/pt-sem.h`
  - SHA-256: `e8b3148cf45c2da0b938ae0ce783ee02ee04724a5202f0fd0da32327b631cb6b`
- `SampleCode/SecureApplication/SecureOTADemo/Esp8266Lib/pt/pt.h`
  - SHA-256: `0645bfeca462492f139611fabe83f47bcee3337ee56db4f43886ad8e2665d2d4`

## 9) Compliance Notes

- Keep the original upstream copyright/license headers in all source files.
- No standalone license file was found under `SampleCode/SecureApplication/SecureOTADemo/Esp8266Lib`; license evidence is taken from source headers.
- Review the conflicting `\license GNU GPL v3` Doxygen metadata in `esp8266_ll_template.h` before distribution if your product compliance process treats short metadata tags as license evidence.
- If producing a finer-grained SBOM, represent the bundled `pt/` Protothreads headers as a separate `Protothreads` component with `BSD-3-Clause` and declare it as a dependency of `Esp8266Lib`.
