/*
 * FuelMovement.h
 *
 *  Created on: Feb 15, 2017
 *      Author: neoadmin
 */

#ifndef SRC_SUBSYSTEMS_FUELMOVEMENT_H_
#define SRC_SUBSYSTEMS_FUELMOVEMENT_H_

#include "Constant.h"
#include "WPILib.h"
#include <VictorSP.h>

class FuelMovement: public Subsystem
{
private:

	Constant *constants;
	VictorSP *FuelMovementSC;

public:
    FuelMovement(Constant *Amy);

    void Roller(bool RollerOn, bool RollerOff);

};

#endif /* SRC_SUBSYSTEMS_FUELMOVEMENT_H_ */
