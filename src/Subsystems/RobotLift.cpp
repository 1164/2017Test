/*
 * RobotLift.cpp
 *
 *  Created on: Feb 15, 2017
 *      Author: neoadmin
 */
#include "WPILib.h"
#include <Subsystems/RobotLift.h>


RobotLift::RobotLift(Constant *Sarah) :
Subsystem("RobbotLift")
{
	constants = Sarah;
	LiftSC = new VictorSP(constants->Get("RobotLifterMotor")); //PWM Channel
	LiftSC->SetInverted(constants->Get("RobotLifterInverted")== 1);

	LimitTop = new DigitalInput(constants->Get("LifterTopLimitIOPort"));
	LimitBottom = new DigitalInput(constants->Get("LifterBottomLimitIOPort"));
} // of RobotLift Constructor

void RobotLift::Set(double climb){
	if (climb > 0.05 && LimitTop->Get()){
		LiftSC->Set(climb);
	}
	else if(climb < -0.05 && LimitBottom->Get()){
		LiftSC->Set(climb);
	}
	else{
		LiftSC->Set(0.0);
	}
}

