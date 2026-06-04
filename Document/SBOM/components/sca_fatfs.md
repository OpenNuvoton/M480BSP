# FatFs Third-Party Component Description (for SCA / SBOM)

This document provides component metadata for the **FatFs file system library** source code under `ThirdParty/FatFs`, so it can be used directly in downstream SBOM generation (CycloneDX format).

## 1) Component Identity

- Component name (`name`): `FatFs`
- Component type (`type`): `library`
- Supplier / author: `ChaN`
- Version: `R0.13a` (identified from source headers and revision ID)
- Copyright:
  - `Copyright (C) 2017, ChaN, all right reserved.`
- Evidence path: `ThirdParty/FatFs`
- Key implementation files:
  - `ThirdParty/FatFs/source/ff.c`
  - `ThirdParty/FatFs/source/ff.h`
  - `ThirdParty/FatFs/source/ffconf.h`
  - `ThirdParty/FatFs/source/ffunicode.c`
  - `ThirdParty/FatFs/source/ffsystem.c`
  - `ThirdParty/FatFs/source/diskio.h`
  - `ThirdParty/FatFs/source/diskio.c`

## 2) License Information

The license text in FatFs source files is an author-declared BSD-like license text (not an official SPDX short identifier). Core conditions are:

1. Redistributions of source code must retain the copyright notice, conditions, and disclaimer.
2. The software is provided "AS IS" without warranty, and the author/contributors are not liable for damages.

> Recommendation: in CycloneDX, keep this as a descriptive `license.name` (and optionally full license text) instead of force-mapping to an SPDX ID.

Recommended fields:

- `licenses[0].license.name`: `FatFs license (BSD-like, as declared by ChaN in source header)`
- `licenses[0].license.text.contentType`: `text/plain`
- `licenses[0].license.text.content`: (paste the full header license text from `ff.c` / `ff.h`)

## 3) Functional / Technical Scope

FatFs is a FAT file system module for embedded systems with the following characteristics:

- Implemented in ANSI C (C89).
- Separated from the low-level storage I/O layer (via `disk_*` interface).
- Supports FAT/exFAT depending on configuration options.
- Feature set can be tailored via `ffconf.h` (read-only mode, multi-volume, LFN, code pages, etc.).

## 4) Suggested CycloneDX Field Mapping

Suggested values (adjust as needed for your SBOM toolchain):

- `type`: `library`
- `name`: `FatFs`
- `version`: `R0.13a`
- `scope`: `required`
- `author`: `ChaN`
- `description`: `FatFs - Generic FAT file system module for embedded systems (ANSI C/C89), integrated as source code under ThirdParty/FatFs.`
- `licenses`: see Section 2
- `properties` (recommended custom properties):
  - `src_path = ThirdParty/FatFs`
  - `fatfs_revision_id = 89352`
  - `integration = vendored_source`

## 5) Suggested BOM-Ref and purl

FatFs is vendored source code and not a typical package-manager artifact (e.g., npm/pypi/maven). Suggested values:

- `bom-ref`: `pkg:generic/fatfs@R0.13a?source=vendored&path=ThirdParty/FatFs`
- `purl`: `pkg:generic/fatfs@R0.13a`

> If your internal policy requires source traceability, you can add `externalReferences` (for example, project website), but use your actual import evidence as the primary reference.

## 6) CycloneDX JSON Component Example

```json
{
  "type": "library",
  "bom-ref": "pkg:generic/fatfs@R0.13a?source=vendored&path=ThirdParty/FatFs",
  "name": "FatFs",
  "version": "R0.13a",
  "scope": "required",
  "author": "ChaN",
  "purl": "pkg:generic/fatfs@R0.13a",
  "description": "FatFs - Generic FAT file system module for embedded systems (ANSI C/C89), integrated as vendored source code.",
  "licenses": [
    {
      "license": {
        "name": "FatFs license (BSD-like, as declared by ChaN in source header)"
      }
    }
  ],
  "properties": [
    { "name": "src_path", "value": "ThirdParty/FatFs" },
    { "name": "fatfs_revision_id", "value": "89352" },
    { "name": "integration", "value": "vendored_source" }
  ]
}
```

## 7) Version Evidence (for Audit)

- `ff.h` header note: `FatFs ... module R0.13a`
- `ff.c` header note: `FatFs ... Module R0.13a`
- `ffunicode.c` header note: `Unicode handling functions for FatFs R0.13a`
- Revision ID in `ff.h` / `ffconf.h` / `ff.c` / `ffunicode.c`: `89352`

## 8) Compliance Notes

- Keep the original license/disclaimer headers in source files.
- If LFN/exFAT features are enabled, perform product-level patent/license review for target markets (this is a product compliance consideration, not part of the FatFs source license terms themselves).
