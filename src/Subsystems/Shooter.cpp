/*
 * Shooter.cpp
 *
 *  Created on: Jan 15, 2017
 *      Author: neoadmin
 */
#include "Shooter.h"
#include <TalonSRX.h>
#include <iostream>
#include <Constant.h>
#include <DigitalInput.h>


Shooter::Shooter(Constant *NASA) :
	Subsystem("Shhooter"){
	constant = NASA;
	testmotor = new TalonSRX(constant->Get("MotorTest"));
	Breakbeam = new DigitalInput(constant->Get("DIBreakbeam"));
	//Test shooter program
		/*if (x == 1) {
				TestMotor->Set(0.5);
			}
			else if (x == 2) {
				TestMotor->Set(0.7);
			}
			else if (x == 3) {
				TestMotor->Set(0.9);
			}
			else if (x == 4) {
				TestMotor->Set(1.0);
			}
			else {
				TestMotor->Set(0.0);
			}
			*/
}
void Shooter::BreakbeamS(float BeamBreak){
	if(Breakbeam->Get()==1){
		//do something
	}else{
		//do something else
	}
}


