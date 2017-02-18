/*
 * Shooter.cpp
 *
 *  Created on: Jan 15, 2017
 *      Author: neoadmin
 */
#include "Shooter.h"
#include <VictorSP.h>
#include <iostream>
#include <Constant.h>
#include <DigitalInput.h>


Shooter::Shooter(Constant *NASA) :
	Subsystem("Shooter"){
	constant = NASA;
	shooterMotor = new VictorSP(constant->Get("ShooterMotor"));
	shooterEnc = new Encoder(constant->Get("ShootEncA"),
								constant->Get("ShootEncB"));
	plunger1 = new Solenoid(constant->Get("PCMCanID"), constant->Get("ShooterPlungerFw"));
	plunger2 = new Solenoid(constant->Get("PCMCanID"), constant->Get("ShooterPlungerRv"));
	shooterOn = false;
}


// update
// This function updates the state of the shooter, it has the code to turn on and off the shooter
// at a constant speed. Also has the plunger code for the shooter by setting triggerButton
//
// @param shooterOnButton - button to set shooter on (toggles)
// @param shooterOffButton - button to set shooter off (toggles)
// @param triggerButton - when true plunges a ball into shooter, moves plunger back when false.
void Shooter::update(bool shooterOnButton, bool shooterOffButton, bool triggerButton)
{
	if (shooterOffButton) {
		shooterOn = false;
	} else if (shooterOnButton) {
		shooterOn = true;
	}


	if (shooterOn || constant->Get("TestMode") == 1) {
		plunger1->Set(triggerButton);
		plunger2->Set(!triggerButton);
	}

	if (shooterOn)
		shooterMotor->Set(constant->Get("ShooterMotorSpeed"));
	else
		shooterMotor->Set(0);
}

int Shooter::GetEncoder() {
	return shooterEnc->Get();
}
