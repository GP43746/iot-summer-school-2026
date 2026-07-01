# Multi-Key Passive Buzzer Digital Piano Module

## Hardware Required
* **1x** Arduino Uno R3 Microcontroller Board
* **1x** Passive Piezoelectric Buzzer element
* **5x** Tactile Push-Buttons
* **Jumper Wire Matrix**
* **1x** Breadboard

---

## Technical Mapping Layout
The input/output peripheral matrix links to these operational endpoints on the Arduino Uno:
* [cite_start]**Button 1 (Pin 2):** Maps to **Do** (262Hz Major / 261Hz Minor) [cite: 106]
* [cite_start]**Button 2 (Pin 3):** Maps to **Re** (294Hz Major / 293Hz Minor) [cite: 106]
* [cite_start]**Button 3 (Pin 4):** Maps to **Mi** (330Hz Major / 311Hz Minor) [cite: 106]
* [cite_start]**Button 4 (Pin 5):** Maps to **Fa** (349Hz Major / 349Hz Minor) [cite: 106]
* [cite_start]**Button 5 (Pin 6):** Scale Mode Toggle (Flips baseline arrays from Major to Minor scales) [cite: 109]
* **Buzzer Actuator Signal Out:** Digital Pin 11 (PWM control line)

---

## Core Features & Expected Behavior
* [cite_start]**Single-Note Play:** Pressing an individual button fires the matching frequency tone out to Pin 11[cite: 106]. [cite_start]Releasing the button instantly calls `noTone()`, silencing the system[cite: 107].
* [cite_start]**Chord Substitution Mode:** Pressing any two or more note buttons together triggers an override branch that outputs a clean **Sol** tone (392Hz)[cite: 108].
* [cite_start]**Scale Shift Toggle:** Tapping the fifth button switches the underlying math arrays from a bright Major scale down into an acoustic Minor scale configuration[cite: 109].