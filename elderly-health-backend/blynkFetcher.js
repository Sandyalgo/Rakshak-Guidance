// blynkFetcher.js
import axios from "axios";
import { db } from "./firebaseConfig.js";
import { sendAlert } from "./alertHandler.js";

const BLYNK_TOKEN = "LQzdFRFGOZtHbmxTiiUsAETfip9IVg50";
const PATIENT_ID = "elderly_001";

async function fetchBlynkData() {
  try {
    // Get real-time Blynk values
    const [hr, spo2, temp, button, lat, lon, speed] = await Promise.all([
      axios.get(`https://blynk.cloud/external/api/get?token=${BLYNK_TOKEN}&V1`),
      axios.get(`https://blynk.cloud/external/api/get?token=${BLYNK_TOKEN}&V2`),
      axios.get(`https://blynk.cloud/external/api/get?token=${BLYNK_TOKEN}&V0`),
      axios.get(`https://blynk.cloud/external/api/get?token=${BLYNK_TOKEN}&V6`),
      axios.get(`https://blynk.cloud/external/api/get?token=${BLYNK_TOKEN}&V3`), // Latitude
      axios.get(`https://blynk.cloud/external/api/get?token=${BLYNK_TOKEN}&V4`), // Longitude
      axios.get(`https://blynk.cloud/external/api/get?token=${BLYNK_TOKEN}&V5`), // Speed
    ]);

    const heartRate = parseFloat(hr.data);
    const spo2Value = parseFloat(spo2.data);
    const temperature = parseFloat(temp.data);
    const manualButton = parseInt(button.data);
    const latitude = parseFloat(lat.data);
    const longitude = parseFloat(lon.data);
    const speedVal = parseFloat(speed.data);

    console.log("💓 From Blynk:", {
      heartRate,
      spo2Value,
      temperature,
      manualButton,
      latitude,
      longitude,
      speedVal,
    });

    // 🔥 Emit to frontend
    if (global.io) {
      global.io.emit("blynk-data", {
        hr: heartRate,
        spo2: spo2Value,
        temp: temperature,
        manual: manualButton,
        lat: latitude,
        lon: longitude,
        speed: speedVal,
      });
    }

    // Generate live location link
    const mapLink = `https://www.google.com/maps?q=${latitude},${longitude}`;

    // ========== MANUAL PUSH ALERT ==========
    if (manualButton === 1) {
      console.log("🖲️ Manual alert button pressed! Sending Telegram alert...");
      await sendAlert(
        PATIENT_ID,
        `🚨 Manual Alert Triggered!\n\n❤️ HR: ${heartRate} bpm\n🫁 SpO₂: ${spo2Value}%\n🌡️ Temp: ${temperature}°C\n🚗 Speed: ${speedVal} km/h\n📍 Location: ${mapLink}`
      );
    }

    // Skip auto alerts if disabled
    if (!global.alertsEnabled) {
      console.log("🚫 Alerts disabled — skipping automatic alerts.");
      return;
    }

    // ========== AUTOMATIC ALERTS ==========
    if (heartRate > 120)
      await sendAlert(
        PATIENT_ID,
        `⚠️ High Heart Rate: ${heartRate} bpm\n📍 Location: ${mapLink}`
      );

    if (spo2Value < 90)
      await sendAlert(
        PATIENT_ID,
        `⚠️ Low SpO₂: ${spo2Value}%\n📍 Location: ${mapLink}`
      );

    if (temperature > 35)
      await sendAlert(
        PATIENT_ID,
        `⚠️ High Temperature: ${temperature}°C\n📍 Location: ${mapLink}`
      );

    // Save to Firestore
    await db.collection("patients").doc(PATIENT_ID).collection("vitals").add({
      heartRate,
      spo2Value,
      temperature,
      manualButton,
      latitude,
      longitude,
      speed: speedVal,
      timestamp: new Date().toISOString(),
    });
  } catch (err) {
    console.error("❌ Error fetching Blynk data:", err.message);
  }
}

setInterval(fetchBlynkData, 5000);
console.log("🔁 Blynk data fetcher started...");
