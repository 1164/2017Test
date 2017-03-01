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
#include "Subsystems/FuelMovement.h"
#include "Subsystems/RobotLift.h"
#include <Constant.h>
#include <Joystick.h>
#include <TalonSRX.h>
#include <RobotDrive.h>
#include "Autonomous/AutoBaseLine.h"
#include "Autonomous/AutoTurnToPilot.h"
#include "Autonomous/BaseLineTurnLeft.h"


class Robot: public frc::IterativeRobot {
private:
	frc::LiveWindow* lw = LiveWindow::GetInstance();
	frc::SendableChooser<std::string> chooser;


	const std::string autoNameDefault = "Default";
	const std::string autoNameCustom = "My Auto";
	std::string autoSelected;

	Joystick *OperatorControl;
	Joystick *DriverControl;
	Constant *constant;
	FourWheelDrive *Drive;
	Shooter *ShootingShooter;
	NavxCode *Navx;
	RobotLift *Lift;
	FuelMovement *Roller;

	int AutoControl=0;

	AutoBaseLine *ABL=NULL;
	AutoTurnToPilot *ATTPLeft;
	AutoTurnToPilot *ATTPRight;
    BaseLineTurnLeft * BLTL;


	frc::CameraServer* C1= CameraServer::GetInstance();

public:
	void RobotInit() {


		chooser.AddDefault(autoNameDefault, autoNameDefault);
		chooser.AddDefault("Hello", "Hello1");
		chooser.AddObject(autoNameCustom, autoNameCustom);
		frc::SmartDashboard::PutData("Auto Modes", &chooser);

		constant = new Constant();
		DriverControl = new Joystick(constant->Get("DriverJoystick"));
		OperatorControl = new Joystick(constant->Get("OperatorJoystick"));
		Drive = new FourWheelDrive (constant);
		ShootingShooter = new Shooter(constant);
		Navx = new NavxCode(constant);
		Lift = new RobotLift(constant);
		Roller = new FuelMovement(constant);

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

		std::string autoSelected = SmartDashboard::GetString("Auto Selector", autoNameDefault);
		std::cout << "Auto selected: " << autoSelected << std::endl;
		DriverStation::GetInstance().ReportError(autoSelected);

		ABL=new AutoBaseLine(Drive,constant);
		BLTL=new BaseLineTurnLeft(Drive,Navx,constant,true);

		switch (AutoControl/10) {
			case 0: DriverStation::GetInstance().ReportError("Running Level 0 Baseline Only\n");

			      Scheduler::GetInstance()->AddCommand((Command *)ABL);
			       break;
			case 1: DriverStation::GetInstance().ReportError("Running Level 1 Base Line Turn Left\n");
			        Scheduler::GetInstance()->AddCommand((Command *)BLTL);
					break;
			case 2: DriverStation::GetInstance().ReportError("Running Level 2\n");
							break;
			case 3: DriverStation::GetInstance().ReportError("Running Level 3\n");
								break;
			case 4: DriverStation::GetInstance().ReportError("Running Level 4\n");
								break;
		}



		if (autoSelected == autoNameCustom) {
			// Custom Auto goes here
		} else {
			// Default Auto goes here
		}
		// ABL=new AutoBaseLine(Drive,constant);
		// ATTPLeft = new AutoTurnToPilot(Drive,Navx,constant,true);
		 //ATTPRight = new AutoTurnToPilot(Drive,Navx,constant,false);

		 //Scheduler::GetInstance()->AddCommand((Command *)ABL);
		 Scheduler::GetInstance()->AddCommand((Command *)ATTPLeft);
		 //Scheduler::GetInstance()->AddCommand((Command *)ATTPRight);




	}

	void AutonomousPeriodic() {
		if (autoSelected == autoNameCustom) {
			// Custom Auto goes here
		} else {
			// Default Auto goes here
		}
		Scheduler::GetInstance()->Run();
	}

