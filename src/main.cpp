#include <Arduino.h>

// #define _LOGGING_OFF

#include "Logging.h"
#include "BTcom.h"
#include "HX711.h"

#define voltagePin 34
#define ADC_Div 200f

#define FrontCell_DOUT_PIN 23
#define FrontCell_SCK_PIN  5

#define RearCell_DOUT_PIN 18
#define RearCell_SCK_PIN 19


HX711 scale;

BTcom btCom;

void setup() {
  _log_begin(115200);
  btCom.begin();
  scale.begin(FrontCell_DOUT_PIN, FrontCell_SCK_PIN);
  _log("Set Scale");
  scale.set_scale(436.34);
  _log("Set Tare");
  scale.tare();
   _logf("Get Unit %ld \n",scale.get_units(5));

}

long looptime = millis();
void loop() {
  
  if (millis() - looptime > 5000) {
   if (scale.is_ready()) {
    _logf("HX711 reading read: %ld | average: %ld | value: %d | unit: %f \n",scale.read(),scale.read_average(20),scale.get_value(5), scale.get_units(5));
   
  } else {
    _log("HX711 not found.");
  }
    looptime = millis();
  }

  delay(20);
}