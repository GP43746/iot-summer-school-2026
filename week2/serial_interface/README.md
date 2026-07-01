# Validated Serial Command Processor Terminal

## Hardware Configuration Requirements
* **1x** Arduino Uno R3 Microcontroller Board
* **1x** Built-in LED Indicator (Digital Pin 13)
* **1x** USB Interface Cable for Data Telemetry

---

## Operational Syntax Matrix
To control the hardware, type the exact command strings below into your Serial Monitor configured at **9600 baud**:

| Command String Input | System Hardware Action |
| :--- | :--- |
| `LED_ON` | Turns the built-in LED on. |
| `LED_OFF` | Turns the built-in LED off. |
| `BLINK_X` | Blinks the LED X times (where parameter $X \in [1, 9]$). |
| `STATUS` | Prints current pin states and global blink counts. |
| `RESET` | Restarts the cumulative blink counter back to zero. |
| *Any other text* | Returns standard error code: `ERROR: Unknown command`. |

---

## Troubleshooting Guide

| Symptom / Failure Mode | Probable Root Cause | Corrective Action Matrix |
| :--- | :--- | :--- |
| Valid commands consistently return `ERROR: Unknown command`. | Hidden formatting characters like carriage returns (`\r`) are appending to the inputs. | Ensure that you use `.trim()` in your code to strip whitespace, or change the dropdown setting in your Serial Monitor from "Both NL & CR" to "Newline only". |
| The `BLINK_X` command fails to parse numeric arguments. | Wrong index offset slicing string data tokens. | Verify that the substring parsing boundary matches `substring(6)` precisely so that it targets the character right after the underscore. |
| No feedback or responses appear in the output window. | Serial channel speed mismatch or disconnected interface port. | Double-check that your terminal software is actively listening on port communications configured to exactly **9600 baud**. |