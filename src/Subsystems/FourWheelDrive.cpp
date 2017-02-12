/*
 * FourWheelDrive.cpp
 *
 *  Created on: Jan 10, 2017
 *      Author: neoadmin
 */

#include "FourWheelDrive.h"

//#include "../RobotMap.h"


FourWheelDrive::FourWheelDrive(Constant *Blah) :
		Subsystem("FourWheeelDrive")
{
	constants = Blah;

	//TestVictor1 = new VictorSP(constants->Get("VictorTest1"));//The Test VictorSP Motor Controller on PWM 1
	//Spark0Controller = new Spark(constants->Get("ControllerSpark0"));//The test Spark Motor Controller on PWM 0
	//TestMotor = new CANTalon(constants->Get("MotorTest"));// THE TEST CAN BUS TALON SRX MOTOR
	Pneumatics = new Solenoid(constants->Get("SolenoidCAN"), constants->Get("PneumaticChannel"));//The Pneumatic solenoid on channel 4

	leftFront = new VictorSP(constants->Get("frontLeftDrive"));
	rightFront = new VictorSP(constants->Get("frontRightDrive"));
	leftBack = new VictorSP(constants->Get("backLeftDrive"));
	rightBack = new VictorSP(constants->Get("backRightDrive"));

	leftBack->SetInverted(constants->Get("leftBackInvert")== 1);
	leftFront->SetInverted(constants->Get("leftFrontInvert")== 1);
	rightBack->SetInverted(constants->Get("rightBackInvert")== 1);
	rightFront->SetInverted(constants->Get("rightFrontInvert")== 1);

	Drive = new RobotDrive(leftFront, leftBack, rightFront, rightBack);
	//Drive1 = new RobotDrive(leftFront,rightFront);
	//Drive2 = new RobotDrive(leftBack, rightBack);
	LeftDriveEncoder = new Encoder(constants->Get("LeftEncoderA"), constants->Get("LeftEncoderB"));
	RightDriveEncoder = new Encoder(constants->Get("RightEncoderA"), constants->Get("RightEncoderB"));
	ShifterTest = false;
	Shifter = new Solenoid(1, constants->Get("ShifterSolenoid"));
	Shifter2 = new Solenoid(1, constants->Get("ShifterSolenoid2")); // CAT REMOVE COMMENT IF DOUBLE SOLENOID



	//Drive->SetSafetyEnabled(false);

}

void FourWheelDrive::arcadeDrive(float x, float y, bool isHighGear, bool isLowGear){

if (isHighGear)//high gear
		ShifterTest = true;

	if (isLowGear)//low gear
		ShifterTest = false;

	if (ShifterTest){
		x=x*constants->Get("HighGearXGain");
		y=y*constants->Get("HighGearYGain");
	}
	else{
		x=x*constants->Get("LowGearXGain");
		y=y*constants->Get("LowGearYGain");
	}
	if (x<.05 && x>-.05){
		x=0;
	}
	if (y<.05 && y>-.05){
			y=0;
	}

	arcadeDrive(x,y,ShifterTest);
} // f class oFWD arcade Drive

void FourWheelDrive::arcadeDrive(float x, float y, bool isHighGear){
	printf("hello");
	// Left and right speed are set for driving with the
	// + and - X and Y sets. This works in all cases until you get
	// a number input from joystick such as (.5,1) this would set the
	// leftSpeed = 1.5 rightSpeed = .5, We want constant different which should
	// be left = 1 right = 0 so we use the if's to catch this issue and
	// subtract the extra .5 from the left speed from the right speed
	double leftSpeed = y + x;
	double rightSpeed = y - x;

	if (leftSpeed > 1)	{
		rightSpeed = rightSpeed - (leftSpeed - 1);
		leftSpeed = 1;
	} else if (leftSpeed < -1)	{
		rightSpeed = rightSpeed - (leftSpeed + 1);
		leftSpeed = -1;
	} else if (rightSpeed > 1) {
		leftSpeed = leftSpeed - (rightSpeed - 1);
	} else if (rightSpeed < -1) {
		leftSpeed = leftSpeed - (rightSpeed + 1);
	}

	//Drive1->TankDrive(leftSpeed, rightSpeed, false);
	//Drive2->TankDrive(leftSpeed, rightSpeed, false);
	Drive->TankDrive(leftSpeed, rightSpeed, false);

	// End Ian's Cheezy algorithm

	//rightMid->Set(rightFront->Get());
	//leftMid->Set(leftFront->Get());

	ShifterTest=isHighGear;

	Shifter->Set(ShifterTest);
	Shifter2->Set(!ShifterTest); // CAT REMOVE COMMENT IF NEEDS DOUBLE SOLENOID

}

// test code for the pneumatic solenoid

void FourWheelDrive::PneumaticSolenoid(float Pneu){
	Pneumatics->Set(Pneu);
}

void FourWheelDrive::ResetEncoders(){

}

int FourWheelDrive::LeftEncoder(){
	return LeftDriveEncoder->Get();
}

int FourWheelDrive::RightEncoder(){
	return RightDriveEncoder->Get();
}

