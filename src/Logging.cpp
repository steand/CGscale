#include <Arduino.h>

void __log_time() {
   long t = millis();
   Serial.printf("%02lu:%02lu:%02lu.%03lu ",t/ 3600000, (t % 3600000)/60000, (t % 60000) / 1000,t % 1000);
 }
