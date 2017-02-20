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
	FuelMovementSC->SetInverted(constants->Get("FuelMovementInverted")== 1);
}

void FuelMovement::Roller(bool RollerOn, bool RollerOff, bool BackButton){

	if (RollerOn){
		FuelMovementSC->Set(1.0);
	}
	else if (RollerOff){
		FuelMovementSC->Set(0.0);
	}
	else if (BackButton){
		FuelMovementSC->Set(-1.0);
	}

} // of FuelMovement Constructor





