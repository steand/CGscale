#include "BTcom.h"
#include "Logging.h"

BTcom::BTcom()
{
}

void BTcom::begin()
{
    SerialBT.begin("Schwerpunktwage"); //Bluetooth device name
    _log("The device started, now you can pair it with bluetooth!");
}

void BTcom::send(String name, float f)
{
    String s="#" + name + ":" + String(f) + "\n";
    for (int i=0;i<s.length();i++) {
        if (Serial.available()) {
            SerialBT.write(s[i]);
    }
  }
}

void BTcom::sendHX711Voltage(float voltage)
{
 send("HX711Voltage",voltage);
}
