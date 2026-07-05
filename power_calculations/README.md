# Power Calculations

This folder contains spreadsheet-based power estimates for the UWB node designs.

The files cover two hardware generations:

| Power-budget family | Hardware context | Notes |
| --- | --- | --- |
| Legacy/earlier calculations | Older SKITH-style UWB assumptions | Kept as reference material for the DWM1000/STM32F407 generation. |
| `AmadeePannel3000.ods` | New DWM3000/Tumbler PCB assumptions | Main reference for the new DWM3000/STM32L431 design and its tag/anchor modes. |

## Files

| File | Purpose |
| --- | --- |
| `AmadeePannel3000.ods` | Power budget for the newer DWM3000-based board. It includes operating-mode assumptions such as TX, RX, idle, and sleep, and separates tag-style and anchor-style behavior. |
| `AmadeePannel_1.ods` | Earlier power-calculation reference. |
| `AmadeePannel_2.ods` | Earlier power-calculation reference. |
| `Power Calculation.xlsx` | Additional spreadsheet reference for the power budget. |
| `.~lock.AmadeePannel.ods#` | LibreOffice lock/temporary file. It is not an engineering input and should not normally be committed. |

## How to Read the Estimates

The power model combines two things:

1. The current consumed by the hardware in each mode.
2. The amount of time the firmware expects to spend in each mode.

The basic calculation is:

```text
energy = voltage * current * time
```

For a complete day, the spreadsheet adds the energy of the relevant modes:

```text
total energy = TX energy + RX energy + idle energy + sleep energy
```

This matters because tag and anchor roles do not behave the same way. A tag can often sleep for most of the time and wake up only for ranging exchanges. An anchor usually consumes more because it must listen for incoming UWB messages for much longer periods.

## Link to Firmware

The firmware cannot change the physical current of the DWM3000 or STM32 by itself, but it can control how long the system stays in TX, RX, idle, and sleep. That is why the power spreadsheets and the embedded state machine need to be reviewed together.
