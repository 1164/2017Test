/*
 * BaseLineTurnLeft.h
 *
 *  Created on: Feb 28, 2017
 *      Author: neoadmin
 */

#ifndef SRC_AUTONOMOUS_BASELINETURNLEFT_H_
#define SRC_AUTONOMOUS_BASELINETURNLEFT_H_

#include <Commands/CommandGroup.h>
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
#include "Subsystems/NavxCode.h"
#include "Autonomous/AutoBaseLine.h"
#include "Autonomous/AutoTurnToPilot.h"

namespace frc {

class BaseLineTurnLeft: public CommandGroup {
public:
	BaseLineTurnLeft(FourWheelDrive *FWD, NavxCode *N,Constant * C, bool left);
	virtual ~BaseLineTurnLeft();
};

} /* namespace frc */

#endif /* SRC_AUTONOMOUS_BASELINETURNLEFT_H_ */
