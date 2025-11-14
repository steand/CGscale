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

#define FrontCell_DOUT_PIN 23
#define FrontCell_SCK_PIN 5

#define RearCell_DOUT_PIN 18
#define RearCell_SCK_PIN 19

#define FrontCell_scale_POS 1   // float
#define RearCell_scale_POS 5    // float
#define distanceGPs_POS 9       // float
#define distanceWingToGP_POS 13 // float
#define EEPROM_SIZE 32

#define unitReadingTimes 5

LoadHandle::LoadHandle() {}

void LoadHandle::begin()
{
    if (EEPROM.begin(64))
    {
        _log("EEPROM startet.");
    }
    else
    {
        _log("EEPROM init fail");
    }
    FrontCell_scale = EEPROM.readFloat(FrontCell_scale_POS);
    if (isnan(FrontCell_scale))
        FrontCell_scale = 1.0F;
    RearCell_scale = EEPROM.readFloat(RearCell_scale_POS);
    if (isnan(RearCell_scale))
        RearCell_scale = 1.0F;
    distanceGPs = EEPROM.readFloat(distanceGPs_POS);
    if (isnan(distanceGPs))
        distanceGPs = 180.0F;
    distanceWingToGP = EEPROM.readFloat(distanceWingToGP_POS);
    if (isnan(distanceWingToGP))
        distanceWingToGP = 30.0F;
    _log(distanceWingToGP);

    FrontCell.begin(FrontCell_DOUT_PIN, FrontCell_SCK_PIN);
    RearCell.begin(RearCell_DOUT_PIN, RearCell_SCK_PIN);

    resetCells();
}

void LoadHandle::loop()
{
    this->FrontWeight = FrontCell.get_units(unitReadingTimes);
    this->RearWeight = RearCell.get_units(unitReadingTimes);
    this->totalWeight = this->FrontWeight + this->RearWeight;
    _logf("CoG in loop  FW : %f RW %f tW %f CoG: %f \n", FrontWeight, RearWeight, totalWeight, CenterOfGravity );
    if (this->totalWeight > 0)
        this->CenterOfGravity = ((distanceGPs * RearWeight) / totalWeight) + distanceWingToGP;
    else
        this->CenterOfGravity = 0.0F;
    _logf("CoG in loop  FW : %f RW %f tW %f CoG: %f \n", FrontWeight, RearWeight, totalWeight, CenterOfGravity );
    _logf("             distGP %f, distWing %f \n",distanceGPs,distanceWingToGP);
}

void LoadHandle::resetFront()
{
    FrontCell.set_scale();
    FrontCell.tare();
    this->FrontCell_scaleZ = FrontCell.get_units(10);
}

void LoadHandle::calibrateFront(float weight)
{
    float f = FrontCell.get_units(10);
    FrontCell_scale = f/weight;
    EEPROM.writeFloat(FrontCell_scale_POS, FrontCell_scale);
    EEPROM.commit();
    FrontCell.set_scale(FrontCell_scale);
    _logf("Front Calib. scaleZ: %f unit: %f scale: %f \n",FrontCell_scale, f, FrontCell_scale );
}

void LoadHandle::resetRear()
{
    RearCell.set_scale();
    RearCell.tare();
    this->RearCell_scaleZ = RearCell.get_units(10);
}

void LoadHandle::calibrateRear(float weight)
{
    RearCell_scale = RearCell.get_units(10)/weight;
    EEPROM.writeFloat(RearCell_scale_POS, RearCell_scale);
    EEPROM.commit();
    FrontCell.set_scale(RearCell_scale);
}

void LoadHandle::resetCells()
{

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
    this->distanceGPs = distanceGPs;
    EEPROM.writeFloat(distanceGPs_POS, distanceGPs);
    this->distanceWingToGP = distanceWingToGP;
    EEPROM.writeFloat(distanceWingToGP_POS, distanceWingToGP);
    EEPROM.commit();
}
