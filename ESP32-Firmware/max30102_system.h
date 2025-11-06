#ifndef MAX30102_SYSTEM_H
#define MAX30102_SYSTEM_H

#include <Arduino.h>

// Function declarations
void init_max30102_system(void);
void process_max30102_data(void);
float read_heart_rate(void);
float read_spo2(void);

#endif