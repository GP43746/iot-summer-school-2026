# Non-Blocking Traffic Light Controller with Pedestrian Override

## Hardware Configuration Requirements
* **1x** Arduino Uno R3
* **1x** Red Light Emitting Diode (LED)
* **1x** Yellow Light Emitting Diode (LED)
* **1x** Green Light Emitting Diode (LED)
* **3x** 220Ω Current-Limiting Resistors
* **1x** Tactile Push-Button Switch
* **1x** Assembly Breadboard and connecting Jumper Wires

## Circuit Mapping Layout
* **Red LED Anode:** Linked directly to Arduino **Digital Pin 11** via a 220Ω resistor.
* **Yellow LED Anode:** Linked directly to Arduino **Digital Pin 10** via a 220Ω resistor.
* **Green LED Anode:** Linked directly to Arduino **Digital Pin 9** via a 220Ω resistor.
* **Pedestrian Button Pin:** Tied between Arduino **Digital Pin 7** and **GND** (internal input pull-up logic active).

## Expected Operational Telemetry Output
```text
[Timestamp: 0 ms] Traffic State Transition -> RED (Initial Loop)
[Timestamp: 5000 ms] Traffic State Transition -> YELLOW
[Timestamp: 7000 ms] Traffic State Transition -> GREEN
[Timestamp: 9140 ms] Traffic State Transition -> PEDESTRIAN OVERRIDE ACTIVATED
[Timestamp: 17140 ms] Traffic State Transition -> RESET FROM OVERRIDE -> CLEARING YELLOW