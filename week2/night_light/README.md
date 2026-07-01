# Multi-Mode Interrupt-Driven PWM Night Light

## Hardware Configuration Requirements
* **1x** Arduino Uno R3 Microcontroller Board
* [cite_start]**1x** Light Emitting Diode (LED) [cite: 84]
* [cite_start]**1x** 220Ω Current-Limiting Resistor [cite: 84]
* [cite_start]**1x** Tactile Push-Button Switch [cite: 85]
* [cite_start]**1x** Breadboard and Hookup Jumper Wires [cite: 85]

---

## Operational Mode Directory
[cite_start]Pressing the mode control button changes the software states sequentially[cite: 126]:
1. [cite_start]**Slow Breathing Mode:** Uses hardware timers to smoothly cycle LED brightness up and down over a 3.0-second window[cite: 125, 126].
2. [cite_start]**Fast Pulse Mode:** Speeds up step modifications to run a rapid 0.5-second pulse cycle[cite: 126].
3. [cite_start]**SOS Pattern Mode:** Disables linear fading to flash a standard Morse code distress signal loop (`... --- ...`)[cite: 126].

---

## Troubleshooting Guide

| Symptom / Failure Mode | Probable Root Cause | Corrective Action Matrix |
| :--- | :--- | :--- |
| Pressing the mode selection button does not trigger state switches. | Pin mapping conflict or floating hardware contacts. | [cite_start]Ensure the button links to Digital Pin 2[cite: 85]. The code utilizes hardware External Interrupt 0, which is physically tied to Pin 2 on the ATmega328P. |
| The LED switches states instantly instead of fading smoothly. | A non-PWM digital pin is utilized in hardware routing. | [cite_start]Make sure the LED connects directly to an active PWM-capable pin layout (such as Pin 6)[cite: 84]. Standard digital IO channels cannot process duty cycles via `analogWrite()`. |
| The state machine skips modes or triggers erratically on a single button press. | Mechanical switch contact bouncing. | The current setup relies on a fast interrupt routine. Add a hardware debouncing capacitor ($0.1\mu\text{F}$) across the button pins to smooth out voltage spikes. |