# paho.mqtt.embedded-c Third-Party Component Description (for SCA / SBOM)

This document provides SBOM-ready metadata for the vendored Eclipse Paho MQTT embedded C component under `ThirdParty/paho.mqtt.embedded-c`.

## 1) Component Identity

- Component name (`name`): `paho.mqtt.embedded-c`
- Component type (`type`): `library`
- Supplier / project: `Eclipse Paho / IBM Corp.`
- Version: `1.0`
- License: `EPL-1.0 OR EDL-1.0` (SPDX expression)
- Evidence path: `ThirdParty/paho.mqtt.embedded-c`
- Subprojects:
  - `MQTTPacket`
  - `MQTTClient`
  - `MQTTClient-C`

## 2) Evidence for Version and License

Primary evidence in this repository:

- `ThirdParty/paho.mqtt.embedded-c/README.md`
  - Identifies the project as Eclipse Paho MQTT C/C++ client for embedded platforms
  - States the project is dual licensed under EPL and EDL
- `ThirdParty/paho.mqtt.embedded-c/about.html`
  - Lists Eclipse Public License Version 1.0 and Eclipse Distribution License Version 1.0
- `ThirdParty/paho.mqtt.embedded-c/Makefile`
  - Defines `MAJOR_VERSION = 1`, `MINOR_VERSION = 0`, and `VERSION = 1.0`
  - Header states EPL v1.0 and EDL v1.0
- `ThirdParty/paho.mqtt.embedded-c/MQTTPacket/src/MQTTPacket.h`
  - Header states EPL v1.0 and EDL v1.0

## 3) License Handling Guidance

For CycloneDX output, use a license expression:

- `licenses[0].expression = EPL-1.0 OR EDL-1.0`

The upstream README states the user can choose either license. Product release should document which license option is used.

## 4) Suggested CycloneDX Field Mapping

Recommended component fields:

- `type`: `library`
- `name`: `paho.mqtt.embedded-c`
- `version`: `1.0`
- `scope`: `required`
- `author`: `Eclipse Paho / IBM Corp.`
- `description`: `Eclipse Paho MQTT C/C++ client library for embedded platforms vendored in ThirdParty/paho.mqtt.embedded-c, including MQTTPacket, MQTTClient, and MQTTClient-C subprojects.`
- `properties`:
  - `src_path = ThirdParty/paho.mqtt.embedded-c`
  - `integration = vendored_source`
  - `paho_mqtt_embedded_c_version = 1.0`

## 5) Suggested BOM-Ref and purl

- `bom-ref`: `pkg:generic/paho-mqtt-embedded-c@1.0?source=vendored&path=ThirdParty/paho.mqtt.embedded-c`
- `purl`: `pkg:generic/paho-mqtt-embedded-c@1.0`

## 6) Compliance Notes

- Keep upstream license notices in source files.
- Record the selected license option, especially if distributing binaries.
