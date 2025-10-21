#include "BTcom.h"
#include "Logging.h"

BTcom::BTcom()
{
}

void BTcom::begin()
{
    SerialBT.begin("CoG"); // Bluetooth device name
    _log("The device started, now you can pair it with bluetooth!");
    availible = false;
    SerialBT.flush();
}

void BTcom::execStr(String s)
{
    int pos = s.indexOf(":");
    if (pos == -1)
    {
        name = s;
        value = "";
    }
    else
    {
        this->name = s.substring(0, pos);
        this->value = s.substring(pos + 1);
    }

    _logf("Resived Name: %s | Value: %s \n", name.c_str(), value.c_str());
    availible = true;
}

void BTcom::loop()
{
    char ch;
    if (SerialBT.available())
    {
        ch = SerialBT.read();
        if (ch == '\n')
        {
            execStr(inString);
            inString = "";
        }
        else
        {
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
    send(name, String(b));
}

void BTcom::send(String name, String s)
{
    SerialBT.println(name + ":" + s);
}

boolean BTcom::isAvailible()
{
    return availible;
}

boolean BTcom::isConnected()
{
    return SerialBT.connected();
}

boolean BTcom::readData(String *name, String *value)
{
    if (this->availible)
    {
        *name = this->name;
        *value = this->value;
        availible = false;
    }
    else
        return false;
    return true;
}
