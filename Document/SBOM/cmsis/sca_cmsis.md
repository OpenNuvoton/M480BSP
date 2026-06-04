# CMSIS Third-Party Component Description (for SCA / SBOM)

This document provides SBOM-ready metadata for the vendored Arm CMSIS component under `Library/CMSIS`.

## 1) Component Identity

- Component name (`name`): `CMSIS`
- Component type (`type`): `library`
- Supplier / project: `Arm Limited`
- Version: `5.0.2`
- License: `Apache-2.0` (SPDX)
- Evidence path: `Library/CMSIS`
- Included top-level areas:
  - `Library/CMSIS/Core`
  - `Library/CMSIS/Core_A`
  - `Library/CMSIS/DAP`
  - `Library/CMSIS/DSP_Lib`
  - `Library/CMSIS/Documentation`
  - `Library/CMSIS/Driver`
  - `Library/CMSIS/Include`
  - `Library/CMSIS/Lib`
  - `Library/CMSIS/Pack`
  - `Library/CMSIS/RTOS`
  - `Library/CMSIS/RTOS2`
  - `Library/CMSIS/SVD`
  - `Library/CMSIS/Utilities`

## 2) Evidence for Version and License

Primary evidence in this repository:

- `Library/CMSIS/Include/cmsis_version.h`
  - Header includes `SPDX-License-Identifier: Apache-2.0`
  - Header shows `@version V5.0.2`
  - `__CM_CMSIS_VERSION_MAIN` is `5U`
  - `__CM_CMSIS_VERSION_SUB` is `0U`
- `Library/CMSIS/Documentation/Core/html/index.html`
  - Documentation shows CMSIS-Core `Version 5.0.2`
- `Library/CMSIS/Core_A/Include/core_ca.h`
  - Header includes `SPDX-License-Identifier: Apache-2.0`
  - Header shows `@version V1.00`
  - `__CA_CMSIS_VERSION_MAIN` is `1U`
  - `__CA_CMSIS_VERSION_SUB` is `0U`
- `Library/CMSIS/Include/arm_math.h`
  - Header includes `SPDX-License-Identifier: Apache-2.0`
  - Header shows `Project: CMSIS DSP Library`
  - Header shows `$Revision: V.1.5.1`
- `Library/CMSIS/RTOS/Template/cmsis_os.h`
  - Header includes `SPDX-License-Identifier: Apache-2.0`
  - Header shows `Project: CMSIS-RTOS API`
  - Header shows API `Version 1.02`
- `Library/CMSIS/RTOS2/Include/cmsis_os2.h`
  - Header includes `SPDX-License-Identifier: Apache-2.0`
  - Header shows `Project: CMSIS-RTOS2 API`
  - Header shows `Version 2.1.1`
- `Library/CMSIS/Driver/Include/Driver_Common.h`
  - Header includes `SPDX-License-Identifier: Apache-2.0`
  - Header shows common driver definitions API `Version 2.0`
- `Library/CMSIS/Documentation/Driver/html/index.html`
  - Documentation shows CMSIS-Driver `Version 2.05`
- `Library/CMSIS/DAP/Firmware/Source/DAP.c`
  - Header includes `SPDX-License-Identifier: Apache-2.0`
  - Defines `DAP_FW_VER` as `1.10`
- `Library/CMSIS/Documentation/DAP/html/index.html`
  - Documentation shows CMSIS-DAP `Version 1.2.0 (Proposal)`
- `Library/CMSIS/Documentation/Pack/html/index.html`
  - Documentation shows CMSIS-Pack `Version 1.5.0`
- `Library/CMSIS/Utilities/PACK.xsd`
  - Header includes `SPDX-License-Identifier: Apache-2.0`
  - Defines schema version `1.4`
- `Library/CMSIS/Lib`, `Library/CMSIS/RTOS/RTX/LIB`, and `Library/CMSIS/RTOS2/RTX/Library`
  - Current checkout contains prebuilt CMSIS math and RTX libraries.

## 3) License Handling Guidance

For CycloneDX output, use SPDX license ID directly:

- `licenses[0].license.id = Apache-2.0`

Also preserve upstream copyright and license headers in vendored source files.

## 4) Suggested CycloneDX Field Mapping

Recommended component fields:

