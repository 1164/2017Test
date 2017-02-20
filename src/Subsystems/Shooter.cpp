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

#define WAIT 0
#define INIT_SHOOT 1
#define SHOOT 2

Shooter::Shooter(Constant *NASA) :
	Subsystem("Shooter"){
	constant = NASA;
	shooterMotor = new VictorSP(constant->Get("ShooterMotor"));
	shooterEnc = new Encoder(constant->Get("ShootEncA"),
								constant->Get("ShootEncB"));
	shooterEnc->SetDistancePerPulse(constant->Get("ShooterDistancePerPulse"));
	plunger1 = new Solenoid(constant->Get("PCMCanID"), constant->Get("ShooterPlungerFw"));
	plunger2 = new Solenoid(constant->Get("PCMCanID"), constant->Get("ShooterPlungerRv"));
	shooterOn = false;
	shooterState = WAIT;
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

	if (TriggerStateUpdate(triggerButton)) {
		plunger1->Set(true);
		plunger2->Set(false);
	}
	else {
		plunger1->Set(false);
		plunger2->Set(true);
	}

	if (shooterOn)
		shooterMotor->Set(bangBangController());
	else
		shooterMotor->Set(0);
}

// bangBangController
// This function implements a simple bangBangController
// The bang-bang controller, will return the FullSpeedShooter when the
// encoder rate is below the setpoint and sets HalfSpeedShooter when above the setpoint
//
// @return - returns the motor speed of the shooter.
double Shooter::bangBangController() {
	if (shooterEnc->GetRate() > constant->Get ("ShooterRpm"))
		return constant ->Get ("HalfSpeedShooter");
	else
		return constant ->Get ("FullSpeedShooter");
}

int Shooter::GetEncoder() {
	return shooterEnc->Get();
}

bool Shooter::TriggerStateUpdate(bool triggerButton) {
	if (shooterState == WAIT){
		if ((triggerButton == true)
				&& (constant->Get("ShooterRpm")-constant->Get("ShooterDeadband") < shooterEnc->GetRate())
				&& (shooterEnc->GetRate() < constant->Get("ShooterRpm")+constant->Get("ShooterDeadband")))
		{
			shooterState = INIT_SHOOT;
		}
		return false;
	}
	else if (shooterState == INIT_SHOOT){
		count = 0;
		shooterState = SHOOT;
		return true;
	}
	else if (shooterState == SHOOT){
		count++;
		if (count >= 50*constant->Get("plungWaitSec")){
			shooterState = WAIT;
			return true;
		}
		else {
			return false;
		}
	}
	return false; //This should never be reached
}
