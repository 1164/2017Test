/*
 * NavxCode.h
 *
 *  Created on: Feb 13, 2017
 *      Author: neoadmin
 */

#ifndef SRC_SUBSYSTEMS_NAVXCODE_H_
#define SRC_SUBSYSTEMS_NAVXCODE_H_
#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "AHRS.h"
#include <math.h>
#include "Constant.h"

class NavxCode: public Subsystem
{
private:

    AHRS *ahrs;

    Constant *constants;

public:
    NavxCode(Constant *Lucy);

    void Gyro();
    double GetPitchAngle();
    double GetRollAngle();

};



#endif /* SRC_SUBSYSTEMS_NAVXCODE_H_ */
