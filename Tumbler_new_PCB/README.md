# Tumbler New PCB

This folder contains the new PCB design for the upgraded UWB node. It is the hardware target for the STM32CubeMX/HAL firmware in `../software_new_pcb/`.

In the overall migration, this is the new hardware platform:

| Layer | Value |
| --- | --- |
| UWB module | DWM3000 family |
| Microcontroller | STM32L431 |
| Firmware stack | STM32Cube HAL plus Qorvo DW3xxx driver |
| Role in this repository | Active hardware target for the new firmware |

## Contents

| File or folder | Purpose |
| --- | --- |
| `Amadee.kicad_pro` | Main KiCad project entry point. Open this file first in KiCad. |
| `Amadee.kicad_sch` | Top-level schematic. |
| `mcu.kicad_sch` | Microcontroller schematic sheet. |
| `B2Bconn.kicad_sch` | Board-to-board connector sheet. |
| `bms.kicad_sch` | Battery-management subsystem sheet. |
| `buck.kicad_sch` | Buck-regulator/power-conversion sheet. |
| `usb.kicad_sch` | USB-related circuitry. |
| `back-to-back-fets.kicad_sch` | Power-path/protection FET sheet. |
| `Amadee.kicad_pcb` | PCB layout. |
| `AmadeeTumbler.step` | 3D mechanical export for CAD review. |
| `AmadeeTumbler.stl` | 3D mesh export. |
| `AmadeeTumbler.pdf` | PDF design export for quick review. |
| `production/` | Manufacturing outputs. |
| `PowerCalc/` | Power-calculation spreadsheets colocated with the PCB project. |
| `lib/` | KiCad footprint/library assets used by the board. |

## Firmware-Relevant Signals

The PCB defines the real electrical wiring. CubeMX must mirror that wiring so the firmware can use the correct MCU pins for:

| Signal group | Why it matters in firmware |
| --- | --- |
| SPI | Data path between the STM32L431 and the DWM3000. |
| Chip select | Selects the UWB chip during SPI transactions. |
| IRQ | Lets the DWM3000 notify the MCU about TX/RX events. |
| Reset | Allows the MCU to reset the UWB module during bring-up. |
| Wakeup | Lets the MCU bring the UWB module out of low-power states. |
| Power and BMS pins | Control and monitor board power behavior. |

This is why the PCB and CubeMX project must agree. The PCB is the physical truth; CubeMX translates that physical wiring into generated C names used by the HAL and by the Qorvo driver port layer.

## Relationship to the Old PCB

The old `../SKITH_old_PCB/` design represents the DWM1000/STM32F407 generation. This folder represents the DWM3000/STM32L431 generation.

The migration is therefore not just a source-code copy. It changes the radio module, the MCU, the framework, the low-level driver, and the board pinout.
