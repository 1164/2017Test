/*
 * BaseLineTurnLeft.cpp
 *
 *  Created on: Feb 28, 2017
 *      Author: neoadmin
 */

#include <Autonomous/BaseLineTurnLeft.h>

namespace frc {

BaseLineTurnLeft::BaseLineTurnLeft(FourWheelDrive *FWD, NavxCode *N,Constant * C, bool left) {
	// TODO Auto-generated constructor stub
	AddSequential(new AutoBaseLine(FWD,C));
	AddSequential(new AutoTurnToPilot(FWD,N,C,true));

}

BaseLineTurnLeft::~BaseLineTurnLeft() {
	// TODO Auto-generated destructor stub
}

} /* namespace frc */
