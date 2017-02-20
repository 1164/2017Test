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

	DigitalInput *LimitTop;
	DigitalInput *LimitBottom;

public:
    RobotLift(Constant *Sarah);

    void Set(double climb);
};

#endif /* SRC_SUBSYSTEMS_ROBOTLIFT_H_ */
