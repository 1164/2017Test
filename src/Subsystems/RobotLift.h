/*
 * RobotLift.h
 *
 *  Created on: Feb 15, 2017
 *      Author: neoadmin
 */

#ifndef SRC_SUBSYSTEMS_ROBOTLIFT_H_
#define SRC_SUBSYSTEMS_ROBOTLIFT_H_
#include "Constant.h"
#include "WPILib.h"
#include <VictorSP.h>

class RobotLift: public Subsystem
{
private:

	Constant *constants;
	VictorSP *LiftSC;

public:
    RobotLift(Constant *Sarah);

};

#endif /* SRC_SUBSYSTEMS_ROBOTLIFT_H_ */
