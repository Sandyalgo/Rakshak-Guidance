#ifndef GPS_SYSTEM_H
#define GPS_SYSTEM_H

#include <Arduino.h>

void init_gps_system(void);
String get_latitude(void);
String get_longitude(void);
float get_speed(void);

#endif
