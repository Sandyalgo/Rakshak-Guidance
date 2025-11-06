// alertHandler.js
import axios from "axios";
import dotenv from "dotenv";

dotenv.config();

const TELEGRAM_BOT_TOKEN = process.env.TELEGRAM_BOT_TOKEN;
const TELEGRAM_CHAT_ID = process.env.TELEGRAM_CHAT_ID;

export async function sendAlert(patientId, message) {
  try {
    const text = `⚠️ Alert for ${patientId}\n${message}`;

    const response = await axios.post(
      `https://api.telegram.org/bot${TELEGRAM_BOT_TOKEN}/sendMessage`,
      {
        chat_id: TELEGRAM_CHAT_ID,
        text,
      }
    );

    console.log("📩 Telegram alert sent:", response.data.ok);
  } catch (err) {
    console.error("❌ Telegram alert failed:", err.message);
  }
}
