/*
 * GearServo.h
 *
 *  Created on: Feb 15, 2017
 *      Author: neoadmin
 */

#ifndef SRC_SUBSYSTEMS_GEARSERVO_H_
#define SRC_SUBSYSTEMS_GEARSERVO_H_
#include "Constant.h"
#include "WPILib.h"
#include <Servo.h>

class GearServo: public Subsystem
{
private:

	Constant *constants;
	Servo *servoL;
	Servo *servoR;


public:
    GearServo(Constant *Ricky);
    void ServoSet();
    void ServoReset();
    void ServoGet();


};

#endif /* SRC_SUBSYSTEMS_GEARSERVO_H_ */
