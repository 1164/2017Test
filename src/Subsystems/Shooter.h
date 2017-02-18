/*
 * Shooter.h
 *
 *  Created on: Jan 15, 2017
 *      Author: neoadmin
 */

#ifndef SRC_SUBSYSTEMS_SHOOTER_H_
#define SRC_SUBSYSTEMS_SHOOTER_H_
#include <VictorSP.h>
#include <Constant.h>
#include <DigitalInput.h>
#include <Solenoid.h>
#include <Encoder.h>
#include <iostream>
#include "Commands/PIDSubsystem.h"
class Shooter: public Subsystem{
private:

	VictorSP *shooterMotor;
	Constant *constant;
	Solenoid *plunger1;
	Solenoid *plunger2;
	Encoder *shooterEnc;
	bool shooterOn;


public:
	Shooter(Constant *NASA);
	void update(bool shooterOnButton, bool shooterOffButton, bool triggerButton);

	int GetEncoder();
};





#endif /* SRC_SUBSYSTEMS_SHOOTER_H_ */
