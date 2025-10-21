/*
main.cpp
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
#include <Arduino.h>

// #define _LOGGING_OFF

#include "Logging.h"
#include "LoadHandle.h"
#include "BTcom.h"

LoadHandle Cells;
BTcom Bt;

void sendCoG()
{
  String s = String(Cells.FrontWeight, 0) + "," + String(Cells.RearWeight, 0) + "," +
             String(Cells.totalWeight, 0) + "," + String(Cells.CenterOfGravity, 1);
  Bt.send("CoG", s);
}

void sendConfig()
{
  String s = String(Cells.distanceGPs, 1) + "," +
             String(Cells.distanceWingToGP, 1);
  _logf("Send config %s \n", s.c_str());
  Bt.send("config", s);
}

String getParameter(String *inStr)
{
  String s;
  int pos = inStr->indexOf(',');
  if (pos >= 0)
  {
    s = inStr->substring(0, pos);
    inStr->remove(0, pos + 1);
  }
  else
  {
    s = *inStr;
  }
  return s;
}

void setDistance(String value)
{
  _logf("setDistance: %s \n", value.c_str());
  float distanceGPs = getParameter(&value).toFloat();
  float distanceWingToGP = getParameter(&value).toFloat();
  Cells.setDistance(distanceGPs, distanceWingToGP);
}

void setData()
{
  String name;
  String value;
  _log("Set Data");
  if (Bt.readData(&name, &value))
  {
    _logf("Read Data Name: %s | Value: %s \n", name.c_str(), value.c_str());
    if (name == "getConfig")
    {

      sendConfig();
      return;
    }
    if (name == "setDistance")
    {
      setDistance(value);
      return;
    }

    if (name == "resetFrontCell")
    {
      Cells.resetFront();
      return;
    }
    if (name == "resetRearCell")
    {
      Cells.resetRear();
      return;
    }

    if (name == "calibrateFrontCell")
    {
      Cells.calibrateFront(value.toFloat());
      return;
    }

    if (name == "calibrateRearCell")
    {
      Cells.calibrateRear(value.toFloat());
      return;
    }

    if (name == "reset")
    {
      Cells.resetCells();
      return;
    }
  }
}

void setup()
{
  delay(10000);
  _log_begin(115200);
  Bt.begin();
  Cells.begin();
  _log("main setup finished");
}

long looptime = millis();
void loop()
{

  if ((millis() - looptime > 5000))
  {
    if (Bt.isConnected())
    {
      _log("Main loop");
      Cells.loop();
      sendCoG();
    }
    else
    {
      _log("Main loop - BT disconect ");
    }
    looptime = millis();
  }
  Bt.loop();
  if (Bt.isAvailible())
    setData();
}