# ESP32 Environmental & Security Monitoring Node

This project is a modular, fault-tolerant IoT sensor node built on the ESP32 (ESP-WROOM-32D). It integrates seven different environmental and security sensors, featuring a robust boot sequence with hardware health checks and WiFi connectivity.

## System Architecture Highlights
* **Defensive Boot Sequence:** The system verifies the health and connection of every individual sensor before allowing the main loop to run. If any hardware fails, the system halts and outputs specific debug information.
* **WiFi-Safe Analog Polling:** The ESP32's WiFi radio monopolizes the ADC2 channel. To prevent analog sensors from failing when WiFi is enabled, all analog modules (Light, Gas, Sound) are strictly mapped to **ADC1** GPIO pins.
* **Modular Codebase:** Each sensor is isolated into its own `.h` library with standardized boolean `init()` and `read()` functions, keeping the main loop exceptionally clean.

## Hardware Configuration & Pin Mapping

| Sensor Module | Type | ESP32 Pin | Pin Function / Notes |
| :--- | :--- | :--- | :--- |
| **Status LED** | Output | `GPIO 2` | Onboard Blue LED |
| **DHT22** | Digital I/O | `GPIO 4` | Temperature & Humidity |
| **HC-SR501 PIR** | Digital Input | `GPIO 5` | Motion Detection (Active High) |
| **OPT101 Light** | Analog Input | `GPIO 33` | Ambient Light Level (ADC1) |
| **MQ Gas Sensor** | Analog Input | `GPIO 34` | Gas/Smoke Level (ADC1, 5V Heater) |
| **Sound Sensor** | Analog Input | `GPIO 35` | Ambient Noise Level (ADC1) |
| **IR Obstacle (Left)** | Digital Input | `GPIO 18` | Proximity (Active Low) |
| **IR Obstacle (Right)**| Digital Input | `GPIO 19` | Proximity (Active Low) |

*Note: The MQ Gas Sensor requires a 5V supply for its internal heater to function properly. It is connected to the ESP32's `VIN` pin.*

## System Behavior

### 1. Initialization Phase
Upon powering up, the ESP32 executes a sequential hardware diagnostic:
1. Attempts to initialize the onboard LED, DHT22, PIR, Light, Gas, Sound, and both IR sensors.
2. The MQ Gas sensor initiates a passive heat-up/burn-in warning.
3. If all hardware checks pass, the system attempts to connect to the configured WiFi network (10-second timeout).

### 2. Success State
If all systems and network connections report `true`:
* The Serial Monitor outputs the local IP address.
* The onboard LED executes 3 rapid blinks.
* The system transitions into the continuous telemetry data loop.

### 3. Error/Halt State
If *any* component fails initialization (e.g., loose wire, dead sensor):
* The boot sequence immediately flags the exact pin/sensor that failed in the Serial Monitor.
* The system halts to prevent running broken code.
* The onboard LED blinks slowly (500ms intervals) in an infinite loop to visually indicate a hardware fault.

## Telemetry Output Format
Data is polled and transmitted every 2000ms in a clean, scannable format:

`T:31.6C | H:77.3% | Lgt:3795 | Gas:475 | Snd:144 || PIR:[YES] | IR1:[clr] | IR2:[BLK]`