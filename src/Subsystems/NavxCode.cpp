/*
 * NavxCode.cpp
 *
 *  Created on: Feb 13, 2017
 *      Author: neoadmin
 */
#include "NavxCode.h"
#include "WPILib.h"
#include "AHRS.h"
#include <math.h>


NavxCode::NavxCode(Constant *Lucy) :
Subsystem("NavxCode")
{
	constants = Lucy;
}
void NavxCode::Gyro(){
	try {
				/***********************************************************************
				 * navX-MXP:
				 * - Communication via RoboRIO MXP (SPI, I2C, TTL UART) and USB.
				 * - See http://navx-mxp.kauailabs.com/guidance/selecting-an-interface.
				 *
				 * navX-Micro:
				 * - Communication via I2C (RoboRIO MXP or Onboard) and USB.
				 * - See http://navx-micro.kauailabs.com/guidance/selecting-an-interface.
				 *
				 * Multiple navX-model devices on a single robot are supported.
				 ************************************************************************/
	            ahrs = new AHRS(SPI::Port::kMXP);
	        } catch (std::exception& ex ) {
	            std::string err_string = "Error instantiating navX MXP:  ";
	            err_string += ex.what();
	            DriverStation::ReportError(err_string.c_str());
	        }
	        if ( ahrs ) {
	            LiveWindow::GetInstance()->AddSensor("IMU", "Angle", ahrs);
	        }
	      //  autoBalanceXMode = false;
	        //autoBalanceYMode = false;
	    }




