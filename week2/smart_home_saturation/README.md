# High-Density Hardware Saturation Smart Home Matrix

## Engineering Overview
This project satisfies the pin-saturation challenge by concurrently routing 11 digital lines and 3 analog telemetry channels on a single ATmega328P microcontroller. The firmware functions as a real-time reactive scheduling framework that processes multi-sensor safety parameters while driving visual, mechanical, and auditory outputs.

---

## Full Pin Interface Reference Directory

### 1. High-Density Digital Mapping
* **Pin 0 & Pin 1 (UART RX/TX):** Hardwired crossing links for PC data visualization loops.
* **Pin 2 (buttonOn):** System activation interrupt line switch (Active-LOW, Internal Pull-up).
* **Pin 3 (buttonOff):** System deactivation interrupt line switch (Active-LOW, Internal Pull-up).
* **Pin 4 (buzzerPin):** Sinks power to the primary acoustic Piezo alarm element.
* **Pin 5, 6, 7 (RGB Pins):** Hardware PWM lines driving the Red, Green, and Blue color states.
* **Pin 8 (statusLed):** Continuous green heartbeat power verification lamp.
* **Pin 9 (servoPin):** PWM generation output controlling the SG90 gate angular vector.
* **Pin 10 (trigPin):** Outbound ultrasound sonar transducer trigger pin.
* **Pin 11 (echoPin):** Inbound pulse capture line for distance data acquisition.
* **Pin 13 (alarmLed):** Hardware diagnostic indicator matching security breach patterns.

### 2. High-Density Analog Mapping
* **Pin A0 (potPin):** Linear voltage input tracking the servo's physical state override.
* **Pin A1 (ldrPin):** Ambient light level photocell measurement circuit.
* **Pin A2 (tempPin):** Core ambient temperature conversion track (TMP36).
* **Pin A4 & Pin A5 (I2C SDA/SCL):** Hardwired multi-drop serial control lines driving the 16x2 text LCD screen.

---

## System Operational Matrix & Expected Outputs
* **SYSTEM STANDBY MODE:** Pressing the OFF button turns the system off. The LCD clears and displays static standby prompts, the status indicators go dark, and the RGB channel remains solid blue.
* **ACTIVE NORMAL MODE:** When active, the status LED stays bright. The LCD continuously tracks conditions in real-time. If the environment stays below 35°C and the sonar sensor reads clear beyond 20cm, the RGB channel stays solid green.
* **CRITICAL BREAK MODE:** If temperature exceeds 35°C or an object crosses closer than 20cm, an alert trips instantly. The RGB element turns red, the standalone alarm LED flashes on, the buzzer emits an acoustic tone, and telemetry logs stream updates down the line.

---

## Saturation Project Troubleshooting Diagnostics

| Symptom / Failure Mode | Probable Root Cause | Corrective Action Matrix |
| :--- | :--- | :--- |
| Pressing the ON/OFF buttons does not trigger a state transition. | High-density wiring overlap or layout short-circuit. | Confirm your buttons are mapped precisely to Pins 2 and 3. Ensure the opposing terminal connections route cleanly to a shared ground rail, as the code relies on internal `INPUT_PULLUP` grounding logic. |
| The LCD text fields display weird characters or scramble randomly. | High current loads are dropping the voltage on the shared power rails. | High-density circuits draw significant current when the servo, buzzer, and multiple LEDs fire at once. Add decoupling capacitors across the breadboard rails to smooth out power spikes during operation. |
| The ultrasonic sensor distance spikes to anomalous or maximum values. | Main script delays are blocking the time-critical echo return signal. | The system utilizes the `pulseIn()` function, which blocks execution while waiting for the echo pin to drop. Ensure your main execution timing loop (`delay(300)`) stays short so the sensor can pulse regularly. |