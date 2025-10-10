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
#ifndef LOADHANDLE_H_
#define LOADHANDLE_H_

#include <Arduino.h>
#include "HX711.h"

class LoadHandle {

    public:
     LoadHandle(byte FrontCell_DOUT_PIN, byte FrontCell_SCK_PIN,byte RearCell_DOUT_PIN, byte RearCell_SCK_PIN );
     void begin(float scaleFront, float scaleRear);
     boolean resetFront();                // Reset for Calibrate
     float calibrateFront(float weight);  // return factor 
     boolean resetFront();               // Reset for Calibrate
     float calibrateRear(float weight);  // return factor
     boolean setTare();
     boolean getCG(float cg, float weight, float weightFront, float weightRear);

};


#endif