#include "BTcom.h"
#include "Logging.h"



BTcom::BTcom()
{
}

void BTcom::begin()
{
    SerialBT.begin("Schwerpunktwage"); //Bluetooth device name
    _log("The device started, now you can pair it with bluetooth!");
    availible =false;
    SerialBT.flush();
}

void BTcom::execStr(String s)
{
    int pos = s.indexOf(":");
    if (pos == 0)
    {
        name = s;
        value = "";
    }
    else
    {   
        String name = s.substring(0, pos-1);
        String value = s.substring(pos + 1);
    }
    availible = true;
}

void BTcom::loop()
{
    char ch;
    if (SerialBT.available()) {
       ch = SerialBT.read();
       if (ch == '\n') {
        execStr(inString);
        inString ="";
       } else {
        inString.concat(ch);
       }
    }
}


void BTcom::send(String name, float f)
{
    send(name, String(f));
}

void BTcom::send(String name, byte b)
{
    send(name,String(b));
}

void BTcom::send(String name, String s)
{
    SerialBT.println(name + ":" +s);
}

boolean BTcom::isAvailible()
{
    return availible;
}

boolean BTcom::isConnected()
{
    return SerialBT.connected();
}

boolean  BTcom::readData(String *name, String *value)
{
    if (this->availible) {
    *name = this->name;
    *value = this->value;
    availible =false;
    } else return false;
    return true;
    
}
