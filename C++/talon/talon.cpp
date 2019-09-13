#define Phoenix_No_WPI // remove WPI dependencies
#include "ctre/Phoenix.h"
#include "ctre/phoenix/platform/Platform.h"
#include "ctre/phoenix/unmanaged/Unmanaged.h"
#include <string>
#include <iostream>
#include <chrono>
#include <thread>
#include <SDL2/SDL.h>
#include <unistd.h>

using namespace ctre::phoenix;
using namespace ctre::phoenix::platform;
using namespace ctre::phoenix::motorcontrol;
using namespace ctre::phoenix::motorcontrol::can;


int main(int argc,char** argv){
        ctre::phoenix::platform::can::SetCANInterface("can0");
	TalonSRX talonRight(1);
	TalonSRX talonLeft(2);

	talonRight.Set(ControlMode::PercentOutput, .1);
	talonLeft.Set(ControlMode::PercentOutput, -.1);
	while(true){
		ctre::phoenix::unmanaged::FeedEnable(100);
		usleep(20);
	}
}

