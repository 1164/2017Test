/*
 * FuelMovement.cpp
 *
 *  Created on: Feb 15, 2017
 *      Author: neoadmin
 */

#include "WPILib.h"
#include <Subsystems/FuelMovement.h>
#include <Joystick.h>


FuelMovement::FuelMovement(Constant *Amy) :
Subsystem("FuelMovement")
{
	constants = Amy;
	FuelMovementSC = new VictorSP(constants->Get("FuelMovementMotor")); //PWM Channel
}

void FuelMovement::Roller(bool RollerOn, bool RollerOff){

	if (RollerOn){
		FuelMovementSC->Set(1.0);
	}
	else if (RollerOff){
		FuelMovementSC->Set(0.0);
	}

} // of FuelMovement Constructor





