/*
LoadHandle.h - Include file for class "LoadHandle".
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

class LoadHandle
{

public:
    LoadHandle();
    void begin(); // take parameter from EEPROM
    void setCellPins(byte FrontCell_DOUT_PIN, byte FrontCell_SCK_PIN, 
                     byte RearCell_DOUT_PIN, byte RearCell_SCK_PIN); // + set parameter to  EEPROM
    void resetCells();

    void loop();

    void resetFront();               // Reset for calibrating
    void calibrateFront(float weight); // Set factor to EEPROM & return factor
    void resetRear();                // Reset for calibrating
    void calibrateRear(float weight);  // Set factor to EEPROM & return factor

    // getter & setter functions

    void setDistance(float distanceGPs,float distanceWingToGP);
    
    byte FrontCell_DOUT_PIN;
    byte FrontCell_SCK_PIN;
    byte RearCell_DOUT_PIN;
    byte RearCell_SCK_PIN;
    float distanceGPs; 
    float distanceWingToGP;
    float FrontCell_scale;
    float RearCell_scale;

    float CenterOfGravity;
    float FrontWeight;
    float RearWeight;
    float totalWeight;
    

private: 
    
    HX711 FrontCell;
    HX711 RearCell;
    float FrontCell_scaleZ;
    float RearCell_scaleZ;

   
    
};

#endif