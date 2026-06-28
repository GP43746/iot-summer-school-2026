# Autonomous Threshold-Driven Smart Street Light

## Hardware Configuration Requirements
* **1x** Arduino Uno R3 Microcontroller Board
* **1x** Photoresistor (LDR)
* **1x** Light Emitting Diode (LED)
* **1x** 10kΩ Calibration Resistor (Pull-down configuration)
* **1x** 220Ω Current-Limiting Resistor
* **1x** Standard Breadboard
* **Solid-core** Hookup Jumper Wires

---

## Circuit Diagram Description
The component network matches your active Tinkercad layout matrix:
* **Sensor Logic:** One terminal of the Photoresistor connects to the Arduino **5V** power delivery rail. The remaining terminal connects to **Analog Input Pin A0** and simultaneously routes through a 10kΩ resistor directly down to the shared system ground (**GND**).
* **Actuator Logic:** The LED Anode connects directly to Arduino **Digital Pin 9** via a series 220Ω protection resistor. The LED Cathode routes directly back into a common ground (**GND**) bus tie-point.

---

## Execution Instructions
1. Open your **Tinkercad Circuits** dashboard pane.
2. Initialize or paste the `smart_street_light.ino` code block inside the scripting interface window.
3. Verify that the hardware peripheral connections mirror the functional layout matrix exactly.
4. Click **Start Simulation** and expand the **Serial Monitor** tab panel at **9600 baud**.

---

## Expected Output Behavior
* **Low Ambient Illumination (PHOTO_VALUE < 300):** Adjusting the interactive photoresistor brightness slider down to simulate night will drop the voltage checked by `analogRead`. The Serial Monitor streams integer outputs below 300, driving the LED on Pin 9 **HIGH** for a 1-second locked cycle window.
* **High Ambient Illumination (PHOTO_VALUE >= 300):** When external light exceeds the boundary marker, the tracking loop drives Pin 9 **LOW**, turning the lighting node completely off.

---

## Engineering Troubleshooting Diagnostics

| Failure State Characterization | Direct Probable Root Cause | Tactical Remediation Vector |
| :--- | :--- | :--- |
| The LED remains fully dark regardless of changing brightness slider conditions. | The LED component package orientation is reversed on the breadboard paths. | Inspect the LED cathode terminal configuration to ensure the short pin tracks straight down into the common ground line rail. |
| The serial data output window prints static non-changing `0` numbers. | The signal tap line routing from A0 is isolated from the 5V power loop. | Verify that the wire extending down to A0 shares a common vertical circuit column with both the photoresistor output terminal leg and the pull-down resistor input leg. |
| The system logic takes a long time to react when dragging the slider tool. | The delay value blocks structural processing sweeps for too long. | Your code includes `delay(1000);` blocks inside the conditional statement filters. To increase sensor polling frequency, decrease the delay magnitude down to a smaller value such as `delay(100);`. |