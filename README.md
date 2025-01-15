# Bidirectional Visitor Counter

## Overview
The **Bidirectional Visitor Counter** is an embedded project that tracks the number of visitors entering and exiting a space using infrared sensors. It controls a relay to switch lights on or off based on the presence of visitors and also displays the data on an OLED screen. Additionally, the project integrates with Ubidots to log data such as visitor count and the current status of the space.

## Features
- **Visitor Counting**: Tracks the number of visitors entering and exiting.
- **Relay Control**: Turns lights on when visitors are present and off when no visitors remain.
- **OLED Display**: Shows real-time visitor data, including:
  - Current number of visitors.
  - Total IN and OUT counts.
- **Ubidots Integration**: Sends data to Ubidots for remote monitoring:
  - IN count.
  - OUT count.
  - Current visitor count.
- **LED Notification**: Indicates visitor presence with an LED.

## Components Used
- **Microcontroller**: ESP32 (or similar WiFi-enabled microcontroller)
- **Infrared Sensors**: Two IR sensors for entry and exit detection.
- **OLED Display**: Adafruit SSD1306 (128x64 resolution).
- **Relay Module**: Controls the lights based on visitor presence.
- **LED**: Provides a visual notification for visitor presence.

## Libraries Required
Ensure you have the following libraries installed in your Arduino IDE:
- `WiFi.h`
- `Wire.h`
- `Adafruit_GFX.h`
- `Adafruit_SSD1306.h`

## Circuit Connections
| Component       | Pin on ESP32      |
|------------------|-------------------|
| IR Sensor IN     | GPIO 2           |
| IR Sensor OUT    | GPIO 32          |
| Relay            | GPIO 18          |
| LED              | GPIO 13          |
| OLED SDA         | GPIO 21 (default)|
| OLED SCL         | GPIO 22 (default)|

## Installation
1. Clone the repository:  
   ```bash
   git clone https://github.com/your-username/Bidirectional-Visitor-Counter.git
2. Open the code file `BidirectionalVisitorCounter.ino` in Arduino IDE.
3. Replace the following placeholders with your specific details:
   - **WiFi Credentials**: Replace `WIFISSID` and `PASSWORD` with your WiFi network details.
   - **Ubidots Details**: Replace `TOKEN`, `ID_IN`, `ID_OUT`, and `ID_NOW` with your Ubidots API token and variable IDs.
4. Upload the code to your ESP32 using the Arduino IDE.

## Usage

Once powered, the system will:
- Connect to the specified WiFi network.
- Start monitoring visitor IN/OUT activity via IR sensors.
- Display real-time visitor data on the OLED screen.
- Automatically control the relay and LED based on visitor presence.
- Push data to Ubidots for remote logging and monitoring.

## Key Functions

- **sendValueToUbidots**: Sends data to Ubidots using HTTP POST requests.
- **setup**: Initializes components, including WiFi, relay, OLED display, and sensors.
- **loop**: Continuously checks for sensor changes, updates the OLED display, controls the relay, and sends data to Ubidots.

## Sample Output

### OLED Display
- **When visitors are present**:
