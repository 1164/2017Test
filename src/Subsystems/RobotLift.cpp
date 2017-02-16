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

} // of RobotLift Constructor



