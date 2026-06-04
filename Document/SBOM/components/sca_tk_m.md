# TouchView_MP Component Description (for SCA / SBOM)

This document provides component metadata for the **TouchView_MP** GUI mass production tool under `Tool/TK`, so it can be used directly in downstream SBOM generation (CycloneDX format).

## 1) Component Identity

- Component name (`name`): `TouchView_MP`
- Component type (`type`): `application`
- Supplier / author: `Nuvoton Technology Corporation`
- Version: `1.0.0.1`
- License: `Nuvoton Proprietary`
- Evidence path: `Tool/TK`
- Component file: `Tool/TK/TouchView_MP.exe`

## 2) Evidence for Version and License

Primary evidence in this repository:

- `Tool/TK/TouchView_MP.exe`
  - PE version resource shows `FileVersion 1.0.0.1`
  - PE version resource shows `ProductVersion 1.0.0.1`
  - Embedded product strings include `TouchView - Mass Production`
  - SHA-256: `798717b616ae59f81bb7cb4428a653f424838ac305bdfccc75623e69cce53cac`
- `Tool/TK/LICENSE.md`
  - Nuvoton Software License Agreement
  - Copyright notice for Nuvoton Technology Corporation

## 3) License Handling Guidance

`TouchView_MP.exe` is a first-party pre-built binary distributed under the Nuvoton software license in `Tool/TK/LICENSE.md`.

For CycloneDX output, keep the license as a descriptive license name:

- `licenses[0].license.name`: `Nuvoton Proprietary`

## 4) Suggested CycloneDX Field Mapping

Recommended component fields:

- `type`: `application`
- `name`: `TouchView_MP`
- `version`: `1.0.0.1`
- `scope`: `required`
- `author`: `Nuvoton Technology Corporation`
- `description`: `TouchView_MP is a GUI mass production tool for touch key functions on supported NuMicro MCUs. The tool is included in the corresponding BSP as a pre-built executable.`
- `licenses[0].license.name`: `Nuvoton Proprietary`
- `hashes[0].alg`: `SHA-256`
- `hashes[0].content`: `798717b616ae59f81bb7cb4428a653f424838ac305bdfccc75623e69cce53cac`
- `properties` (recommended custom properties):
  - `bsp:file-path = Tool/TK/TouchView_MP.exe`
  - `integration = vendored_binary`
  - `bsp:component-origin = first-party`
  - `bsp:component-source = Nuvoton Technology Corporation`
  - `bsp:license-file = Tool/TK/LICENSE.md`
  - `bsp:evidence-file = Document/SBOM/components/sca_tk_m.json`
  - `bsp:evidence-path = Tool/TK`
  - `bsp:version-evidence = Tool/TK/TouchView_MP.exe (PE version resource: FileVersion 1.0.0.1; ProductVersion 1.0.0.1)`

## 5) Suggested BOM-Ref and purl

Suggested values:

- `bom-ref`: `pkg:generic/touchview-mp@1.0.0.1?source=vendored&path=Tool/TK/TouchView_MP.exe`
- `purl`: `pkg:generic/touchview-mp@1.0.0.1`

## 6) CycloneDX JSON Component Example

```json
{
  "type": "application",
  "bom-ref": "pkg:generic/touchview-mp@1.0.0.1?source=vendored&path=Tool/TK/TouchView_MP.exe",
  "name": "TouchView_MP",
  "version": "1.0.0.1",
  "scope": "required",
  "author": "Nuvoton Technology Corporation",
  "purl": "pkg:generic/touchview-mp@1.0.0.1",
  "description": "TouchView_MP is a GUI mass production tool for touch key functions on supported NuMicro MCUs. The tool is included in the corresponding BSP as a pre-built executable.",
  "licenses": [
    {
      "license": {
        "name": "Nuvoton Proprietary"
      }
    }
  ],
  "hashes": [
    {
      "alg": "SHA-256",
      "content": "798717b616ae59f81bb7cb4428a653f424838ac305bdfccc75623e69cce53cac"
    }
  ],
  "properties": [
    { "name": "bsp:file-path", "value": "Tool/TK/TouchView_MP.exe" },
    { "name": "integration", "value": "vendored_binary" },
    { "name": "bsp:component-origin", "value": "first-party" },
    { "name": "bsp:component-source", "value": "Nuvoton Technology Corporation" },
    { "name": "bsp:license-file", "value": "Tool/TK/LICENSE.md" },
    { "name": "bsp:evidence-file", "value": "Document/SBOM/components/sca_tk_m.json" },
    { "name": "bsp:evidence-path", "value": "Tool/TK" },
    { "name": "bsp:version-evidence", "value": "Tool/TK/TouchView_MP.exe (PE version resource: FileVersion 1.0.0.1; ProductVersion 1.0.0.1)" }
  ]
}
```

## 7) Compliance Notes

- Keep `Tool/TK/LICENSE.md` with the distributed binary.
- Treat `TouchView_MP.exe` as a first-party vendored binary component in SBOM output.
