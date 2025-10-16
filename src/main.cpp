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

/*
#define FrontCell_DOUT_PIN 23
#define FrontCell_SCK_PIN  5

#define RearCell_DOUT_PIN 18
#define RearCell_SCK_PIN 19
*/

LoadHandle Cells;
BTcom Bt;

void setup() {
  _log_begin(115200);
  Bt.begin();
  Cells.begin();
}

void sendCoG() {
  Bt.send("CoG",Cells.CenterOfGravity);
  Bt.send("FrontWeight",Cells.FrontWeight);
  Bt.send("ReartWeight",Cells.RearWeight);
  Bt.send("totalWeight",Cells.totalWeight);
}

void sendConfig()
{
  Bt.send("FrontCellPinDout", Cells.FrontCell_DOUT_PIN);
  Bt.send("FrontCellPinSCK", Cells.FrontCell_SCK_PIN);
  Bt.send("RearCellPinDout", Cells.RearCell_DOUT_PIN);
  Bt.send("RearCellPinSCK", Cells.RearCell_SCK_PIN);
  Bt.send("distanceGPs", Cells.distanceGPs);
  Bt.send("distanceWingToGP", Cells.distanceWingToGP);
}

String getParameter(String *s) {
    String ls = *s;
    String rs;
    ls.substring(0,ls.indexOf(",")-1);
    rs = ls;
    ls.remove(0,ls.indexOf(","));
    *s = ls; 
    return ls;
}

void setConfig(String value) {
  _logf("setConfig %s \n", value);
  Cells.FrontCell_DOUT_PIN = getParameter(&value).toInt();
  Cells.FrontCell_SCK_PIN = getParameter(&value).toInt();
  Cells.RearCell_DOUT_PIN = getParameter(&value).toInt();
  Cells.RearCell_SCK_PIN = getParameter(&value).toInt();
  Cells.distanceGPs = getParameter(&value).toFloat();
  Cells.distanceWingToGP = getParameter(&value).toFloat();
}

void setData()
{
  String name;
  String value;
  if (Bt.readData(&name, &value))
  {
    if (name == "getConfig")
    {
      sendConfig();
      return;
    }
    if (name == "setConfig")
    {
      setConfig(value);
      return;
    }

  if (name == "ResetFrontCell")
    {
      Cells.resetFront();
      return;
    }
  if (name == "ResetRearCell")
    {
      Cells.resetRear();
      return;
    }

    if (name == "CalibrateFrontCell")
    {
      Cells.calibrateFront(value.toFloat());
      return;
    }

     if (name == "CalibrateRearCell")
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

  long looptime = millis();
  void loop()
  {

    if ((millis() - looptime > 5000) && Bt.isConnected())
    {
      Cells.loop();
      sendCoG();
      looptime = millis();
    }
    if (Bt.isAvailible())
      setData();
  }