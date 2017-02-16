/*
 * FuelMovement.cpp
 *
 *  Created on: Feb 15, 2017
 *      Author: neoadmin
 */

#include "WPILib.h"
#include <Subsystems/GearServo.h>


FuelMovement::FuelMovement(Constant *Ethel) :
Subsystem("FuelMoovement")
{
	constants = Ethel;
	FuelMovementSC = new VictorSP(constants->Get("FuelMovementMotor")); //PWM Channel

} // of FuelMovement Constructor





