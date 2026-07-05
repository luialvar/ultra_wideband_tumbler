# Legacy Embedded UWB Firmware

This folder contains the embedded firmware for the old SKITH UWB boards. It is included as a reference for the new DWM3000/STM32L431 firmware, not as code that should be copied directly.

## Hardware

The original target is the SKITH UWB board from the University of Wuerzburg environment. The board combines:

| Part | Legacy platform |
| --- | --- |
| Microcontroller | STM32F4 family, specifically the STM32F407 generation in this project context |
| UWB transceiver | Decawave DWM1000 |
| Programming/debug | ST-Link over SWD |
| Framework | RODOS plus legacy board wrappers |

The hardware design files for the old board are stored separately in `../../SKITH_old_PCB/`.

## Software Structure

| Folder | Purpose |
| --- | --- |
| `decadriver/` | Legacy Decawave DWM1000 driver code. |
| `wrapper/` | Board-support wrappers around the old driver and platform. |
| `rodos/` | RODOS framework sources used by the old firmware. |
| `ros_lib/` | RODOS/ROS bridge support. |
| `include/` | Shared headers for the UWB application. |
| `src/common/` | Shared protocol, timestamp, and state-machine logic. |
| `src/anchor/` | Anchor role implementation. |
| `src/tag/` | Tag role implementation. |
| `src/id/` | Utility firmware for publishing/reading the chip identity. |
| `src/monitor/` | Monitoring firmware for observing UWB messages and bridging selected messages to ROS. |

## Reuse Boundary

Reusable for the new firmware:

- tag/anchor state-machine design,
- UWB message layout,
- `POLL`, `RESP`, `FINAL`, and `DISTANCE` sequencing,
- timestamp extraction and packing,
- double-sided two-way-ranging math.

Not reusable as-is:

- DWM1000 driver code,
- RODOS scheduling and thread structure,
- ROS bridge code,
- old SPI/GPIO/reset wrappers,
- old antenna-delay calibration constants.

The new firmware should port the application concepts onto the STM32Cube HAL and Qorvo DW3xxx driver base in `../../software_new_pcb/stm32l4/`.

## Legacy Build Notes

These commands describe the historical build flow for the old firmware:

```bash
sudo apt install -y apt-utils
sudo apt install -y clang clang-format clang-tools gdb
sudo apt install -y gcc-multilib g++-multilib
sudo apt install -y gcc-arm-none-eabi binutils-arm-none-eabi libnewlib-arm-none-eabi
sudo apt install -y cmake
```

```bash
cd build
cmake -DCMAKE_TOOLCHAIN_FILE=../rodos/cmake/port/skith.cmake ..
make all
```

Flashing was done over SWD with an ST-Link. The old workflow depends on the SKITH hardware setup and university-local documentation, so it should be treated as legacy reference material.
