# lwIP Third-Party Component Description (for SCA / SBOM)

This document provides SBOM-ready metadata for the vendored lwIP component under `ThirdParty/lwIP`.

## 1) Component Identity

- Component name (`name`): `lwIP`
- Component type (`type`): `library`
- Supplier / project: `Swedish Institute of Computer Science / lwIP project`
- Version: `2.0.3`
- License: `BSD-3-Clause` (SPDX)
- Evidence path: `ThirdParty/lwIP`

## 2) Evidence for Version and License

Primary evidence in this repository:

- `ThirdParty/lwIP/src/include/lwip/init.h`
  - Defines `LWIP_VERSION_MAJOR 2`
  - Defines `LWIP_VERSION_MINOR 0`
  - Defines `LWIP_VERSION_REVISION 3`
  - Defines release version string composition for `2.0.3`
  - Header contains BSD-style redistribution terms
- `ThirdParty/lwIP/COPYING`
  - Contains the BSD-style license text
- `ThirdParty/lwIP/README`
  - States lwIP is available under a BSD license

## 3) License Handling Guidance

For CycloneDX output, use the SPDX license ID:

- `licenses[0].license.id = BSD-3-Clause`

Also preserve upstream license headers and `COPYING`.

## 4) Suggested CycloneDX Field Mapping

Recommended component fields:

- `type`: `library`
- `name`: `lwIP`
- `version`: `2.0.3`
- `scope`: `required`
- `author`: `Swedish Institute of Computer Science / lwIP project`
- `description`: `lwIP TCP/IP stack vendored in ThirdParty/lwIP, including core stack, APIs, netif code, apps, documentation, and tests.`
- `properties`:
  - `src_path = ThirdParty/lwIP`
  - `integration = vendored_source`
  - `lwip_version = 2.0.3`

## 5) Suggested BOM-Ref and purl

- `bom-ref`: `pkg:generic/lwip@2.0.3?source=vendored&path=ThirdParty/lwIP`
- `purl`: `pkg:generic/lwip@2.0.3`

## 6) Compliance Notes

- Keep original BSD license and copyright notices.
- lwIP includes optional apps and PPP-related code; product-level SBOMs may split optional subcomponents if only part of the tree is distributed.
