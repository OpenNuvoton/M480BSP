# mbed TLS Third-Party Component Description (for SCA / SBOM)

This document provides SBOM-ready metadata for the vendored mbed TLS component under `ThirdParty/mbedtls-2.13.0`.

## 1) Component Identity

- Component name (`name`): `mbed TLS`
- Component type (`type`): `library`
- Supplier / project: `ARM Limited`
- Version: `2.13.0`
- License: `Apache-2.0` (SPDX)
- Evidence path: `ThirdParty/mbedtls-2.13.0`

## 2) Evidence for Version and License

Primary evidence in this repository:

- `ThirdParty/mbedtls-2.13.0/include/mbedtls/version.h`
  - Defines `MBEDTLS_VERSION_MAJOR 2`
  - Defines `MBEDTLS_VERSION_MINOR 13`
  - Defines `MBEDTLS_VERSION_PATCH 0`
  - Defines `MBEDTLS_VERSION_STRING "2.13.0"`
  - Header includes `SPDX-License-Identifier: Apache-2.0`
- `ThirdParty/mbedtls-2.13.0/library/aes.c`
  - Header includes `SPDX-License-Identifier: Apache-2.0`
  - Header identifies the file as part of mbed TLS

## 3) License Handling Guidance

For CycloneDX output, use the SPDX license ID:

- `licenses[0].license.id = Apache-2.0`

Also preserve upstream license headers in vendored source files.

## 4) Suggested CycloneDX Field Mapping

Recommended component fields:

- `type`: `library`
- `name`: `mbed TLS`
- `version`: `2.13.0`
- `scope`: `required`
- `author`: `ARM Limited`
- `description`: `mbed TLS cryptographic and TLS library vendored in ThirdParty/mbedtls-2.13.0, including public headers and library source files.`
- `properties`:
  - `src_path = ThirdParty/mbedtls-2.13.0`
  - `integration = vendored_source`
  - `mbedtls_version = 2.13.0`

## 5) Suggested BOM-Ref and purl

- `bom-ref`: `pkg:generic/mbedtls@2.13.0?source=vendored&path=ThirdParty/mbedtls-2.13.0`
- `purl`: `pkg:generic/mbedtls@2.13.0`

## 6) Compliance Notes

- Keep original Apache-2.0 license headers.
- This vendored tree contains Nuvoton-specific conditional code in some source files; product SBOM should still identify the upstream base as mbed TLS 2.13.0.
