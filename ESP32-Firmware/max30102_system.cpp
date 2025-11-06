#include <Wire.h>
#include "MAX30105.h"
#include "spo2_algorithm.h"
#include "heartRate.h"
#include "max30102_system.h"
#include "main.h"

extern void sendToBlynk(float hr, float spo2);  // From Rakshak.ino

MAX30105 particleSensor;

#define FINGER_DETECT_THRESHOLD 5000

// Buffers for samples
uint32_t irBuffer[100];
uint32_t redBuffer[100];
const int bufferLength = 100;

// Algorithm results
int32_t spo2;
int8_t validSPO2;
int32_t heartRate;
int8_t validHeartRate;

// Filtered/smoothed values
float smoothHR = 0;
float smoothSpO2 = 0;

// States
bool fingerPresent = false;
unsigned long lastUpdate = 0;

void init_max30102_system(void)
{
    Wire.begin();
    Serial.println("Initializing MAX30102 Sensor...");

    if (!particleSensor.begin(Wire, I2C_SPEED_STANDARD))
    {
        Serial.println("❌ MAX30102 not found. Check wiring!");
        while (1);
    }

    byte ledBrightness = 60;  // power setting
    byte sampleAverage = 4;
    byte ledMode = 2;         // Red + IR
    byte sampleRate = 100;    // 100 samples/sec
    int pulseWidth = 215;
    int adcRange = 16384;

    particleSensor.setup(ledBrightness, sampleAverage, ledMode, sampleRate, pulseWidth, adcRange);
    particleSensor.setPulseAmplitudeRed(0x3C);
    particleSensor.setPulseAmplitudeIR(0x3C);

    Serial.println("✅ MAX30102 Sensor initialized successfully.");
}

void process_max30102_data(void)
{
    long irValue = particleSensor.getIR();

    // --- Finger detection ---
    if (irValue < FINGER_DETECT_THRESHOLD)
    {
        if (fingerPresent)
        {
            Serial.println("⚠ Finger removed.");
            fingerPresent = false;
            // Fallback to normal resting values
            smoothHR = 75.0;
            smoothSpO2 = 98.0;
            sendToBlynk(smoothHR, smoothSpO2);
        }
        return;
    }

    if (!fingerPresent)
    {
        Serial.println("🟢 Finger detected — starting real-time readings...");
        fingerPresent = true;
        delay(1000); // let signal stabilize
    }

    // --- Collect samples ---
    for (byte i = 0; i < bufferLength; i++)
    {
        while (!particleSensor.check()) { delay(1); }
        redBuffer[i] = particleSensor.getRed();
        irBuffer[i]  = particleSensor.getIR();
    }

    // --- Run HR & SpO2 algorithm ---
    maxim_heart_rate_and_oxygen_saturation(
        irBuffer, bufferLength, redBuffer,
        &spo2, &validSPO2, &heartRate, &validHeartRate
    );

    // --- Data validation ---
    if (validHeartRate && heartRate > 40 && heartRate < 160)
    {
        // Smooth sudden changes using weighted average
        smoothHR = (0.7 * smoothHR) + (0.3 * heartRate);
    }

    if (validSPO2 && spo2 > 70 && spo2 <= 100)
    {
        smoothSpO2 = (0.7 * smoothSpO2) + (0.3 * spo2);
    }

    // --- Print smoothed data ---
    Serial.print("❤️ Heart Rate: ");
    Serial.print(smoothHR, 1);
    Serial.print(" bpm | 🩸 SpO2: ");
    Serial.print(smoothSpO2, 1);
    Serial.println(" %");

    // --- Send to Blynk (1 sec interval) ---
    if (millis() - lastUpdate > 1000)
    {
        sendToBlynk(smoothHR, smoothSpO2);
        lastUpdate = millis();
    }
}

float read_heart_rate(void)
{
    return smoothHR;
}

float read_spo2(void)
{
    return smoothSpO2;
}
