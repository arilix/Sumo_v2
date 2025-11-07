# 🤖 Sumo_v2 — ESP32 PS3 Controlled Sumo Robot

This project contains the firmware for the **Sumo_v2 robot**, controlled via a **PS3 controller** using an **ESP32** microcontroller.
The code includes movement logic, motor driver control, and wireless pairing with the PS3 controller.

---

## 🧩 Project Structure

```
Sumo_v2/
├── esp32-ps3-master/       # PS3 controller library for ESP32
└── sumo_versi_2.ino        # Main program for Sumo robot control
```

---

## ⚙️ Requirements

### ✅ Hardware

* **ESP32 Dev Module**
* **BTS7960 / L298N Motor Driver**
* **DC Motors** (left & right wheel)
* **PS3 Controller (DualShock 3)**
* **Power supply** 7–12 V

---

## 🧮 Software Setup

### 1. Install Arduino IDE

Download and install the latest [Arduino IDE](https://www.arduino.cc/en/software).

### 2. Add ESP32 Board Manager

Open Arduino IDE → `File` → `Preferences`,
then add this URL to **Additional Board Manager URLs**:

```
https://dl.espressif.com/dl/package_esp32_index.json
```

Go to **Tools → Board → Boards Manager**, search for **ESP32**, and install **version 1.0.6**.

> ⚠️ Use **ESP32 core version 1.0.6**, newer versions may cause PS3 library incompatibility.

---

## 📦 Library Installation

Open Arduino IDE → **Sketch → Include Library → Add .ZIP Library**,
and import the following libraries:

1. [`esp32-ps3-master`](https://github.com/jvpernis/esp32-ps3)
   (already included in this repo under `esp32-ps3-master/`)

Or manually:

```bash
Sketch → Include Library → Add .ZIP Library → select esp32-ps3-master.zip
```

---

## 🔧 Uploading Code

1. Open `sumo_versi_2.ino` in Arduino IDE.
2. Select **Tools → Board → ESP32 Dev Module**.
3. Set correct **Port (COMx or /dev/ttyUSBx)**.
4. Click **Upload** (or press `Ctrl + U`).

If you encounter upload issues:

* Press and hold the **BOOT** button during upload.
* Release once “Connecting…” appears.

---

## 🎮 Pairing PS3 Controller

To pair your PS3 controller:

1. Connect your **PS3 controller** to PC via USB.
2. Run SixaxisPairTool or equivalent to set the **ESP32 MAC address** as the master.
3. Reconnect the controller wirelessly; the LED should light up when paired successfully.

---

## 🚀 Features

* Wireless control via PS3 Bluetooth
* Dual motor driver support (BTS7960 / L298N)
* Real-time response
* Modular code for future upgrade (sensors, auto mode, etc.)

---

## 🧠 Author

**Arilix Tekkom**
📍 Computer Engineering | Robotics & Embedded Systems
🔗 [GitHub Profile](https://github.com/arilix)

---

## 🪪 License

This project is licensed under the MIT License — see [LICENSE](LICENSE) for details.

---

### ⭐ Support

If you find this project useful, give it a ⭐ on GitHub!
