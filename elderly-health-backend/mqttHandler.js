import mqtt from "mqtt";
import db from "./firebaseConfig.js";
import { sendAlert } from "./alertHandler.js";

const client = mqtt.connect(process.env.MQTT_BROKER);
const topic = process.env.MQTT_TOPIC;

client.on("connect", () => {
  console.log("✅ MQTT connected");
  client.subscribe(topic);
});

client.on("message", async (topic, message) => {
  try {
    const data = JSON.parse(message.toString());
    console.log("📥 Incoming Data:", data);

    const { heartRate, spo2, temperature, patientId } = data;

    // Store in Firebase
    await db.collection("patients").doc(patientId).collection("vitals").add({
      heartRate, spo2, temperature, timestamp: new Date(),
    });

    // Threshold check
    if (heartRate > 120 || spo2 < 90 || temperature > 38) {
      console.log("🚨 Abnormal reading detected!");
      await sendAlert(patientId, data);
    }
  } catch (error) {
    console.error("Error processing MQTT data:", error);
  }
});

export default client;
