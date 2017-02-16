/*
 * GearServo.cpp
 *
 *  Created on: Feb 15, 2017
 *      Author: neoadmin
 */

#include "WPILib.h"
#include <Subsystems/GearServo.h>


GearServo::GearServo(Constant *Ricky) :
Subsystem("GearServo")
{
	constants = Ricky;
	servoL = new Servo(constants->Get("ServoLChannel")); //PWM Channel
	servoR = new Servo(constants->Get("ServoRChannel")); //PWM Channel

} // of GearServo Constructor

void GearServo::ServoSet(){
servoL->Set(constants->Get("ServoLSet"));
servoR->Set(constants->Get("ServoRSet"));

}

void GearServo::ServoReset(){
servoL->Set(constants->Get("ServoLReset"));
servoR->Set(constants->Get("ServoRReset"));

}

void GearServo::ServoGet(){
servoL->Get();
servoR->Get();

}

