# ESP32 Deep Sleep Low-Power State Configuration

## Technical Overview
When the ESP32 enters **Deep Sleep**, the main CPU cores, high-speed internal oscillators, RAM memory blocks, and RF components (Wi-Fi/Bluetooth) are entirely unpowered. The only hardware domain left running is the **Ultra-Low-Power (ULP) co-processor** and the **RTC controller module**.

### Key Architectural Concepts:
* **`RTC_DATA_ATTR` Variable Modifier:** Standard SRAM loses all contents when the power drops. Using the prefix `RTC_DATA_ATTR` tells the compiler to allocate that specific variable variable inside the **8KB RTC Slow Memory** area instead. This allows data counters to survive deep sleep cycles.
* **The Boot Lifecycle Reset:** Unlike simple delay loops, waking up from deep sleep triggers a complete system reset vector. Execution does **not** pick up where it left off in `loop()`; instead, it reboots completely from the very top of `setup()`.

---

## Hardware Configuration Requirements
* **1x** ESP32 Development Board (e.g., ESP32 NodeMCU)
* **1x** Micro-USB or USB-C Communication Cable
* **1x** Computer with Arduino IDE / Wokwi Simulator installed

---

## How to Compile and Run the Code
1. Launch the **Arduino IDE** and open the `esp32_deep_sleep.ino` file.
2. Ensure the ESP32 Arduino Board Package is active (**Tools -> Board -> ESP32 Arduino -> ESP32 Dev Module**).
3. Connect the physical board to your computer via USB.
4. Select the matching connection line under **Tools -> Port**.
5. Upload the script. Open the **Serial Monitor** and change the speed option dropdown filter to exactly **115200 baud**.

---

## Expected Output Logging
When the program initializes, it prints logs to the terminal, stays active for 3 seconds, sleeps for 10 seconds, and repeats. The persistent count variable increments flawlessly over boot cycles:

```text
------------------------------------
Boot Cycle Counter Tracker: 1
Wakeup was not caused by deep sleep routines: 0
ESP32 active core task processing execution for 3 seconds...
Setup ESP32 to sleep for 10 Seconds.
Entering Deep Sleep Mode Now. Goodnight!
------------------------------------

[... 10 Seconds of Total Silence / Complete Power Down ...]

------------------------------------
Boot Cycle Counter Tracker: 2
Wakeup caused by numeric RTC hardware timer interrupt.
ESP32 active core task processing execution for 3 seconds...
Setup ESP32 to sleep for 10 Seconds.
Entering Deep Sleep Mode Now. Goodnight!
------------------------------------