/*
Config.h - Include file for class "Config".
Copyright (C) 2023  by Stefan Andres

This program is free software,   // you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https,   ////www.gnu.org/licenses/>.
*/
#ifndef CONFIG_H_
#define CONFIG_H_

#include <Arduino.h>
#include <FS.h>
#include <LittleFS.h>

class Config_
{
private:
    Config_() = default;

    void setVariable(String str);
    void genString(char *str,const char * name,const char * value);
    void genStringInt(char *str,const char * name, int value);

public:
    char _WiFiSSID[32];
    char _wifiPassword[32];
    char _mqttServer[32];
    char _mqttID[32];
    char _mqttUser[32];
    char _mqttPassword[32];
    long _updateRate;

    static Config_ &getInstance();     // Accessor for singleton instance
    Config_(const Config_ &) = delete; // no copying
    Config_ &operator=(const Config_ &) = delete;

    void begin();

    // Config Variable
    boolean readConfig();
    boolean writeConfig();

    void setWiFiSSID(const char *ssid);
    void getWifiSSID(char *ssid);
    String getWifiSSID();

    void setWiFiPassword(const char *password);
    void getWiFiPassword(char *password);
    String getWifiPassword();

    void setMqttID(const char *id);
    void getMqttID(char *id);
    String getMqttID();

    void setMqttServer(const char *name);
    void getMqttServer(char *name);
    String getMqttServer();

    void setMqttUser(const char *user);
    void getMqttUser(char *user);
    String getMqttUser();

    void setMqttPassword(const char *password);
    void getMqttPassword(char *password);
    String getMqttPassword();

    void setUpdateRate(uint16_t seconds);
    String getUpdateRate();
};

extern Config_ &Config;
#endif