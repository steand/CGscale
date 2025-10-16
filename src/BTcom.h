/*
Config.h - Include file for class "Config".
Copyright (C) 2025  by Stefan Andres

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
#ifndef BTCOM_H_
#define BTCOM_H_

#include <Arduino.h>
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif




class BTcom
{
 private:
  BluetoothSerial SerialBT;
  String inString;
  String name;
  String value;
  boolean availible;

  void execStr(String s);
 public:
  BTcom();
  void begin();
  void loop();
  void send(String name, float f);
  void send(String name, byte b);
  void send(String name, String s);
  boolean isAvailible();
  boolean isConnected();
  boolean readData(String *name, String *value);
};

#endif
