/*
 * AutoTurnToPilot.h
 *
 *  Created on: Feb 25, 2017
 *      Author: neoadmin
 */

#ifndef SRC_AUTONOMOUS_AUTOTURNTOPILOT_H_
#define SRC_AUTONOMOUS_AUTOTURNTOPILOT_H_
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


class AutoTurnToPilot : Command {
public:
	AutoTurnToPilot(FourWheelDrive *FWD, NavxCode *N,Constant * C, bool left);
	virtual ~AutoTurnToPilot();
	bool running_;
	FourWheelDrive * Drive;
	Constant *constant;
	NavxCode * mynavx;

	double target_angle;

	bool IsFinished();
	void End();
	void Initialize();
	void Execute();
};


} // of frc namespace


#endif /* SRC_AUTONOMOUS_AUTOTURNTOPILOT_H_ */
