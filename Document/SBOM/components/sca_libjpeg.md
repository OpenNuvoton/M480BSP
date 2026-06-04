# libjpeg Third-Party Component Description (for SCA / SBOM)

This document provides SBOM-ready metadata for the vendored Independent JPEG Group JPEG software under `ThirdParty/libjpeg`.

## 1) Component Identity

- Component name (`name`): `libjpeg`
- Component type (`type`): `library`
- Supplier / project: `Independent JPEG Group`
- Version: `9b`
- License: `IJG` (SPDX)
- Evidence path: `ThirdParty/libjpeg`

## 2) Evidence for Version and License

Primary evidence in this repository:

- `ThirdParty/libjpeg/README`
  - Identifies the package as release `9b` dated `10-Jan-2016`
  - Contains the `LEGAL ISSUES` section for redistribution and attribution requirements
- `ThirdParty/libjpeg/jversion.h`
  - Defines `JVERSION "9b  10-Jan-2016"`
  - Defines `JCOPYRIGHT "Copyright (C) 2016, Thomas G. Lane, Guido Vollbeding"`

## 3) License Handling Guidance

For CycloneDX output, use the SPDX license ID:

- `licenses[0].license.id = IJG`

Also preserve the upstream README/legal text and copyright headers in vendored source files.

## 4) Suggested CycloneDX Field Mapping

Recommended component fields:

- `type`: `library`
- `name`: `libjpeg`
- `version`: `9b`
- `scope`: `required`
- `author`: `Independent JPEG Group`
- `description`: `Independent JPEG Group JPEG software vendored in ThirdParty/libjpeg for JPEG encoding, decoding, and transcoding.`
- `properties`:
  - `src_path = ThirdParty/libjpeg`
  - `integration = vendored_source`
  - `libjpeg_version = 9b`

## 5) Suggested BOM-Ref and purl

- `bom-ref`: `pkg:generic/libjpeg@9b?source=vendored&path=ThirdParty/libjpeg`
- `purl`: `pkg:generic/libjpeg@9b`

## 6) Compliance Notes

- Keep the original IJG README and copyright notices.
- Product documentation may need an acknowledgement for use of IJG code, per the README legal terms.
