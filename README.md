# 🩺 Rakshak – Elderly Health Monitoring System

### 👁️ Real-Time Health & Safety Platform for Senior Citizens

Rakshak is a **real-time elderly health and safety monitoring system** that continuously tracks **vital health parameters** such as:
- **Heart Rate (BPM)**
- **Body Temperature (°C)**
- **SpO₂ (Oxygen Saturation)**
- **GPS Location (Live Map View)**

It uses **IoT sensors**, **Blynk Cloud**, and a **React + Node.js dashboard** to provide **instant health alerts**, **live visualization**, and **Telegram-based emergency notifications**.

---

## 🚨 Problem Statement

An integrated dashboard that continuously monitors
vital signs (heart rate, SpO2, temperature) in elderly patients and sends
emergency alerts to caregivers if abnormalities are detected

---

## 💡 Our Solution – “Rakshak”

Rakshak continuously monitors a patient’s vitals through IoT sensors and sends the data to **Blynk Cloud**.  
The system then:
1. Displays real-time readings on a **React web dashboard** with modern UI.
2. Triggers **instant Telegram alerts** if vitals cross safe thresholds.
3. Shows **live GPS location** on an embedded **Leaflet map**.
4. Allows manual **ON/OFF control of alert systems** via Virtual Pin (V6).

This helps caretakers, family members, and medical responders **react faster** to any emergency.

---

## 🧠 Features

| Feature | Description |
|----------|-------------|
| 💓 Real-Time Health Monitoring | Continuously reads HR, SpO₂, and Temperature |
| 🗺️ Live GPS Tracking | Displays the patient's live location on the dashboard |
| 🔔 Smart Alerts | Sends Telegram messages when vitals exceed limits |
| 🧭 Web Dashboard | Modern React-based Blynk-style interface |
| 🟢 Alert Control Switch | Toggle alerts ON/OFF (linked to Virtual Pin V6) |
| 🕹️ MQTT + Blynk Cloud | For smooth data streaming and event handling |
| ⚙️ Node.js Backend | Fetches sensor data, sends alerts, manages sockets |

---


---

## ⚙️ Tech Stack

### 🖥️ Frontend
- React.js
- React Gauge Chart
- Leaflet.js (for free live maps)
- Socket.io (real-time updates)
- Tailwind CSS / Custom Dark Theme

### 🔧 Backend
- Node.js + Express.js
- Socket.io server
- Axios (API communication)
- Telegram Bot API (free alerts)
- Blynk Cloud REST API
- Firebase (optional data storage)

### 🧠 IoT Hardware
- NodeMCU / ESP32 microcontroller
- MAX30102 (Heart rate & SpO₂)
- LM35 / DS18B20 (Temperature)
- NEO-6M (GPS Module)

---

## 🧩 Key Innovations

- **Free Telegram-based alert system** (no GSM charges)
- **Dark-mode dashboard UI inspired by Blynk**
- **Leaflet-based live GPS map (OpenStreetMap – free & open-source)**
- **Alert control integrated via Virtual Pin V6**
- **Lightweight Node.js server that can run even on Raspberry Pi**

---

## 📲 Alert Example

**Telegram Notification:**


