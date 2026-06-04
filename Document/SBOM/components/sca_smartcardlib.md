# SmartcardLib Component Description (for SCA / SBOM)

This document provides component metadata for the **SmartcardLib** pre-built library under `Library/SmartcardLib`, so it can be used directly in downstream SBOM generation (CycloneDX format).

## 1) Component Identity

- Component name (`name`): `SmartcardLib`
- Component type (`type`): `library`
- Supplier / author: `Nuvoton Technology Corporation`
- Version: `V3.00`
- License: `Nuvoton Proprietary`
- Evidence path: `Library/SmartcardLib`
- Component files:
  - `Library/SmartcardLib/libsmartcard.a`
  - `Library/SmartcardLib/SmartCardLib_Keil.lib`
  - `Library/SmartcardLib/SmartCardLib_IAR.a`
  - `Library/SmartcardLib/Include/sclib.h`

## 2) Evidence for Version and License

Primary evidence in this repository:

- `Library/SmartcardLib/Include/sclib.h`
  - Header version shows `@version V3.00`
  - Header brief shows `Smartcard library header File`
  - Header copyright notice shows `Copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.`
  - Header SPDX tag shows `SPDX-License-Identifier: Apache-2.0`
  - SHA-256: `72ad31e5366dd4348dc9539e8d28b80c6c8ad03c60869b75044390c483c10c77`
- `Library/SmartcardLib/LICENSE.md`
  - Nuvoton Software License Agreement
  - Copyright notice for Nuvoton Technology Corporation
  - SHA-256: `ee61ebfcdb1c0f17b01f83d7e928711840b62cd58172276cb1a873ea2a13664d`
- `Library/SmartcardLib/libsmartcard.a`
  - Archive members: `sclib_api.o`, `sclib_t0protocol.o`, `sclib_t1protocol.o`, `sclib_util.o`
  - SHA-256: `c426c4b9402edb3a8147bcb8ce9f7dbc48a22707eefac4be8d3ce734ec9232e3`
- `Library/SmartcardLib/SmartCardLib_Keil.lib`
  - Archive members: `sclib_util.o`, `sclib_api.o`, `sclib_t0protocol.o`, `sclib_t1protocol.o`
  - SHA-256: `4c0f8f28c5076c96f71f065c5fdc52dbde86bd63712a3276c817de32f3d41e82`
- `Library/SmartcardLib/SmartCardLib_IAR.a`
  - Archive members: `sclib_api.o`, `sclib_t0protocol.o`, `sclib_t1protocol.o`, `sclib_util.o`
  - SHA-256: `aa1bcd76af1d1207b8aa1492623392f3ee2127895207a039254e6263761ba34d`

## 3) License Handling Guidance

`SmartcardLib` is a first-party pre-built binary library distributed with the Nuvoton software license in `Library/SmartcardLib/LICENSE.md`.

For CycloneDX output, keep the component license as a descriptive license name:

- `licenses[0].license.name`: `Nuvoton Proprietary`

Note: `Library/SmartcardLib/Include/sclib.h` contains an `SPDX-License-Identifier: Apache-2.0` tag. If your SBOM policy tracks source/header files separately from binary archives, record the header file license as `Apache-2.0` while keeping the pre-built library component under the Nuvoton software license.

## 4) Functional / Technical Scope

SmartcardLib provides SCLIB APIs for supported NuMicro MCUs, including:

- Smartcard activation, cold reset, warm reset, and deactivation.
- Card information retrieval, including ATR and selected protocol.
- T=0 and T=1 smartcard transmission support.
- Smartcard interrupt event handling helpers for card detect, timeout, Tx/Rx, and error events.

## 5) Suggested CycloneDX Field Mapping

Recommended component fields:

