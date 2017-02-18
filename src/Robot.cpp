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


class Robot: public frc::IterativeRobot {
private:
	frc::LiveWindow* lw = LiveWindow::GetInstance();
	frc::SendableChooser<std::string> chooser;
	const std::string autoNameDefault = "Default";
	const std::string autoNameCustom = "My Auto";
	std::string autoSelected;

	Joystick *OperatorControl;
	Joystick *ShooterControl;
	Constant *constant;
	FourWheelDrive *Drive;
	Shooter *ShootingShooter;
	NavxCode *Navx;

	frc::CameraServer* C1= CameraServer::GetInstance();
public:
	void RobotInit() {
		chooser.AddDefault(autoNameDefault, autoNameDefault);
		chooser.AddObject(autoNameCustom, autoNameCustom);
		frc::SmartDashboard::PutData("Auto Modes", &chooser);

		constant = new Constant();
		OperatorControl = new Joystick(0);
		ShooterControl = new Joystick(1);
		Drive = new FourWheelDrive (constant);
		ShootingShooter = new Shooter(constant);
		Navx = new NavxCode(constant);

		// Create a Cameraserver Object
		//C1 = new CameraServer::GetInstance();
		C1->AddAxisCamera ("axis-camera");
		Drive->ResetEncoders();

	}

	/*
	 * This autonomous (along with the chooser code above) shows how to select
	 * between different autonomous modes using the dashboard. The sendable
	 * chooser code works with the Java SmartDashboard. If you prefer the
	 * LabVIEW Dashboard, remove all of the chooser code and uncomment the
	 * GetString line to get the auto name from the text box below the Gyro.
	 *
	 * You can add additional auto modes by adding additional comparisons to the
	 * if-else structure below with additional strings. If using the
	 * SendableChooser make sure to add them to the chooser code above as well.
	 */
	void AutonomousInit() override {
		autoSelected = chooser.GetSelected();
		// std::string autoSelected = SmartDashboard::GetString("Auto Selector", autoNameDefault);
		std::cout << "Auto selected: " << autoSelected << std::endl;

		if (autoSelected == autoNameCustom) {
			// Custom Auto goes here
		} else {
			// Default Auto goes here
		}
	}

	void AutonomousPeriodic() {
		if (autoSelected == autoNameCustom) {
			// Custom Auto goes here
		} else {
			// Default Auto goes here
		}
	}

	void TeleopInit() {

	}

	void TeleopPeriodic() {

		OperatorControl->GetRawButton(1);

		/*Drive->arcadeDrive(OperatorControl->GetAxis((Joystick::AxisType)constant->Get("DriveAxisY")),
							OperatorControl->GetAxis((Joystick::AxisType)constant->Get("DriveAxisX")),
								false,
								false);*/



		// Now work on the arcade motor testing
		/*int value;
		if (OperatorControl->GetRawButton(1)) {
			value = 1;
		}
		else if (OperatorControl->GetRawButton(2)) {
			value = 2;
		}
		else if (OperatorControl->GetRawButton(3)) {
			value = 3;
		}
		else if (OperatorControl->GetRawButton(4)) {
			value = 4;
		}
		else {
			value = 0;
		}
		*/
		//Drive->arcadeDrive(value, 0.0, false, false);

		ShootingShooter->update(ShooterControl->GetRawButton(constant->Get("ShootOnButton")),
								ShooterControl->GetRawButton(constant->Get("ShootOffButton")),
								ShooterControl->GetRawButton(constant->Get("ShootTrigButton")));

		Drive->arcadeDrive(OperatorControl->GetAxis((Joystick::AxisType)constant->Get("MotorAxisY")),
						OperatorControl->GetAxis((Joystick::AxisType)constant->Get("DriveAxisX")),
						OperatorControl->GetRawButton(constant->Get("HighShiftButton")),
						OperatorControl->GetRawButton(constant->Get("LowShiftButton")));
		Navx->Gyro();


	}

