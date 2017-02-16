/*
 * FuelMovement.cpp
 *
 *  Created on: Feb 15, 2017
 *      Author: neoadmin
 */

#include "WPILib.h"
#include <Subsystems/FuelMovement.h>


FuelMovement::FuelMovement(Constant *Amy) :
Subsystem("FuelMovement")
{
	constants = Amy;
	FuelMovementSC = new VictorSP(constants->Get("FuelMovementMotor")); //PWM Channel

} // of FuelMovement Constructor





