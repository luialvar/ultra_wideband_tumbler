# Old UWB Reference Repository

This folder is the legacy UWB localization repository used as a reference for the migration. It comes from a university toolkit around UWB localization and includes both embedded firmware for the old SKITH boards and robot-side localization software.

It is not the target firmware for the new PCB. Its value is that it documents the old system architecture and contains reusable application-level ranging logic.

## Historical Context

This project gathers code connected to the UWB localization approach introduced in the included master-thesis PDF:

`An EKF-SLAM based Ultra Wideband Localization Approach for Unknown Anchor Distributions.pdf`

The repository is structured in two main parts:

| Folder | Purpose |
| --- | --- |
| `embedded_uwb/` | Embedded firmware for the old SKITH UWB boards. This is the main reference for the legacy tag/anchor ranging flow. |
| `robot/` | Robot-side ROS code, including UWB localization and EKF integration. |

## Role in the Migration

The old stack belongs to this generation:

| Layer | Legacy value |
| --- | --- |
| Hardware | SKITH board with DWM1000 |
| Microcontroller | STM32F407 |
| Framework | RODOS and legacy wrappers |
| Driver | Decawave DWM1000 API |
| Application | Tag/anchor ranging firmware and robot-side localization |

The new target is:

| Layer | New value |
| --- | --- |
| Hardware | Tumbler PCB with DWM3000 |
| Microcontroller | STM32L431 |
| Framework | STM32Cube HAL |
| Driver | Qorvo DW3xxx driver |
| Application | New CubeMX firmware for the new PCB |

## What Is Reusable

The useful reusable material is the application/protocol logic:

- tag/anchor message flow,
- `POLL`, `RESP`, `FINAL`, and distance-message structure,
- timestamp packing and unpacking,
- double-sided two-way-ranging timing math,
- node-state transitions and sequencing.

The old DWM1000 driver, RODOS scheduling code, ROS bridge, board wrappers, SPI/GPIO/reset plumbing, and antenna-delay constants are legacy-platform specific and should not be copied directly into the new STM32L431/DWM3000 firmware.