- `type`: `library`
- `bom-ref`: `pkg:generic/smartcardlib@V3.00?source=vendored&path=Library/SmartcardLib`
- `name`: `SmartcardLib`
- `version`: `V3.00`
- `scope`: `required`
- `author`: `Nuvoton Technology Corporation`
- `purl`: `pkg:generic/smartcardlib@V3.00`
- `description`: `SmartcardLib is a first-party pre-built smartcard protocol library for supported NuMicro MCUs. The library provides ISO-7816 smartcard activation, reset, card information, and T=0/T=1 transmission APIs through the SCLIB interface.`
- `licenses[0].license.name`: `Nuvoton Proprietary`
- `properties` (recommended custom properties):
  - `bsp:file-path = Library/SmartcardLib`
  - `bsp:binary-file = Library/SmartcardLib/libsmartcard.a`
  - `bsp:binary-file = Library/SmartcardLib/SmartCardLib_Keil.lib`
  - `bsp:binary-file = Library/SmartcardLib/SmartCardLib_IAR.a`
  - `bsp:header-file = Library/SmartcardLib/Include/sclib.h`
  - `integration = vendored_binary`
  - `bsp:component-origin = first-party`
  - `bsp:component-source = Nuvoton Technology Corporation`
  - `bsp:license-file = Library/SmartcardLib/LICENSE.md`
  - `bsp:evidence-file = Document/SBOM/components/sca_smartcardlib.json`
  - `bsp:evidence-path = Library/SmartcardLib`
  - `bsp:version-evidence = Library/SmartcardLib/Include/sclib.h (@version V3.00)`

## 6) Suggested BOM-Ref and purl

Suggested values:

- `bom-ref`: `pkg:generic/smartcardlib@V3.00?source=vendored&path=Library/SmartcardLib`
- `purl`: `pkg:generic/smartcardlib@V3.00`

## 7) CycloneDX JSON Component Example

```json
{
  "type": "library",
  "bom-ref": "pkg:generic/smartcardlib@V3.00?source=vendored&path=Library/SmartcardLib",
  "name": "SmartcardLib",
  "version": "V3.00",
  "scope": "required",
  "author": "Nuvoton Technology Corporation",
  "purl": "pkg:generic/smartcardlib@V3.00",
  "description": "SmartcardLib is a first-party pre-built smartcard protocol library for supported NuMicro MCUs. The library provides ISO-7816 smartcard activation, reset, card information, and T=0/T=1 transmission APIs through the SCLIB interface.",
  "licenses": [
    {
      "license": {
        "name": "Nuvoton Proprietary"
      }
    }
  ],
  "properties": [
    { "name": "bsp:file-path", "value": "Library/SmartcardLib" },
    { "name": "bsp:binary-file", "value": "Library/SmartcardLib/libsmartcard.a" },
    { "name": "bsp:binary-file", "value": "Library/SmartcardLib/SmartCardLib_Keil.lib" },
    { "name": "bsp:binary-file", "value": "Library/SmartcardLib/SmartCardLib_IAR.a" },
    { "name": "bsp:header-file", "value": "Library/SmartcardLib/Include/sclib.h" },
    { "name": "integration", "value": "vendored_binary" },
    { "name": "bsp:component-origin", "value": "first-party" },
    { "name": "bsp:component-source", "value": "Nuvoton Technology Corporation" },
    { "name": "bsp:license-file", "value": "Library/SmartcardLib/LICENSE.md" },
    { "name": "bsp:evidence-file", "value": "Document/SBOM/components/sca_smartcardlib.json" },
    { "name": "bsp:evidence-path", "value": "Library/SmartcardLib" },
    { "name": "bsp:version-evidence", "value": "Library/SmartcardLib/Include/sclib.h (@version V3.00)" },
    { "name": "bsp:sha256:Library/SmartcardLib/libsmartcard.a", "value": "c426c4b9402edb3a8147bcb8ce9f7dbc48a22707eefac4be8d3ce734ec9232e3" },
    { "name": "bsp:sha256:Library/SmartcardLib/SmartCardLib_Keil.lib", "value": "4c0f8f28c5076c96f71f065c5fdc52dbde86bd63712a3276c817de32f3d41e82" },
    { "name": "bsp:sha256:Library/SmartcardLib/SmartCardLib_IAR.a", "value": "aa1bcd76af1d1207b8aa1492623392f3ee2127895207a039254e6263761ba34d" },
    { "name": "bsp:sha256:Library/SmartcardLib/Include/sclib.h", "value": "72ad31e5366dd4348dc9539e8d28b80c6c8ad03c60869b75044390c483c10c77" },
    { "name": "bsp:sha256:Library/SmartcardLib/LICENSE.md", "value": "ee61ebfcdb1c0f17b01f83d7e928711840b62cd58172276cb1a873ea2a13664d" }
  ]
}
```

## 8) Compliance Notes

- Keep `Library/SmartcardLib/LICENSE.md` with the distributed pre-built libraries.
- Treat the archive files as first-party vendored binary components in SBOM output.
- Preserve the SPDX and copyright header in `Library/SmartcardLib/Include/sclib.h`.
