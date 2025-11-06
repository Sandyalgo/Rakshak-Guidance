#include "gsm_system.h"

// Use UART1 for GSM communication
HardwareSerial gsmSerial(1);

#define GSM_BAUDRATE 9600
#define READINGS_COUNT 10

// Buffers for checking stable readings
float hrBuffer[READINGS_COUNT];
float spo2Buffer[READINGS_COUNT];
float tempBuffer[READINGS_COUNT];
int indexCount = 0;
bool bufferFilled = false;

// --- Initialize GSM ---
void init_gsm_system(void)
{
    Serial.println("Initializing GSM Module...");
    gsmSerial.begin(GSM_BAUDRATE, SERIAL_8N1, GSM_RX, GSM_TX);
    delay(2000);

    gsmSerial.println("AT");
    delay(1000);

    if (gsmSerial.available())
        Serial.write(gsmSerial.read());

    gsmSerial.println("ATE0"); // Disable echo
    delay(500);
    gsmSerial.println("AT+CMGF=1"); // Set SMS to text mode
    delay(500);

    Serial.println("GSM Module Initialized Successfully!");
}

// --- Send SMS ---
void gsm_sendSMS(String phoneNumber, String message)
{
    Serial.println("Sending SMS Alert...");
    gsmSerial.println("AT+CMGF=1");  // Text mode
    delay(1000);
    gsmSerial.print("AT+CMGS=\"");
    gsmSerial.print(phoneNumber);
    gsmSerial.println("\"");
    delay(1000);
    gsmSerial.print(message);
    delay(500);
    gsmSerial.write(26);  // CTRL+Z
    delay(5000);

    Serial.println("SMS Sent!");
}

// --- Make Call ---
void gsm_makeCall(String phoneNumber)
{
    Serial.println("Dialing Emergency Call...");
    gsmSerial.print("ATD");
    gsmSerial.print(phoneNumber);
    gsmSerial.println(";");
    delay(15000);  // 15 seconds call
    gsmSerial.println("ATH"); // Hang up
    Serial.println("Call Ended.");
}

// --- Stability Check (avoid false alarms) ---
bool check_stable_readings(float hr, float spo2, float temp)
{
    // Store readings in circular buffer
    hrBuffer[indexCount] = hr;
    spo2Buffer[indexCount] = spo2;
    tempBuffer[indexCount] = temp;
    indexCount++;

    if (indexCount >= READINGS_COUNT) {
        indexCount = 0;
        bufferFilled = true;
    }

    // Wait until 10 readings collected
    if (!bufferFilled)
        return false;

    // Calculate average
    float avgHR = 0, avgSPO2 = 0, avgTemp = 0;
    for (int i = 0; i < READINGS_COUNT; i++) {
        avgHR += hrBuffer[i];
        avgSPO2 += spo2Buffer[i];
        avgTemp += tempBuffer[i];
    }
    avgHR /= READINGS_COUNT;
    avgSPO2 /= READINGS_COUNT;
    avgTemp /= READINGS_COUNT;

    // Check if all readings are close to average (within tolerance)
    float hrTol = 0, spo2Tol = 0, tempTol = 0;
    for (int i = 0; i < READINGS_COUNT; i++) {
        hrTol += abs(hrBuffer[i] - avgHR);
        spo2Tol += abs(spo2Buffer[i] - avgSPO2);
        tempTol += abs(tempBuffer[i] - avgTemp);
    }

    hrTol /= READINGS_COUNT;
    spo2Tol /= READINGS_COUNT;
    tempTol /= READINGS_COUNT;

    // If readings stable (variation within tolerance)
    if (hrTol < 5 && spo2Tol < 2 && tempTol < 0.5)
        return true;

    return false;
}