	void TestPeriodic() {
		lw->Run();
		/*char *EncoderTest = new char[255];
		char *PneumaticsTest = new char[255];
		char *VictorTest = new char[255];
		char *SparkTest = new char[255];
		char *MotorTest = new char[255];
		char *Breakbeam = new char[255];

		sprintf(EncoderTest, "Encoder value: %d\n",  Drive->LeftEncoder()); //outputs Encoder reading
					DriverStation::GetInstance().ReportError(EncoderTest); // funnels Encoder reading into driver station
		sprintf(PneumaticsTest, "pnue value: %f\n",  constant->Get("PneumaticChannel")); //outputs solenoid reading
					DriverStation::GetInstance().ReportError(PneumaticsTest); // funnels solenoid reading into driver station
		sprintf(VictorTest, "MotorOutput: %f\n",  OperatorControl->GetAxis((Joystick::AxisType)constant->Get("DriveAxisY"))); //outputs button value
					DriverStation::GetInstance().ReportError(VictorTest); // funnels button value into driver station
		sprintf(SparkTest, "MotorOutput: %f\n",  OperatorControl->GetAxis((Joystick::AxisType)constant->Get("DriveAxisY"))); //outputs button value
					DriverStation::GetInstance().ReportError(SparkTest); // funnels button value into driver station
		sprintf(MotorTest, "MotorOutput: %f\n",  OperatorControl->GetAxis((Joystick::AxisType)constant->Get("DriveAxisY"))); //outputs button value
					DriverStation::GetInstance().ReportError(MotorTest); // funnels button value into driver station
		sprintf(Breakbeam, "DigitalInput: %f\n",  constant->Get("DIBreakbeam")); //outputs Breakbeam Sensor value
					DriverStation::GetInstance().ReportError(Breakbeam); // funnels breakbeam value into driver station
		*/
	}


	void DisabledPeriodic()
	{
		/*char *EncoderTest = new char[255];
		char *PneumaticsTest = new char[255];
		char *VictorTest = new char[255];
		char *SparkTest = new char[255];
		char *MotorTest = new char[255];
		char *Breakbeam = new char[255];

		sprintf(EncoderTest, "Encoder value: %d\n",  Drive->LeftEncoder()); //outputs Encoder reading
			DriverStation::GetInstance().ReportError(EncoderTest); // funnels Encoder reading into driver station
		sprintf(PneumaticsTest, "pnue value: %f\n",  constant->Get("PneumaticChannel")); //outputs solenoid reading
			DriverStation::GetInstance().ReportError(PneumaticsTest); // funnels solenoid reading into driver station
		sprintf(VictorTest, "MotorOutput: %f\n",  OperatorControl->GetAxis((Joystick::AxisType)constant->Get("DriveAxisY"))); //outputs button value
			DriverStation::GetInstance().ReportError(VictorTest); // funnels button value into driver station
		sprintf(SparkTest, "MotorOutput: %f\n",  OperatorControl->GetAxis((Joystick::AxisType)constant->Get("DriveAxisY"))); //outputs button value
			DriverStation::GetInstance().ReportError(SparkTest); // funnels button value into driver station
		sprintf(MotorTest, "MotorOutput: %f\n",  OperatorControl->GetAxis((Joystick::AxisType)constant->Get("DriveAxisY"))); //outputs button value
			DriverStation::GetInstance().ReportError(MotorTest); // funnels button value into driver station
		sprintf(Breakbeam, "DigitalInput: %f\n",  constant->Get("DIBreakbeam")); //outputs Breakbeam Sensor value
			DriverStation::GetInstance().ReportError(Breakbeam); // funnels breakbeam value into driver station
		*/
		char shooterEncValue[255];
		sprintf(shooterEncValue, "Shooter encoder: %d\n",  ShootingShooter->GetEncoder()); //outputs Breakbeam Sensor value
					DriverStation::GetInstance().ReportError(shooterEncValue); // funnels breakbeam value into driver station
	}

};

START_ROBOT_CLASS(Robot)
