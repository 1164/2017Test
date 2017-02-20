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

	LimitTop = new DigitalInput(constants->Get("LifterTopLimitIOPort"));
	LimitBottom = new DigitalInput(constants->Get("LifterBottomLimitIOPort"));
} // of RobotLift Constructor

void RobotLift::Set(double climb){
	if (LimitTop == 0 && LimitBottom == 0){
		LiftSC->Set(climb);
	}
}

