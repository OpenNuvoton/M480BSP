# LibMAD Third-Party Component Description (for SCA / SBOM)

This document provides SBOM-ready metadata for the vendored libmad component under `ThirdParty/LibMAD`.

## 1) Component Identity

- Component name (`name`): `LibMAD`
- Component type (`type`): `library`
- Supplier / project: `Underbit Technologies, Inc.`
- Version: `0.15.1-beta`
- License: `GPL-2.0-or-later` (SPDX)
- Evidence path: `ThirdParty/LibMAD`

## 2) Evidence for Version and License

Primary evidence in this repository:

- `ThirdParty/LibMAD/inc/version.h`
  - Defines `MAD_VERSION_MAJOR 0`, `MAD_VERSION_MINOR 15`, `MAD_VERSION_PATCH 1`, and `MAD_VERSION_EXTRA " (beta)"`
  - Header states GPL version 2 or later
  - Copyright shows `2000-2004 Underbit Technologies, Inc.`
- `ThirdParty/LibMAD/inc/global.h`
  - Header states GPL version 2 or later

## 3) License Handling Guidance

For CycloneDX output, use the SPDX license ID:

- `licenses[0].license.id = GPL-2.0-or-later`

This is a copyleft license. Product release should confirm whether the way this library is linked and distributed is acceptable for the target product.

## 4) Suggested CycloneDX Field Mapping

Recommended component fields:

- `type`: `library`
- `name`: `LibMAD`
- `version`: `0.15.1-beta`
- `scope`: `required`
- `author`: `Underbit Technologies, Inc.`
- `description`: `libmad MPEG audio decoder library vendored in ThirdParty/LibMAD.`
- `properties`:
  - `src_path = ThirdParty/LibMAD`
  - `integration = vendored_source`
  - `libmad_version = 0.15.1-beta`

## 5) Suggested BOM-Ref and purl

- `bom-ref`: `pkg:generic/libmad@0.15.1-beta?source=vendored&path=ThirdParty/LibMAD`
- `purl`: `pkg:generic/libmad@0.15.1-beta`

## 6) Compliance Notes

- Keep original GPL and copyright headers.
- Confirm source-offer, notice, and linking obligations before product distribution.
