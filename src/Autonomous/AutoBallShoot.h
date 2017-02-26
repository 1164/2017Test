/*
 * AutoBallShoot.h
 *
 *  Created on: Feb 26, 2017
 *      Author: neoadmin
 */

#ifndef SRC_AUTONOMOUS_AUTOBALLSHOOT_H_
#define SRC_AUTONOMOUS_AUTOBALLSHOOT_H_

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


class AutoBallShoot : Command {
public:
	AutoBallShoot();
};


} // of frc namespace

#endif /* SRC_AUTONOMOUS_AUTOBALLSHOOT_H_ */
