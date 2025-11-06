#ifndef GSM_SYSTEM_H
#define GSM_SYSTEM_H

#include <Arduino.h>
#include <HardwareSerial.h>

#define GSM_RX 26   // ESP32 RX (connect to SIM800 TX)
#define GSM_TX 27   // ESP32 TX (connect to SIM800 RX)

void init_gsm_system(void);
void gsm_sendSMS(String phoneNumber, String message);
void gsm_makeCall(String phoneNumber);
bool check_stable_readings(float hr, float spo2, float temp);

#endif
