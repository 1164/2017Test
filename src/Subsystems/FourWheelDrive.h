/*
 * FourWheelDrive.h
 *
 *  Created on: Jan 10, 2017
 *      Author: neoadmin
 */

#ifndef FourWheelDrive_H
#define FourWheelDrive_H

#include "Commands/Subsystem.h"
#include "WPILib.h"
#include <RobotDrive.h>
#include <Joystick.h>
#include <Solenoid.h>
#include <Encoder.h>
#include "../Constant.h"
#include <VictorSP.h>
#include <iostream>
#include <CANTalon.h>
#include <Spark.h>
#include <Solenoid.h>
const double EncoderReset = 0;
//#include <Talon.h>

class FourWheelDrive: public Subsystem
{
private:
	RobotDrive *Drive;

	VictorSP *leftBack; //VictorSP
	VictorSP *rightBack;//VictorSP
	VictorSP *rightFront;//VictorSP
	VictorSP *leftFront;//VictorSP
	//Encoder *RightDriveEncoder;
	Encoder *LeftDriveEncoder;
	Solenoid *Shifter;
	Solenoid *Shifter2;
	bool ShifterTest;
	Constant *constants;


public:
	FourWheelDrive(Constant *Blah);

	void arcadeDrive(float x, float y, bool isHighGear, bool isLowGear);
	void PneumaticSolenoid(float Pneu);
	void arcadeDrive(float x, float y, bool isHighGear);
	void ResetEncoders();
	int LeftEncoder();
	int RightEncoder();
	void Forward(bool forwardFace, bool backwardFace);

	//void InitDefaultCommand();

};

#endif /* SRC_SUBSYSTEMS_FOURWHEELDRIVE_H_ */
