/*
 * AutoBaseLine.h
 *
 *  Created on: Feb 23, 2017
 *      Author: neoadmin
 */

#ifndef SRC_AUTOBASELINE_H_
#define SRC_AUTOBASELINE_H_
#include <iostream>
#include <memory>
#include <string>

#include <WPILib.h>

#include <DriverStation.h>

#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include "Subsystems/FourWheelDrive.h"
#include "Subsystems/Shooter.h"
#include "Subsystems/NavxCode.h"
#include <Constant.h>
#include <Joystick.h>
#include <TalonSRX.h>
#include <RobotDrive.h>
#include <Autonomous/FetchZed.h>

namespace frc {

class AutoBaseLine : Command  {
public:
	AutoBaseLine(FourWheelDrive *FWD, Constant* C);
	virtual ~AutoBaseLine();
	bool IsFinished();
	void End();
	void Initialize();
	void Execute();
	bool running_;
	Constant * constants;

private:
	FourWheelDrive * Drive;
};

} /* namespace frc */

#endif /* SRC_AUTOBASELINE_H_ */