	void TeleopInit() {
		//  We need to remove any commands that may be on the scheduler that are autonmous only
		if ( ABL != NULL ) Scheduler::GetInstance()->Remove((Command *)ABL); //  Remove the autonomous

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
		char *ENCstring = new char[255];

		sprintf(ENCstring, "Shooter Encoder %f\n",ShootingShooter->GetRate() ); //outputs Encoder reading
		DriverStation::GetInstance().ReportError(ENCstring); // funnels Encoder reading into driver station

		ShootingShooter->update(OperatorControl->GetRawButton(constant->Get("ShootOnButton")),
								OperatorControl->GetRawButton(constant->Get("ShootOffButton")),
								OperatorControl->GetRawButton(constant->Get("ShootTrigButton")));

		Drive->arcadeDrive(	DriverControl->GetAxis((Joystick::AxisType)constant->Get("DriveAxisX")),
							-DriverControl->GetAxis((Joystick::AxisType)constant->Get("DriveAxisYForward")),
							DriverControl->GetRawButton(constant->Get("HighShiftButtonPOV")),
							DriverControl->GetRawButton(constant->Get("LowShiftButtonPOV")));

		Drive->Forward(	DriverControl->GetRawButton(constant->Get("ForwardFaceButton")),
						DriverControl->GetRawButton(constant->Get("BackwardFaceButton")));

		Roller->Roller(	OperatorControl->GetRawButton(constant->Get("RollerOnButton")),
						OperatorControl->GetRawButton(constant->Get("RollerOffButton")),
						OperatorControl->GetRawButton(constant->Get("RollerBackButton")));

		Lift->Set(OperatorControl->GetAxis((Joystick::AxisType)constant->Get("LiftAxis")));
		//Navx->Gyro();
/*
		char joystickPOVValue[255];
		sprintf(joystickPOVValue, "Axis Value 1: %f\n",  OperatorControl->GetAxis((Joystick::AxisType)2)); //outputs Breakbeam Sensor value
					DriverStation::GetInstance().ReportError(joystickPOVValue); // funnels breakbeam value into driver station
		sprintf(joystickPOVValue, "Axis Value 2: %f\n",  OperatorControl->GetAxis((Joystick::AxisType)4)); //this is truly axis 3
					DriverStation::GetInstance().ReportError(joystickPOVValue); // funnels breakbeam value into driver station
*/
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
		//char *EncoderTest = new char[255];
		/*char *PneumaticsTest = new char[255];
		char *VictorTest = new char[255];
		char *SparkTest = new char[255];
		char *MotorTest = new char[255];
		char *Breakbeam = new char[255];

		*/


		if (DriverControl->GetRawButton(10))
			AutoControl=(AutoControl+1)%50;



		switch (AutoControl/10) {
		case 0: DriverStation::GetInstance().ReportError("Level 0 Baseline Only\n");
		       break;
		case 1: DriverStation::GetInstance().ReportError("Level 1  Base Line Turn Left\n");
				break;
		case 2: DriverStation::GetInstance().ReportError("Level 2\n");
						break;
		case 3: DriverStation::GetInstance().ReportError("Level 3\n");
							break;
		case 4: DriverStation::GetInstance().ReportError("Level 4\n");
							break;


		}

	//	sprintf(EncoderTest, "Encoder value: %d\n",  Drive->LeftEncoder()); //outputs Encoder reading
	//		DriverStation::GetInstance().ReportError(EncoderTest); // funnels Encoder reading into driver station
	/*	sprintf(PneumaticsTest, "pnue value: %f\n",  constant->Get("PneumaticChannel")); //outputs solenoid reading
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
		/*char shooterEncValue[255];
		sprintf(shooterEncValue, "Shooter encoder: %d\n",  ShootingShooter->GetEncoder()); //outputs Breakbeam Sensor value
					DriverStation::GetInstance().ReportError(shooterEncValue); // funnels breakbeam value into driver station*/
		//char joystickPOVValue[255];
		//sprintf(joystickPOVValue, "Axis Value 1: %f\n",  ShooterControl->GetAxis((Joystick::AxisType)0)); //outputs Breakbeam Sensor value
		//			DriverStation::GetInstance().ReportError(joystickPOVValue); // funnels breakbeam value into driver station
		//sprintf(joystickPOVValue, "Axis Value 2: %f\n",  ShooterControl->GetAxis((Joystick::AxisType)1)); //this is truly axis 3
		//			DriverStation::GetInstance().ReportError(joystickPOVValue); // funnels breakbeam value into driver station
		/*char joystickPOVValue[255];
		sprintf(joystickPOVValue, "Limit 1: %d\n",  Lift->LimitTop->Get()); //outputs Breakbeam Sensor value
					DriverStation::GetInstance().ReportError(joystickPOVValue); // funnels breakbeam value into driver station
		sprintf(joystickPOVValue, "Limit 2: %d\n",  Lift->LimitBottom->Get()); //this is truly axis 3
					DriverStation::GetInstance().ReportError(joystickPOVValue); // funnels breakbeam value into driver station*/

		//char *NAVXstring = new char[255];
		//Navx->Gyro();

		//sprintf(NAVXstring, "NAVX Pitch %f   NAVX Roll %f  NAVX YAW %f\n",
		//		Navx->GetPitchAngle(), Navx->GetRollAngle()
		//		Navx->GetYawAngle()); //outputs Encoder reading
		//DriverStation::GetInstance().ReportError(NAVXstring); // funnels Encoder reading into driver station

	}

};

START_ROBOT_CLASS(Robot)