- `type`: `library`
- `name`: `CMSIS`
- `version`: `5.0.2`
- `scope`: `required`
- `author`: `Arm Limited`
- `description`: `Arm CMSIS vendored in Library/CMSIS, including CMSIS-Core(M), CMSIS-Core(A), CMSIS-DSP Library, CMSIS-Driver, CMSIS-RTOS and CMSIS-RTOS2, CMSIS-DAP firmware, SVD examples, Pack examples, Utilities, prebuilt libraries, templates, and documentation.`
- `licenses[0].license.id`: `Apache-2.0`
- `properties` (recommended custom properties):
  - `src_path = Library/CMSIS`
  - `integration = vendored_source_binary_and_documentation`
  - `cmsis_core_m_version = 5.0.2`
  - `cmsis_core_m_version_macro = 5.0`
  - `cmsis_core_a_version = 1.0`
  - `cmsis_dsp_library_version = 1.5.1`
  - `cmsis_rtos_api_version = 1.02`
  - `cmsis_rtos2_api_version = 2.1.1`
  - `cmsis_driver_common_api_version = 2.0`
  - `cmsis_driver_documentation_version = 2.05`
  - `cmsis_dap_firmware_version = 1.10`
  - `cmsis_dap_documentation_version = 1.2.0 (Proposal)`
  - `cmsis_pack_documentation_version = 1.5.0`
  - `cmsis_pack_schema_version = 1.4`

## 5) Suggested BOM-Ref and purl

Suggested values:

- `bom-ref`: `pkg:generic/cmsis@5.0.2?source=vendored&path=Library/CMSIS`
- `purl`: `pkg:generic/cmsis@5.0.2`

If your internal SBOM naming policy differs, keep naming consistent across all third-party components in this BSP.

## 6) CycloneDX JSON Component Example

```json
{
  "type": "library",
  "bom-ref": "pkg:generic/cmsis@5.0.2?source=vendored&path=Library/CMSIS",
  "name": "CMSIS",
  "version": "5.0.2",
  "scope": "required",
  "author": "Arm Limited",
  "purl": "pkg:generic/cmsis@5.0.2",
  "description": "Arm CMSIS vendored in Library/CMSIS, including CMSIS-Core(M), CMSIS-Core(A), CMSIS-DSP Library, CMSIS-Driver, CMSIS-RTOS and CMSIS-RTOS2, CMSIS-DAP firmware, SVD examples, Pack examples, Utilities, prebuilt libraries, templates, and documentation.",
  "licenses": [
    {
      "license": {
        "id": "Apache-2.0"
      }
    }
  ],
  "properties": [
    { "name": "src_path", "value": "Library/CMSIS" },
    { "name": "integration", "value": "vendored_source_binary_and_documentation" },
    { "name": "cmsis_core_m_version", "value": "5.0.2" },
    { "name": "cmsis_core_m_version_macro", "value": "5.0" },
    { "name": "cmsis_core_a_version", "value": "1.0" },
    { "name": "cmsis_dsp_library_version", "value": "1.5.1" },
    { "name": "cmsis_rtos_api_version", "value": "1.02" },
    { "name": "cmsis_rtos2_api_version", "value": "2.1.1" },
    { "name": "cmsis_driver_common_api_version", "value": "2.0" },
    { "name": "cmsis_driver_documentation_version", "value": "2.05" },
    { "name": "cmsis_dap_firmware_version", "value": "1.10" },
    { "name": "cmsis_dap_documentation_version", "value": "1.2.0 (Proposal)" },
    { "name": "cmsis_pack_documentation_version", "value": "1.5.0" },
    { "name": "cmsis_pack_schema_version", "value": "1.4" }
  ]
}
```

## 7) Compliance Notes

- Keep original upstream copyright/license notices.
- CMSIS in this BSP contains multiple CMSIS subareas, including Core(M), Core(A), DSP Library, Driver, RTOS, RTOS2, DAP firmware sources, SVD, Pack examples, Utilities, templates, prebuilt libraries, and documentation.
- Prebuilt CMSIS math and RTX libraries are present under `Library/CMSIS/Lib`, `Library/CMSIS/RTOS/RTX/LIB`, and `Library/CMSIS/RTOS2/RTX/Library`.
- If producing a finer-grained SBOM, represent major CMSIS subcomponents separately when product policy requires component-level version tracking.
