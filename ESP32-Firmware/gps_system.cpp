#include "gps_system.h"
#include <TinyGPSPlus.h>
#include <HardwareSerial.h>

HardwareSerial gpsSerial(2);
TinyGPSPlus gps;

String latitude  = "";
String longitude = "";
String lastLatitude  = "";
String lastLongitude = "";
float speed_kmph = 0.0;

// --- Default fallback coordinates (your area) ---
#define DEFAULT_LAT "17.457441"
#define DEFAULT_LON "78.668360"
#define DEFAULT_SPD 0.13

void init_gps_system() {
  Serial.println("Initializing GPS...");
  gpsSerial.begin(9600, SERIAL_8N1, 16, 17);  // RX=16, TX=17
  delay(2000);
  Serial.println("GPS ready. Waiting for satellite fix...");
}

void read_gps_data() {
  while (gpsSerial.available())
    gps.encode(gpsSerial.read());

  if (gps.location.isValid()) {
    latitude  = String(gps.location.lat(), 6);
    longitude = String(gps.location.lng(), 6);
    lastLatitude  = latitude;
    lastLongitude = longitude;
  }
  else if (!lastLatitude.isEmpty() && !lastLongitude.isEmpty()) {
    // Use last valid location
    latitude  = lastLatitude;
    longitude = lastLongitude;
  }
  else {
    // GPS not connected or no valid fix yet → use defaults
    latitude  = DEFAULT_LAT;
    longitude = DEFAULT_LON;
  }

  // Speed validation
  if (gps.speed.isValid())
    speed_kmph = gps.speed.kmph();
  else
    speed_kmph = DEFAULT_SPD;
}

String get_latitude()  { read_gps_data(); return latitude; }
String get_longitude() { read_gps_data(); return longitude; }
float  get_speed()     { read_gps_data(); return speed_kmph; }
