# Full-Duplex UART Cross-Board Master-Slave Inter-Processor Link

## Technical Protocol Analysis
Universal Asynchronous Receiver-Transmitter (**UART**) is a hardware serial communication architecture that transfers bytes sequentially bit-by-bit over single lines. Because transmission is *asynchronous* (lacking a shared clock line), both boards must be explicitly configured to match the exact same **Baud Rate** (data transmission speed, set here to **9600 bits per second**). 

### Critical Data Transfer Blueprint:
1. When the push button attached to the **Master** board changes state, the micro-controller formats a character string array followed by standard termination bytes (`\n` line feed).
2. The data shifts out of the Master **TX (Transmitter)** pin into the internal shift registers of the Slave **RX (Receiver)** pin.
3. The **Slave** board pulls data out of its ring buffer via `Serial.readStringUntil('\n')`, evaluates the command tokens against condition blocks, and generates PWM angle targets to position the servo arm.

---

## Hardware Configuration Requirements
* **2x** Arduino Uno R3 Microcontroller Boards
* **1x** Micro Servo Motor (SG90 Variant)
* **1x** Tactile Push-Button Switch
* **1x** 10kΩ Resistor (Configured as an external hardware pull-down layout)
* **1x** Integration Breadboard
* **Solid-core** Hookup Jumper Wires

---

## Circuit Interface Mapping
The routing connection matrix between the discrete microcontrollers maps as follows:

### Cross-Board Communication Lines
* Master **Pin 1 (TX)** $\rightarrow$ Slave **Pin 0 (RX)** (Green crossover link)
* Master **Pin 0 (RX)** $\rightarrow$ Slave **Pin 1 (TX)** (Green crossover link)
* Master **GND Pin** $\rightarrow$ Slave **GND Pin** $\rightarrow$ Breadboard Common Ground (**Mandatory Common Reference Ground**)

### Peripherals Matrix
* **Master Input:** Push button terminal wired to Master **Digital Pin 2**, while the opposing logic side bridges through a 10kΩ pull-down resistor straight to **GND**.
* **Slave Output:** Servo Signal Line maps directly to Slave **Digital Pin 9 (PWM)**. Servo Power maps to **5V**, and Servo Ground maps to **GND**.

---

## Execution Instructions
1. Access your digital workspace inside **Tinkercad Circuits**.
2. Flash the `master.ino` codebase into the left Arduino board scripting window.
3. Flash the `slave.ino` codebase into the right Arduino board scripting window.
4. Open the simulation and open the **Serial Monitor windows for both devices**.

---

## Expected Output Logging
* **Idle State:** The servo remains stationary at 0 degrees.
* **Button Pressed (HIGH):** Master outputs the text string `OPEN` over the TX pin. The Slave reads the command packet, rotates the servo horn to **90 degrees**, and outputs a confirmation log string: `Gate Opened`.
* **Button Released (LOW):** Master outputs `CLOSE`. The Slave reads it, snaps the servo horn back to **0 degrees**, and updates telemetry: `Gate Closed`.

---

## UART Protocol Troubleshooting Diagnostics

| Symptom / Failure Mode | Probable Root Cause | Corrective Action Matrix |
| :--- | :--- | :--- |
| Code uploads successfully, but dragging the button creates zero servo response. | The TX and RX communication wires are misaligned or mapped in parallel. | UART requires crossed lines. Ensure Master **TX (Pin 1)** routes strictly to Slave **RX (Pin 0)**. Connecting TX-to-TX or RX-to-RX will result in silent bus collision failures. |
| The Slave reads garbled commands or completely ignores valid incoming bytes. | The two distinct hardware boards are floating without a common ground reference point. | Verify that a physical jumper wire bridges a **GND** pin from the left Arduino directly to a **GND** pin on the right Arduino. Without this common line, relative logic voltages cannot be decoded accurately. |
| Compiling error or sketch upload fails on physical boards. | Active USB programming lines are conflicting with the hardware UART bus. | On standard AVR boards like the Arduino Uno, Pins 0 and 1 share the exact same hardware serial channel as the USB interface. **Always disconnect the TX/RX jumper lines** before uploading new sketches, and reconnect them only after uploading completes. |