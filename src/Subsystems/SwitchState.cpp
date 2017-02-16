/*
 * SwitchState.cpp
 *
 *  Created on: Feb 15, 2017
 *      Author: neoadmin
 */

#include "WPILib.h"
#include <Subsystems/SwitchState.h>


SwitchState::SwitchState(Constant *Jill) :
Subsystem("SwitchState")
{
	constants = Jill;

} // of SwitchState Constructor


