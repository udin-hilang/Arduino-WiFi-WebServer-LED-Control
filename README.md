# ESP32 Web LED Controller

Simple IoT project using ESP32 to control multiple LEDs via a web interface.

## 📌 Overview
This project turns an ESP32 into a simple web server that allows you to control 4 LEDs through a browser.  
The ESP32 connects to a WiFi network and hosts a local webpage with ON/OFF buttons.

## ⚙️ Features
- Web-based LED control (ON / OFF buttons)
- ESP32 connects to WiFi (Station Mode)
- Simple HTML interface served from ESP32
- Serial debug for WiFi status
- Controls 4 output pins

## 🔌 Hardware Used
- ESP32 Dev Board
- 4x LEDs
- Resistors (220Ω recommended)
- Breadboard + jumper wires

## 📍 GPIO Mapping
| LED | GPIO Pin |
|-----|----------|
| 1   | 4        |
| 2   | 17       |
| 3   | 18       |
| 4   | 21       |

## 🌐 How It Works
1. ESP32 connects to WiFi
2. Web server starts on port 80
3. User accesses ESP32 IP from browser
4. Web UI appears with ON/OFF buttons
5. Buttons trigger `/H` (ON) and `/L` (OFF) routes

## 🚀 How to Use
1. Open Arduino IDE
2. Install ESP32 board support
3. Select correct board & port
4. Upload code to ESP32
5. Open Serial Monitor to get IP address
6. Access IP from browser

## 🧠 Routes
- `/` → Main control page
- `/H` → Turn ON all LEDs
- `/L` → Turn OFF all LEDs

## 🧪 Notes
- Make sure WiFi credentials are correct in code
- GPIO pins can be changed based on wiring
- Works best on local network (same WiFi)

## 📜 License
Free to use for learning and experimentation.
