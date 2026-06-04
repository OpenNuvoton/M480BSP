# TouchView Component Description (for SCA / SBOM)

This document provides component metadata for the **TouchView** GUI tool under `Tool/TK`, so it can be used directly in downstream SBOM generation (CycloneDX format).

## 1) Component Identity

- Component name (`name`): `TouchView`
- Component type (`type`): `application`
- Supplier / author: `Nuvoton Technology Corporation`
- Version: `1.0.0.1`
- License: `Nuvoton Proprietary`
- Evidence path: `Tool/TK`
- Component file: `Tool/TK/TouchView.exe`

## 2) Evidence for Version and License

Primary evidence in this repository:

- `Tool/TK/TouchView.exe`
  - PE version resource shows `FileVersion 1.0.0.1`
  - PE version resource shows `ProductVersion 1.0.0.1`
  - PE version resource shows `ProductName TouchView`
  - Embedded product strings include `Nuvoton-TouchView`
  - SHA-256: `38d449b6ab80a6c6391e297f042b619e5767a753d4ad62d2e4c4386ac7daa6fd`
- `Tool/TK/LICENSE.md`
  - Nuvoton Software License Agreement
  - Copyright notice for Nuvoton Technology Corporation

## 3) License Handling Guidance

`TouchView.exe` is a first-party pre-built binary distributed under the Nuvoton software license in `Tool/TK/LICENSE.md`.

For CycloneDX output, keep the license as a descriptive license name:

- `licenses[0].license.name`: `Nuvoton Proprietary`

## 4) Suggested CycloneDX Field Mapping

Recommended component fields:

- `type`: `application`
- `bom-ref`: `TouchView.exe-38d449b6`
- `name`: `TouchView`
- `version`: `1.0.0.1`
- `scope`: `required`
- `author`: `Nuvoton Technology Corporation`
- `purl`: `pkg:generic/touchview@1.0.0.1`
- `description`: `TouchView is a GUI tool for developing and tuning touch key functions on supported NuMicro MCUs. The tool is included in the corresponding BSP as a pre-built executable.`
- `licenses[0].license.name`: `Nuvoton Proprietary`
- `hashes[0].alg`: `SHA-256`
- `hashes[0].content`: `38d449b6ab80a6c6391e297f042b619e5767a753d4ad62d2e4c4386ac7daa6fd`
- `properties` (recommended custom properties):
  - `bsp:file-path = Tool/TK/TouchView.exe`
  - `integration = vendored_binary`
  - `bsp:component-origin = first-party`
  - `bsp:component-source = Nuvoton Technology Corporation`
  - `bsp:evidence-file = Document/SBOM/components/sca_tk.json`
  - `bsp:evidence-path = Tool/TK`
  - `bsp:version-evidence = Tool/TK/TouchView.exe (PE version resource: FileVersion 1.0.0.1)`

## 5) Suggested BOM-Ref and purl

Suggested values from `Document/SBOM/components/sca_tk.json`:

- `bom-ref`: `TouchView.exe-38d449b6`
- `purl`: `pkg:generic/touchview@1.0.0.1`

## 6) CycloneDX JSON Component Example

```json
{
  "type": "application",
  "bom-ref": "TouchView.exe-38d449b6",
  "name": "TouchView",
  "version": "1.0.0.1",
  "scope": "required",
  "author": "Nuvoton Technology Corporation",
  "purl": "pkg:generic/touchview@1.0.0.1",
  "description": "TouchView is a GUI tool for developing and tuning touch key functions on supported NuMicro MCUs. The tool is included in the corresponding BSP as a pre-built executable.",
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
      "content": "38d449b6ab80a6c6391e297f042b619e5767a753d4ad62d2e4c4386ac7daa6fd"
    }
  ],
  "properties": [
    { "name": "bsp:file-path", "value": "Tool/TK/TouchView.exe" },
    { "name": "integration", "value": "vendored_binary" },
    { "name": "bsp:component-origin", "value": "first-party" },
    { "name": "bsp:component-source", "value": "Nuvoton Technology Corporation" },
    { "name": "bsp:evidence-file", "value": "Document/SBOM/components/sca_tk.json" },
    { "name": "bsp:evidence-path", "value": "Tool/TK" },
    { "name": "bsp:version-evidence", "value": "Tool/TK/TouchView.exe (PE version resource: FileVersion 1.0.0.1)" }
  ]
}
```

## 7) Compliance Notes

- Keep `Tool/TK/LICENSE.md` with the distributed binary.
- Treat `TouchView.exe` as a first-party vendored binary component in SBOM output.
