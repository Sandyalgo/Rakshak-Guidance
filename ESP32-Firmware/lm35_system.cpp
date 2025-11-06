#include "lm35_system.h"
#include "Arduino.h"

float temperature;

void init_lm35_system(void)
{
    pinMode(LM35_SENSOR_PIN, INPUT);
}

float read_temperature(void)
{
    int adcValue = analogRead(LM35_SENSOR_PIN);
    // ESP32: 12-bit ADC (0–4095), 3.3V reference
    float voltage = (adcValue * 3.3) / 4095.0;
    temperature = voltage * 100.0;  // 10mV per °C
    return temperature;
}
