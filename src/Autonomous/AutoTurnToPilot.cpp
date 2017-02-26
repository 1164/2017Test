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

	if (left)
	  target_angle=mynavx->GetRollAngle() + C->Get("AutoTurnPilotAngle");
	else
		target_angle=mynavx->GetRollAngle() - C->Get("AutoTurnPilotAngle");

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

	double difference=target_angle - mynavx->GetRollAngle();
	double direction;

	if (difference < 0) direction =-1.0;
	else direction = 1.0;

	// Turn Autonomously until we get to our target angle

	//  get the Drive encoder --- if we get to the encoder value then we are done, other wise drive
	if ((target_angle  < (mynavx->GetRollAngle() + window))   &&
		(target_angle > (mynavx->GetRollAngle() - window)) ) running_=false;

	else    Drive->arcadeDrive(direction*0.25,0.,false,false);

}


