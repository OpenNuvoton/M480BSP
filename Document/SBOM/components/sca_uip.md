# uIP Third-Party Component Description (for SCA / SBOM)

This document provides SBOM-ready metadata for the vendored uIP component under `ThirdParty/uip-0.9`.

## 1) Component Identity

- Component name (`name`): `uIP`
- Component type (`type`): `library`
- Supplier / project: `Adam Dunkels`
- Version: `0.9`
- License: `BSD-3-Clause` (SPDX)
- Evidence path: `ThirdParty/uip-0.9`

## 2) Evidence for Version and License

Primary evidence in this repository:

- `ThirdParty/uip-0.9` directory name
  - Identifies vendored version as `0.9`
- `ThirdParty/uip-0.9/apps/httpd/makefsdata`
  - Emits HTTP server header `uIP/0.9`
- `ThirdParty/uip-0.9/uip/uip.h`
  - Header identifies the component as the uIP TCP/IP stack
  - Header contains BSD-style redistribution terms
  - Copyright shows `2001-2003, Adam Dunkels`
- `ThirdParty/uip-0.9/uip/uip.c`
  - Header contains BSD-style redistribution terms

## 3) License Handling Guidance

For CycloneDX output, use the SPDX license ID:

- `licenses[0].license.id = BSD-3-Clause`

Also preserve upstream license headers in vendored source files.

## 4) Suggested CycloneDX Field Mapping

Recommended component fields:

- `type`: `library`
- `name`: `uIP`
- `version`: `0.9`
- `scope`: `required`
- `author`: `Adam Dunkels`
- `description`: `uIP small TCP/IP stack vendored in ThirdParty/uip-0.9, including uIP core, ARP, SLIP, example applications, documentation, and Unix example code.`
- `properties`:
  - `src_path = ThirdParty/uip-0.9`
  - `integration = vendored_source`
  - `uip_version = 0.9`

## 5) Suggested BOM-Ref and purl

- `bom-ref`: `pkg:generic/uip@0.9?source=vendored&path=ThirdParty/uip-0.9`
- `purl`: `pkg:generic/uip@0.9`

## 6) Compliance Notes

- Keep original BSD license and copyright notices.
- Some application examples include code derived from or mentioning lwIP; keep file-level notices if distributing those examples.
