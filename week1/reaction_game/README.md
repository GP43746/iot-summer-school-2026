# Edge-Triggered Hardware Reaction Time Reflex Game

## Hardware Required
* **1x** Arduino Uno R3 Microcontroller Board
* **1x** Green Light Emitting Diode (Signal Indicator)
* **2x** Red / Yellow Light Emitting Diodes (Preparatory Sequence Indicators)
* **3x** 220Ω Current-Limiting Resistors
* **1x** Tactile Push-Button Switch
* **1x** Breadboard
* **Solid-core** Jumper Wires

---

## Circuit Diagram Description
This system maps three outputs and one input utilizing the internal pull-up capability of the ATmega328P microcontroller:

* **Red LED Anode:** Connects directly to Arduino **Digital Pin 11** via a 220Ω resistor.
* **Yellow LED Anode:** Connects directly to Arduino **Digital Pin 10** via a 220Ω resistor.
* **Green LED Anode:** Connects directly to Arduino **Digital Pin 9** via a 220Ω resistor.
* **All Common Cathodes:** Wired to the shared breadboard **GND** ground rail.
* **Push Button Switch:** One side runs to Arduino **Digital Pin 2**, while the opposing side runs to **GND** (Active-LOW input structure).

---

## How to Upload and Run the Code
1. Open the desktop **Arduino IDE** or access your **Tinkercad Circuits** simulator dashboard.
2. Load the `reaction_game.ino` sketch code file into the workspace editor.
3. Wire the components exactly as detailed in the circuit layout description block above.
4. Click **Upload** or hit **Start Simulation**. Open the **Serial Monitor** at **9600 baud**.

---

## Expected Output
* **Visual Loop:** The red and yellow LEDs will flash in random patterns for changing durations. Suddenly, the green LED turns ON.
* **Telemetry Output:** The moment the green LED shines, pressing the button prints real-time precision metrics onto the Serial Monitor stream:
  ```text
  === DIGITAL REACTION GAME INITIALIZED ===
  Instructions: Await the Green LED signal, then press the trigger button immediately!
  
  Starting random generation loop... Keep your hand off the trigger!
  >>> SIGNAL ACKNOWLEDGED! Reflex Reaction Time: 242 ms <<<