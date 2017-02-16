/*
 * SwitchState.h
 *
 *  Created on: Feb 15, 2017
 *      Author: neoadmin
 */

#ifndef SRC_SUBSYSTEMS_SWITCHSTATE_H_
#define SRC_SUBSYSTEMS_SWITCHSTATE_H_
#include "Constant.h"
#include "WPILib.h"

class SwitchState: public Subsystem
{
private:

	Constant *constants;

public:
    SwitchState(Constant *Jill);

};




#endif /* SRC_SUBSYSTEMS_SWITCHSTATE_H_ */
