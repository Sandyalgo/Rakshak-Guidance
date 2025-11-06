# 🛡️ Rakshak – IoT-Based Elderly Health Monitoring & Alert System

### 🌍 Empowering Elderly Care with Real-Time Health Intelligence


---

## 💡 Overview

**Rakshak** is an **IoT-enabled smart health monitoring system** designed to continuously track vital parameters of elderly individuals.
It integrates **ESP32 hardware**, **health sensors**, **cloud connectivity**, and **real-time web & Telegram alerting** to detect medical anomalies and send instant notifications to caregivers.

> “A complete, low-cost IoT solution for elderly healthcare monitoring, alerting, and live tracking.”

---

## ⚙️ Core Features

### 🩺 1. Real-Time Health Monitoring

* **Heart Rate (bpm)** via MAX30102 Pulse Oximeter
* **SpO₂ (Oxygen Saturation %)** via MAX30102
* **Body Temperature (°C)** via LM35 sensor
* **GPS Location** via NEO-6M module
* **Manual SOS Button** for emergency alerts

Data is collected by the **ESP32** and uploaded to the **Blynk IoT Cloud**.

---

### ☁️ 2. Cloud Connectivity (Blynk IoT)

* Live dashboards with real-time charts and indicators
* Virtual pins for continuous data streaming
* Secure connection through Wi-Fi

**Virtual Pins Mapping**

| Parameter    | Blynk Virtual Pin |
| ------------ | ----------------- |
| Temperature  | V0                |
| Heart Rate   | V1                |
| SpO₂         | V2                |
| Latitude     | V3                |
| Longitude    | V4                |
| Speed        | V5                |
| Manual Alert | V6                |

---

### 🛰️ 3. Location Tracking (GPS)

* Continuous GPS readings for **Latitude**, **Longitude**, and **Speed**
* If GPS signal is unavailable, **default fallback coordinates** are used

  ```
  Latitude: 17.457441  
  Longitude: 78.668360  
  Speed: 0.13 km/h
  ```

---

### 📲 4. Backend Server (Node.js + Firebase)

* Fetches live data from **Blynk Cloud** using REST API
* Stores readings in **Firebase Firestore** for history
* Performs **threshold analysis** (HR, SpO₂, Temp)
* Sends emergency alerts through **Telegram Bot API**

---

### 🚨 5. Instant Emergency Alert System

* **Automatic Alerts:** Triggered when thresholds are breached

  * HR > 120 bpm
  * SpO₂ < 90%
  * Temp > 38°C
* **Manual Alerts:** Triggered via physical push button
* Alerts are sent via **Telegram** with real-time Google Map link:

📍 Example Message:

```
🚨 Alert for Elderly_001  
High Temperature: 52.95 °C  
Location: https://maps.google.com/?q=17.457441,78.668360
```

---

### 💻 6. React Web Dashboard (Frontend)

A modern, dark-themed dashboard displays live vitals, GPS map, and system status.

**Key Modules:**

* Real-time gauge charts for HR, SpO₂, and Temperature
* Mini Map with current GPS position
* “Alert ON/OFF” toggle and “Manual Button” status indicator

**Tech Stack:**
React.js | Socket.io | Leaflet.js | Firebase | CSS3


---

## 🧩 Tech Stack

| Layer            | Technology                                     |
| ---------------- | ---------------------------------------------- |
| **IoT Hardware** | ESP32, MAX30102, LM35, GPS NEO-6M, Push Button |
| **IoT Platform** | Blynk Cloud                                    |
| **Backend**      | Node.js + Express.js                           |
| **Database**     | Firebase Firestore                             |
| **Frontend**     | React.js + Socket.io + Leaflet                 |
| **Alerts**       | Telegram Bot API                               |
| **Optional**     | SIM800L GSM for offline SMS/call               |

---

## 🧱 System Architecture

```
ESP32 Sensors (MAX30102, LM35, GPS)
        ↓
     Blynk Cloud
        ↓
 Node.js Backend  ←→  Firebase Firestore
        ↓
  React.js Web Dashboard
        ↓
   Telegram Bot Alerts
```

---

## 🧠 How It Works

1. ESP32 continuously collects data from sensors
2. Data is transmitted to **Blynk IoT** over Wi-Fi
3. Backend fetches data every few seconds
4. Threshold checks are performed:

   * HR > 120 → Tachycardia alert
   * SpO₂ < 90 → Hypoxia alert
   * Temp > 38°C → Fever alert
5. On alert, Telegram sends a live location message
6. All data is displayed live on a React web dashboard

---

## 🔧 Hardware Setup

| Component    | Connection to ESP32                           |
| ------------ | --------------------------------------------- |
| LM35         | Analog pin (A0)                               |
| MAX30102     | I2C (SDA=21, SCL=22)                          |
| GPS NEO-6M   | TX=17, RX=16                                  |
| Push Button  | GPIO 25                                       |
| GSM SIM800L  | TX=27, RX=26 (optional)                       |
| Power Supply | 5V VIN (USB or Li-ion 3.7V + Boost Converter) |


---

## 🚀 Deployment

### Clone the repository

```bash
git clone https://github.com/Sandyalgo/Rakshak-Guidance.git
```

### ESP32 Firmware

1. Open Arduino IDE
2. Load `Rakshak.ino` inside `ESP32-Firmware/`
3. Select board: **ESP32 Dev Module**
4. Upload code

### Backend (Node.js)

```bash
cd elderly-health-backend
npm install
npm start
```

### Frontend (React)

```bash
cd elderly-health-frontend
npm install
npm run dev
```

Then open your browser at **[http://localhost:3000](http://localhost:3000)**

---

## 📸 Project Demonstration

| ESP32 IoT Prototype | Live Data Logging | React Dashboard | Telegram Alerts |
|----------------------|------------------|-----------------|-----------------|
| ![ESP32 Prototype](https://github.com/user-attachments/assets/5a480caa-e78f-480f-ab0b-d1dfc9adc118) | ![Serial Monitor](https://github.com/user-attachments/assets/253c7a12-e627-4c16-b2be-06db23fdf1e5) | ![React Dashboard](https://github.com/user-attachments/assets/0e8b419c-8d42-4542-a28e-266bb9773427) | ![Telegram Alerts](https://github.com/user-attachments/assets/0f28de8c-77d1-4256-8143-9a334af2c7d6) |

---

## 🧭 Future Enhancements

* Add GSM module fallback for areas with no Wi-Fi
* Integrate voice calls using Twilio API
* Predictive anomaly detection using AI models
* Mobile app using React Native

---

## 💬 Team & Credits

**Project:** Rakshak – Real-Time Elderly Health Monitor
**Team Members:** Sandeep Gadi and Team
**Platform:** Forge Hackathon
**Institute:** Sreenidhi Institute of Science and Technology (SNIST)

---

> ⭐ *“Rakshak aims to bridge the gap between technology and healthcare — ensuring that every second counts in saving lives.”*  
> — **SNIST 💚**

