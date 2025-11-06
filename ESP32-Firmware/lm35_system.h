#ifndef LM35_SYSTEM_H
#define LM35_SYSTEM_H

#define LM35_SENSOR_PIN 34  // ESP32 analog pin connected to LM35

void init_lm35_system(void);
float read_temperature(void);

#endif
