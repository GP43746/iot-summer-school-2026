# 4x4 Multiplexed LED Matrix Initials Display

## Hardware Required
* **1x** Arduino Uno R3 Microcontroller Board
* **16x** Light Emitting Diodes (LEDs) arranged in a 4x4 matrix configuration
* **4x** 220Ω Current-Limiting Resistors (Wired in series with column lines)
* **1x** Breadboard
* **Solid-core** Jumper Wires

---

## Circuit Diagram Description
The 16 individual LEDs are multiplexed into a common grid using 4 Row lines and 4 Column lines to save pin overhead. The connections map to the following pinouts:

### Row Common Cathodes (Active LOW Control Lines)
* **Row 1 (Top Row):** Connects to Arduino **Digital Pin 2**
* **Row 2:** Connects to Arduino **Digital Pin 3**
* **Row 3:** Connects to Arduino **Digital Pin 4**
* **Row 4 (Bottom Row):** Connects to Arduino **Digital Pin 5**

### Column Common Anodes (Active HIGH Control Lines via Resistors)
* **Column 1 (Left Col):** Connects through a 220Ω resistor to Arduino **Digital Pin 6**
* **Column 2:** Connects through a 220Ω resistor to Arduino **Digital Pin 7**
* **Column 3:** Connects through a 220Ω resistor to Arduino **Digital Pin 8**
* **Column 4 (Right Col):** Connects through a 220Ω resistor to Arduino **Digital Pin 9**

---

## How to Upload and Run the Code
1. Open your **Tinkercad Circuits** workspace or the desktop **Arduino IDE**.
2. Load `led_matrix.ino` into the programming editor panel.
3. Wire the common-anode columns and common-cathode rows exactly matching the circuit map description above.
4. Verify port assignments and click **Upload** or **Start Simulation**.

---

## Expected Output
Due to rapid row-by-row scanning at a refresh frequency of ~1ms, individual pixel strobes blend into a single continuous visual image via **Persistence of Vision (POV)**. The matrix grid cleanly illuminates the shape of the initial **'G'** persistently:
* Row 0 activates columns 0, 1, 2 ($\text{LEDs } 1, 2, 3$).
* Row 1 activates column 0 ($\text{LED } 5$).
* Row 2 activates columns 0, 2, 3 ($\text{LEDs } 9, 11, 12$).
* Row 3 activates columns 1, 3 ($\text{LEDs } 14, 16$).

---

## Troubleshooting Tips

| Symptom / Failure Mode | Probable Root Cause | Corrective Action Matrix |
| :--- | :--- | :--- |
| The wrong letter or scrambled LED configurations are turning ON. | Row and column array mappings are flipped or out of sequence. | Verify that row pins 2–5 and column pins 6–9 are wired in ascending order from top-to-bottom and left-to-right. |
| The matrix looks dim or flickers noticeably. | The strobe delay timing inside the inner rendering loops is too long. | Ensure that `delay(1);` is used. Increasing this value beyond 10–15ms breaks the POV effect, causing the rows to flash individually. |
| Faint shadow artifacts ("ghosting") appear on adjacent unmapped LEDs. | Pins are not being reset cleanly before moving to the next pixel coordinate. | Verify that the code actively drives the current row back `HIGH` and column back `LOW` at the end of each iteration to clear remaining voltage. |