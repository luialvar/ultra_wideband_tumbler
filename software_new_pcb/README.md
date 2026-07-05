# New PCB Software

This folder contains the firmware work for the new Tumbler PCB. This is the active software area for the new board.

## Target Platform

| Layer | New target |
| --- | --- |
| Hardware | Tumbler PCB |
| UWB module | DWM3000 family |
| Microcontroller | STM32L431 |
| Framework | STM32Cube HAL generated from CubeMX |
| UWB driver | Qorvo DW3xxx driver |
| Application goal | Port the legacy tag/anchor ranging logic onto the new board |

## Folder

| Folder | Purpose |
| --- | --- |
| `stm32l4/` | STM32CubeMX/CMake firmware project for the STM32L431-based PCB. |

The firmware target is described in more detail in `stm32l4/README.md`.

## Relationship to the Other Folders

The new firmware uses:

- `../Tumbler_new_PCB/` as the hardware pinout and board-design reference.
- `stm32l4/Drivers/dwt_uwb_driver/` and `stm32l4/Drivers/dwt_uwb_src/` as the local DW3xxx driver integration.
- `../old_uwb_reference_repo/embedded_uwb/` as the old application/protocol reference.
- `../power_calculations/` to understand expected current draw for tag and anchor operating modes.
