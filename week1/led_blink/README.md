# Potentiometer-Controlled Rate Limiting LED Blink System

## Hardware Required
* **1x** Arduino Uno R3 Microcontroller Board
* **1x** Breadboard (Standard Half-Size)
* **1x** Light Emitting Diode (LED)
* **1x** 220Ω Current-Limiting Resistor (Band colors: Red, Red, Brown, Gold)
* **1x** 10kΩ Rotary Potentiometer (Analog Input)
* **Solid-core** Jumper Wires

---

## Circuit Diagram Description
Because this project utilizes simple peripheral routing, the schematic mapping is configured as follows:

### 1. LED Circuit Path
* **Anode (Long positive leg)** of the LED is routed directly to Arduino **Digital Pin 9**.
* **Cathode (Short negative leg)** of the LED connects to one terminal of the **220Ω Resistor**.
* The remaining terminal of the **220Ω Resistor** terminates into the common **GND** rail of the Arduino.

### 2. Potentiometer Configuration
* **Terminal 1 (Left pin)** is wired to the Arduino **5V** power delivery pin.
* **Terminal 2 (Wiper / Center pin)** is wired to the Arduino **Analog Input Pin A0**.
* **Terminal 3 (Right pin)** is wired directly to the common Arduino **GND** ground plane.

---

## How to Upload and Run the Code
Follow these steps to deploy this firmware using the native Arduino IDE platform:

1. **Clone/Download:** Ensure your local copy of `led_blink.ino` matches the updated working script.
2. **Launch IDE:** Launch the Arduino IDE and open the `led_blink.ino` sketch.
3. **Hardware Interface:** Connect your physical Arduino Uno R3 board to your machine via an appropriate USB Type-A to Type-B cable.
4. **Target Selection:** Navigate to the top menu and select **Tools -> Board -> Arduino Uno**.
5. **Port Allocation:** Select **Tools -> Port** and choose the active COM port assigned to your connected hardware (e.g., `COM3` or `/dev/ttyUSB0`).
6. **Compile & Write:** Click the **Upload** arrow button in the top left corner (or press `Ctrl + U`). Wait for the status line to read *"Done uploading"*.
7. **Telemetry Stream:** Open the serial interface via **Tools -> Serial Monitor** and set the baud rate filter to **9600 baud**.

---

## Expected Output
* **Hardware Behavior:** The LED wired to Pin 9 will pulse continuously. Rotating the potentiometer knob counter-clockwise drops the analog pin voltage, compressing the delay timeline toward **100ms** (rapid strobe). Rotating the knob clockwise extends the interval up to **2000ms** (slow pulse).
* **Serial Telemetry Stream:** The Serial Monitor will continuously print real-time telemetry packets matching this exact format:
  ```text
  Blink count: 1 | Delay: 100ms
  Blink count: 2 | Delay: 545ms
  Blink count: 3 | Delay: 2000ms