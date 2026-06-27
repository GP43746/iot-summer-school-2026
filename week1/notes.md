# Repository Branching Strategy

This document outlines the purpose and scope of each development branch within the `iot-summer-school-2026` ecosystem:

* **`main`**: The production-ready branch. Contains fully working, tested, and reviewed firmware implementations. Direct commits are restricted.
* **`dev`**: The primary integration branch. All weekly practical tasks, code exercises, and feature increments are merged here first for evaluation before hitting production.
* **`sensor-module`**: A dedicated feature branch utilized for developing hardware data acquisition layers, including DHT11 environmental metrics, HC-SR04 ultrasonic logic, and LDR calibrations.
* **`wireless-module`**: A dedicated feature branch reserved for implementing networking frameworks, including ESP32 Bluetooth Low Energy (BLE) GATT setups, Wi-Fi local servers, and MQTT JSON publishers.