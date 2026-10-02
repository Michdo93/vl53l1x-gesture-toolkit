# vl53l1x-gesture-toolkit

A lightweight, zero-additional-hardware gesture control toolkit using a single **VL53L1X Time-of-Flight (ToF)** sensor and microcontrollers (ESP32, ESP32-C3, Arduino, or RP2040).

By dynamically configuring the internal **SPAD (Single-Photon Avalanche Diode)** array on the VL53L1X, this repository turns a single optical sensor into a 2D optical gesture tracker without requiring camera modules or complex computer vision algorithms.

---

## 🚀 Key Features

- **Zero Additional Hardware:** Requires only 4 wires (`VCC`, `GND`, `SDA`, `SCL`). No external resistors or optical components needed.
- **Dual-Zone SPAD Switching:** Splits the sensor field of view into Left and Right Region-of-Interest (ROI) zones for spatial detection.
- **Gesture Engine:** Recognizes `Swipe Left`, `Swipe Right`, `Hold`, and distance-based threshold triggers.
- **Multi-Platform Support:** Ready-to-run examples for Arduino IDE, ESP32, ESP32-C3, and Native USB HID devices.

---

## 🛠 Hardware Setup

Connect your VL53L1X breakout module directly to your microcontroller via standard I2C pins:

```text
  +------------------+             +--------------------+
  |     VL53L1X      |             |   Microcontroller  |
  |  Breakout Board  |             |  (ESP32 / Arduino) |
  |                  |             |                    |
  |             VCC  +------------>+  3.3V / 5V         |
  |             GND  +------------>+  GND               |
  |             SDA  +------------>+  SDA (e.g. GPIO 21)|
  |             SCL  +------------>+  SCL (e.g. GPIO 22)|
  +------------------+             +--------------------+
```

For detailed pinout matrices across different MCU platforms, check [docs/WIRING.md](https://www.google.com/search?q=docs/WIRING.md).

---

## 📂 Repository Structure

```text
vl53l1x-gesture-toolkit/
├── README.md
├── docs/
│   └── WIRING.md                            # Wiring diagrams and pinout charts
├── examples/
│   ├── 01_basic_distance/
│   │   └── 01_basic_distance.ino            # Basic distance measurement via Serial
│   ├── 02_roi_dual_zone/
│   │   └── 02_roi_dual_zone.ino             # Alternating SPAD ROI zone measurements
│   ├── 03_gesture_swipe_tap/
│   │   └── 03_gesture_swipe_tap.ino         # Swipe & Hold gesture recognition
│   └── 04_usb_hid_media_keys/
│       └── 04_usb_hid_media_keys.ino        # USB Media Key Controller (Play/Pause/Skip)
└── src/
    └── VL53L1X_GestureEngine.h
```

---

## 💻 Getting Started

1. Open **Arduino IDE**.
2. Install the **Pololu VL53L1X** library via the Library Manager (`Tools -> Manage Libraries...`).
3. Clone or download this repository.
4. Flash `examples/03_gesture_swipe_tap/03_gesture_swipe_tap.ino` to your board.
5. Open the **Serial Monitor** at `115200` baud rate and wave your hand across the sensor!

---

## 📄 License

MIT License. Free for personal, commercial, and educational DIY Smart Home projects!
