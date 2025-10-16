#include "LoadHandle.h"
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
#include <EEPROM.h>
#include "Logging.h"

#define FrontCell_DOUT_PIN_POS 1
#define FrontCell_SCK_PIN_POS 2
#define RearCell_DOUT_PIN_POS 3
#define RearCell_SCK_PIN_POS 4
#define FrontCell_scale_POS 5  // float 
#define RearCell_scale_POS 9   // float

#define EEPROM_SIZE 32

#define unitReadingTimes 5

LoadHandle::LoadHandle()
{
    EEPROM.begin(EEPROM_SIZE);
}

void LoadHandle::begin()
{
    FrontCell_DOUT_PIN=EEPROM.readByte(FrontCell_DOUT_PIN_POS);
    FrontCell_SCK_PIN=EEPROM.readByte(FrontCell_SCK_PIN_POS);
    RearCell_DOUT_PIN=EEPROM.readByte(RearCell_DOUT_PIN_POS);
    RearCell_SCK_PIN=EEPROM.readByte(RearCell_SCK_PIN_POS);
    FrontCell_scale=EEPROM.readFloat(FrontCell_scale_POS);
    if (FrontCell_scale == 0.0f) FrontCell_scale=1.0f;
    RearCell_scale=EEPROM.readFloat(RearCell_scale_POS);
    if (RearCell_scale == 0.0f) RearCell_scale=1.0f;
    resetCells();
}

void LoadHandle::loop()
{
    this->FrontWeight = FrontCell.get_units(unitReadingTimes);
    this->RearWeight = RearCell.get_units(unitReadingTimes);
    this->totalWeight = this->FrontWeight + this->RearWeight;
    this->CenterOfGravity = ((distanceGPs*RearWeight)/totalWeight) + distanceWingToGP;
}

void LoadHandle::resetFront()
{
    FrontCell.set_scale();
    FrontCell.tare();
    this->FrontCell_scaleZ=FrontCell.get_units(10);
}

void LoadHandle::calibrateFront(float weight)
{
    FrontCell_scale = FrontCell_scaleZ/FrontCell.get_units(10);
    EEPROM.writeFloat(FrontCell_scale_POS,FrontCell_scale);
    FrontCell.set_scale(FrontCell_scale);

}

void LoadHandle::resetRear()
{
    RearCell.set_scale();
    RearCell.tare();
    this->RearCell_scaleZ=RearCell.get_units(10);
}

void LoadHandle::calibrateRear(float weight)
{
    RearCell_scale = RearCell_scaleZ/RearCell.get_units(10);
    EEPROM.writeFloat(RearCell_scale_POS,RearCell_scale);
    FrontCell.set_scale(RearCell_scale);

}

void LoadHandle::setCellPins(byte FrontCell_DOUT_PIN, byte FrontCell_SCK_PIN, 
                             byte RearCell_DOUT_PIN, byte RearCell_SCK_PIN)
{
    FrontCell_DOUT_PIN=FrontCell_DOUT_PIN; EEPROM.writeByte(FrontCell_DOUT_PIN_POS,FrontCell_DOUT_PIN);
    FrontCell_SCK_PIN=FrontCell_SCK_PIN; EEPROM.writeByte(FrontCell_SCK_PIN_POS,FrontCell_SCK_PIN);
    RearCell_DOUT_PIN=RearCell_DOUT_PIN; EEPROM.writeByte(RearCell_DOUT_PIN_POS,RearCell_DOUT_PIN);
    RearCell_SCK_PIN=RearCell_SCK_PIN; EEPROM.writeByte(RearCell_SCK_PIN_POS,RearCell_SCK_PIN);
    resetCells();
}


void LoadHandle::resetCells()
{   
    FrontCell.begin(FrontCell_DOUT_PIN, FrontCell_SCK_PIN);
    RearCell.begin(RearCell_DOUT_PIN,RearCell_SCK_PIN);
 
    if (FrontCell.is_ready())
    {
        _log("load Frontcell: set_scale, tare");
        FrontCell.set_scale(FrontCell_scale);
        FrontCell.tare();
    }
    else
    {
        _log("loding FrontCell not ready!");
    }
    if (RearCell.is_ready())
    {
        _log("load Frontcell: set_scale, tare");
        RearCell.set_scale(RearCell_scale);
        RearCell.tare();
    }
    else
    {
        _log("loding FrontCell not ready!");
    }
}

void LoadHandle::setDistance(float distanceGPs, float distanceWingToGP)
{
    this->distanceGPs=distanceGPs;
    this->distanceWingToGP=distanceWingToGP;
}



