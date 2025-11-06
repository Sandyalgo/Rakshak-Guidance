/*************************************************************
 Title        : Rakshak - Smart Health Monitoring System (Test Phase 1)
 Description  : ESP32 + LM35 + Blynk (Testing Wi-Fi and temperature data)
*************************************************************/

// Blynk Template Info
#define BLYNK_TEMPLATE_ID "TMPL3b3NyGfOV"
#define BLYNK_TEMPLATE_NAME "Rakshak"
#define BLYNK_AUTH_TOKEN "LQzdFRFGOZtHbmxTiiUsAETfip9IVg50"

// Include necessary libraries
#include <BlynkSimpleEsp32.h>
#include <WiFi.h>
#include "main.h"
#include "lm35_system.h"
#include "max30102_system.h"
#include "gps_system.h"
//#include "gsm_system.h"
#include "emergency_button.h"

// Wi-Fi credentials
char ssid[] = "realme 9i 5G";
char pass[] = "prem2468";

// Create a Blynk timer object
BlynkTimer timer;

// Function to read and send temperature to Blynk
void sendToBlynk(float hr, float spo2) {
  Blynk.virtualWrite(HR_V_PIN, hr);
  Blynk.virtualWrite(SPO2_V_PIN, spo2);
}

void handle_emergency_button()
{
    if (is_emergency_pressed())
    {
        Serial.println("🚨 Emergency Button Pressed!");
        Blynk.virtualWrite(ALERT_V_PIN, ON);      // send ON signal
        Blynk.logEvent("emergency_alert", "🚨 Emergency button was pressed!");
        delay(3000);  // <-- give Blynk 1.5 sec to send update
        Blynk.virtualWrite(ALERT_V_PIN, OFF);
    }
}

// void check_alert_condition(float hr, float spo2, float temp)
// {
//     if ((hr > 110 || spo2 < 90 || temp > 38) && check_stable_readings(hr, spo2, temp)) {
//         String lat = get_latitude();
//         String lon = get_longitude();
//         String link = "https://www.google.com/maps?q=" + lat + "," + lon;

//         String alertMsg = "🚨 EMERGENCY ALERT 🚨\n"
//                           "Heart Rate: " + String(hr) + " bpm\n"
//                           "SpO2: " + String(spo2) + " %\n"
//                           "Temp: " + String(temp) + " °C\n"
//                           "Location: " + link;

//         gsm_sendSMS(ALERT_PHONE_NUMBER, alertMsg);
//         delay(1000);
//         gsm_makeCall(ALERT_PHONE_NUMBER);
//     }
// }

void sendGPS()
{
    String lat = get_latitude();
    String lon = get_longitude();
    float spd  = get_speed();

    Serial.println("-------- GPS Data --------");
    Serial.print("Latitude : "); Serial.println(lat);
    Serial.print("Longitude: "); Serial.println(lon);
    Serial.print("Speed    : "); Serial.print(spd); Serial.println(" km/h");
    Serial.println("--------------------------\n");

    // Send to Blynk (optional)
    Blynk.virtualWrite(GPS_LAT_V_PIN, lat);
    Blynk.virtualWrite(GPS_LON_V_PIN, lon);
    Blynk.virtualWrite(GPS_SPD_V_PIN, spd);
}

void sendTemperature()
{
    float temp = read_temperature();   // Read from LM35
    float hr = read_heart_rate();
    float spo2 = read_spo2();

    Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.println(" °C");

    if (hr > 0 && spo2 > 0) {
        Serial.print("Heart Rate: ");
        Serial.print(hr);
        Serial.println(" bpm");

        Serial.print("SpO2: ");
        Serial.print(spo2);
        Serial.println(" %");
    }

    Blynk.virtualWrite(TEMP_V_PIN, temp);
}

// Setup section
void setup()
{
  Serial.begin(115200);

  init_lm35_system();    // Initialize LM35 (defined in lm35_system.cpp)
  init_max30102_system();
  init_gps_system();
  //init_gsm_system();
  init_emergency_button_system();
  Serial.println("Rakshak system ready.");

  Serial.println("Connecting to Wi-Fi...");
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass); // Connect to Blynk cloud
  Serial.println("Connected to Wi-Fi and Blynk Cloud.");

  // Send data every 3 seconds
  timer.setInterval(3000, sendTemperature);
  timer.setInterval(3000, sendGPS);
}

// Main loop
void loop()
{
  Blynk.run();
  timer.run();
  process_max30102_data();
  handle_emergency_button();
  delay(50);
}
