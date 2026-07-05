# SKITH Old PCB

This folder contains the legacy PCB design for the older SKITH UWB node used as the starting point of the migration.

In the overall project, this is the old hardware reference:

| Layer | Value |
| --- | --- |
| UWB module | DWM1000 |
| Microcontroller family | STM32F407 |
| Firmware stack used with this board | RODOS, legacy wrappers, Decawave DWM1000 API |
| Role in this repository | Hardware reference for the legacy platform |

## Contents

| File or folder | Purpose |
| --- | --- |
| `skithSTMv2.kicad_pro` | KiCad project entry point. Open this file in KiCad to inspect the board. |
| `skithSTMv2.kicad_pcb` | PCB layout. |
| `skithSTMv2.sch` | Legacy schematic file. |
| `Schaltplan_Skith_STM_2.pdf` | PDF schematic export for quick review. |
| `skithSTMv2.brd` | Board file from the older design flow. |
| `sym-lib-table` | KiCad symbol-library configuration. |
| `skithSTMv2.kicad_dru` | KiCad design-rule settings. |
| `skithSTMv2.kicad_prl` | KiCad local/session state; useful for KiCad, but not part of the engineering design itself. |

## How This Fits the Migration

This board is not the firmware target for the new implementation. It is included so the old DWM1000/STM32F407 hardware can be compared against the new DWM3000/STM32L431 design.

The old firmware associated with this hardware is kept separately in `../old_uwb_reference_repo/embedded_uwb/`. The PCB files here describe the electrical design: connectors, MCU pins, UWB module wiring, power rails, and board layout.

For the new board, see `../Tumbler_new_PCB/`.
