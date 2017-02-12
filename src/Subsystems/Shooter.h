/*
 * Shooter.h
 *
 *  Created on: Jan 15, 2017
 *      Author: neoadmin
 */

#ifndef SRC_SUBSYSTEMS_SHOOTER_H_
#define SRC_SUBSYSTEMS_SHOOTER_H_
#include <TalonSRX.h>
#include <Constant.h>
#include <DigitalInput.h>
#include <iostream>
#include "Commands/PIDSubsystem.h"
class Shooter: public Subsystem{
private:

	TalonSRX *testmotor;
	Constant *constant;
	DigitalInput *Breakbeam;

public:
Shooter(Constant *NASA);
void BreakbeamS(float BeamBreak);

};





#endif /* SRC_SUBSYSTEMS_SHOOTER_H_ */
