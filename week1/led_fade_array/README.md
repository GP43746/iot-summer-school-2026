# Conditional Index-Based PWM LED Fading Array

## Hardware Required
* **1x** Arduino Uno R3 Microcontroller Board
* **6x** Light Emitting Diodes (LEDs)
* **6x** 220Ω Current-Limiting Resistors
* **1x** Breadboard
* **Solid-core** Jumper Wires

---

## Circuit Diagram Description
This system utilizes all 6 hardware Pulse Width Modulation (PWM) channels on the Arduino Uno to control the duty cycles simultaneously. The hardware matrix maps out as follows:

* **LED 1 (Index 0):** Anode connected to Arduino **Pin 11 (PWM)**. Cathode via resistor to **GND**.
* **LED 2 (Index 1):** Anode connected to Arduino **Pin 10 (PWM)**. Cathode via resistor to **GND**.
* **LED 3 (Index 2):** Anode connected to Arduino **Pin 9 (PWM)**. Cathode via resistor to **GND**.
* **LED 4 (Index 3):** Anode connected to Arduino **Pin 6 (PWM)**. Cathode via resistor to **GND**.
* **LED 5 (Index 4):** Anode connected to Arduino **Pin 5 (PWM)**. Cathode via resistor to **GND**.
* **LED 6 (Index 5):** Anode connected to Arduino **Pin 3 (PWM)**. Cathode via resistor to **GND**.

---

## How to Upload and Run the Code
1. Launch the **Arduino IDE** or access your **Tinkercad Circuits** dashboard.
2. Load the updated `led_fade_array.ino` sketch into the code workspace.
3. Complete the physical component wiring according to the pin-out specifications listed above.
4. Go to **Tools -> Board -> Arduino Uno** and pick the corresponding active interface port.
5. Click **Upload** (or click **Start Simulation** inside Tinkercad).

---

## Expected Output
Once initialized, the array executes a structured pattern cycling through each pin sequentially:
* **Pin 11 (Index 0):** Executes a rapid fade-in and fade-out breathing loop **two times** continuously.
* **Pin 10 (Index 1):** Executes the fading breathing loop **one single time**.
* **Pin 9 (Index 2):** Breathes **two times**.
* **Pin 6 (Index 3):** Breathes **one time**.
* **Pin 5 (Index 4):** Breathes **two times**.
* **Pin 3 (Index 5):** Breathes **one time** before the main tracking register shifts back to Pin 11 to restart the execution map.

---

## Troubleshooting Tips

| Symptom / Failure Mode | Probable Root Cause | Corrective Action Matrix |
| :--- | :--- | :--- |
| An LED blinks instantly instead of creating a smooth glow fade. | The wrong digital pin destination was selected on the Arduino board. | Verify that the hardware line routes directly into a PWM-enabled pin (`11, 10, 9, 6, 5, or 3`). Standard digital IO lines cannot map duty cycles via `analogWrite`. |
| The repetition count is uneven or jumping incorrectly. | The conditional modulo statement (`i % 2 == 0`) is processing a misaligned array configuration. | Ensure that your array size initialization variable inside the setup `for` loop tracks to exactly `i < 6` to prevent evaluation errors. |
| The LED appears faint or dims out too fast. | Current-limiting resistor value is too high for power scaling. | Ensure you are deploying resistors between 220Ω and 330Ω. Exceeding 1kΩ will limit current drastically, making PWM changes difficult to see. |