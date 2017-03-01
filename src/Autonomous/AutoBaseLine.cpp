/*
 * AutoBaseLine.cpp
 *
 *  Created on: Feb 23, 2017
 *      Author: neoadmin
 */

#include <Autonomous/AutoBaseLine.h>

namespace frc {

AutoBaseLine::AutoBaseLine(FourWheelDrive *FWD, Constant* C) : Command("AutoBaseLine") {
	Drive = FWD;
	Drive->ResetEncoders(); //set encoder to 0 so we know how far to go
	running_=true;
	constants=C;

}

AutoBaseLine::~AutoBaseLine() {
	// TODO Auto-generated destructor stub
}

} /* namespace frc */

bool  AutoBaseLine::IsFinished()  {

	if (!running_) {
		Drive->arcadeDrive(0,0,0,0); // stop
	}

	return(!running_);

}

void AutoBaseLine::End()
{

}

void AutoBaseLine::Initialize()
{

}

void AutoBaseLine::Execute(){

	// Drive Autonomously until we get to our spot
	char myst[200];

	sprintf(myst,"Encoder Constant is %f, Encoder is %d\n",
			constants->Get("AutoBaseLineEncoder"),Drive->LeftEncoder());

	perror(myst);

	//  get the Drive encoder --- if we get to the encoder value then we are done, other wise drive
	if (constants->Get("AutoBaseLineEncoder") < Drive->LeftEncoder()) running_=false;
	else    Drive->arcadeDrive(0,-0.5,false,false);

}
