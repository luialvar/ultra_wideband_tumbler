# Legacy Robot-Side UWB Localization

This folder contains the PC/robot-side software from the old UWB localization toolkit. It is included as context for the original system, especially the ROS-side localization and evaluation pipeline.

It is not part of the new STM32L431/DWM3000 firmware target.

## Runtime Entry Point

The `launch/robot.launch` file starts the robot-side stack and exposes several arguments:

| Argument | Purpose |
| --- | --- |
| `useRiegl` | Enables nodes for the Riegl scanner. Default: `false`. |
| `useHectorMapping` | Enables Hector SLAM. Default: `false`. |
| `useUwb` | Enables the UWB localization nodes, including `rosserial_server` and the EKF launch path. Default: `false`. |

The UWB serial setup includes configurable ports such as `/dev/UWB-back`, `/dev/UWB-front-right`, and `/dev/UWB-front-left`, with a default baud rate of `115200`.

## Package Map

| Package | Purpose |
| --- | --- |
| `lms100` | Interfaces with the SICK LMS100 2D laser scanner. |
| `rclock`, `riegl`, `riegl_scan_retriever`, `rivlib` | Interface with the Riegl VZ-400 laser scanner. |
| `rosserial_server` | Serial bridge to the UWB embedded boards. |
| `turtlesim_representation` | Python/turtlesim-based live visualization of localization systems. |
| `uwb` | UWB localization implementation and evaluation. |
| `volksbot` | Base robot code. |

## Migration Relevance

For the new PCB firmware, this folder is mainly useful for understanding how UWB measurements were consumed by the larger localization stack. The embedded migration itself should focus on `../embedded_uwb/` for the old tag/anchor protocol and on `../../software_new_pcb/stm32l4/` for the new firmware implementation.
