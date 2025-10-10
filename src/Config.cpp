#include "Config.h"

// #define _LOGGING_OFF  // uncomment for disable logging in this file
#include "Logging.h"

#define _dataFileName "/config.txt"



Config_ &Config_::getInstance()
{
    static Config_ instance;
    return instance;
}

Config_ &Config = Config.getInstance();

void Config_::genString(char *str,const char * name,const char * value)
{    
    strcpy(str,name);
    strcat(str,"=");
    strcat(str,value);
}

void Config_::genStringInt(char *str,const char * name, int value)
{    
    strcpy(str,name);
    strcat(str,"=");
    char val[16];
    itoa(value,val,10);
    strcat(str,val);
}

boolean Config_::writeConfig()
{
    char str[32];
    boolean ret;

    File file = LittleFS.open(_dataFileName,FILE_WRITE);
    if (file) {
        genString(str,"WiFiSSID",_WiFiSSID); file.println(str);
        genString(str,"WiFiPassword",_wifiPassword); file.println(str);
        genString(str,"MQTTServer",_mqttServer); file.println(str);
        genString(str,"MQTTID",_mqttID); file.println(str);
        genString(str,"MQTTUser",_mqttUser); file.println(str);
        genString(str,"MQTTPassword",_mqttPassword); file.println(str);
        genStringInt(str,"updateRate",_updateRate/1000); file.println(str);        
    } else ret=false;
    file.close();
    return ret;
  return boolean();
}

void Config_::setWiFiSSID(const char *ssid)
{
    strcpy(_WiFiSSID, ssid);
}

void Config_::getWifiSSID(char *ssid)
{
    strcpy(ssid,_WiFiSSID);
}

String Config_::getWifiSSID()
{
  return String(_WiFiSSID);
}

void Config_::setWiFiPassword(const char *password)
{
    strcpy(_wifiPassword,password);
}

void Config_::getWiFiPassword(char *password)
{
    strcpy(password,_wifiPassword);
}

String Config_::getWifiPassword()
{
  return String(_wifiPassword);
}

void Config_::setMqttID(const char *id)
{
    strcpy(_mqttID,id);
}

void Config_::getMqttID(char *id)
{
    strcpy(id,_mqttID);
}

String Config_::getMqttID()
{
    return String(_mqttID);
}

void Config_::setMqttServer(const char *name)
{
    strcpy(_mqttServer,name);
}

void Config_::getMqttServer(char *name)
{
    strcpy(name,_mqttServer);
}

String Config_::getMqttServer()
{
    return String(_mqttServer);
}

void Config_::setMqttUser(const char *user)
{
    strcpy(_mqttUser,user);
}

void Config_::getMqttUser(char *user)
{
    strcpy(user,_mqttUser);
}

String Config_::getMqttUser()
{
    return String(_mqttUser);
}

void Config_::setMqttPassword(const char *password)
{
    strcpy(_mqttPassword,password);
}

void Config_::getMqttPassword(char *password)
{
    strcpy(password,_mqttPassword);
}

String Config_::getMqttPassword()
{
    return String(_mqttPassword);
}

void Config_::setUpdateRate(uint16_t seconds)
{
    _updateRate = seconds;
}

String Config_::getUpdateRate()
{
    return String(_updateRate/1000);
}

void Config_::setVariable(String str)
{
    String name,var;
    size_t pos;
    _logf("Config: %s\n",str.c_str());
    pos = str.indexOf("=");  
    name = str.substring(0,pos);
    var =  str.substring(pos+1);
    if (name.equals("WiFiSSID")) {var.toCharArray(_WiFiSSID,32); return; }
    if (name.equals("WiFiPassword")) {var.toCharArray(_wifiPassword,32); return; }
    if (name.equals("MQTTServer")) {var.toCharArray(_mqttServer,32); return; }
    if (name.equals("MQTTID")) {var.toCharArray(_mqttID,32); return; }
    if (name.equals("MQTTUser")) {var.toCharArray(_mqttUser,32); return; }
    if (name.equals("MQTTPassword")) {var.toCharArray(_mqttPassword,32); return; }
    if (name.equals("updateRate")) {_updateRate=((long)strtol(var.c_str(),0,10))*1000; return; }
}

boolean Config_::readConfig()
{
    String str;
    boolean ret;
    _log("Config try to open File");
    File file = LittleFS.open(_dataFileName,FILE_READ);
    if (file) {
        _log("Config File opend");
        while(file.available()) {
            str = file.readStringUntil('\n');
            str.replace(" ","");
            str.replace(" ","\r");
            if (str.startsWith("#")) continue;
            if (str.length() == 0) continue;
            setVariable(str);
        }
        ret=true;
        
    } else {
        ret=false;
        _log("Config File can't open!!!");}
    file.close();
    return ret;
}




