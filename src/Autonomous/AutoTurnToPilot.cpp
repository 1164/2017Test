/*
 * AutoTurnToPilot.cpp
 *
 *  Created on: Feb 25, 2017
 *      Author: neoadmin
 */

#include <Autonomous/AutoTurnToPilot.h>

AutoTurnToPilot::AutoTurnToPilot(FourWheelDrive *FWD, NavxCode *N,Constant * C, bool left)
                 : Command("AutoTurnToPilot") {
	Drive = FWD;
	Drive->ResetEncoders(); //set encoder to 0 so we know how far to go
	running_=true;
	constant=C;
	mynavx = N;
	mynavx->ResetYaw();

	if (left)
	  target_angle=mynavx->GetYawAngle() - C->Get("AutoTurnPilotAngle");
	else
		target_angle=mynavx->GetYawAngle() + C->Get("AutoTurnPilotAngle");

}

AutoTurnToPilot::~AutoTurnToPilot() {
	// TODO Auto-generated destructor stub
}

bool  AutoTurnToPilot::IsFinished()  {

	if (!running_) {
		Drive->arcadeDrive(0,0,0,0); // stop
	}

	return(!running_);

}

void AutoTurnToPilot::End()
{

}

void AutoTurnToPilot::Initialize()
{

}

void AutoTurnToPilot::Execute(){

	double window=2.0;

	double difference=target_angle - mynavx->GetYawAngle();
	double direction;

	if (difference < 0) direction =-1.0;
	else direction = 1.0;

	direction=direction*-1;

	// Turn Autonomously until we get to our target angle

	//  get the Drive encoder --- if we get to the encoder value then we are done, other wise drive
	if ((target_angle  < (mynavx->GetYawAngle() + window))   &&
		(target_angle > (mynavx->GetYawAngle() - window)) ) running_=false;

	else    Drive->arcadeDrive(direction*0.25,0.,false,false);

}


