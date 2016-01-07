#include <unistd.h>
#include <signal.h>
#include <iostream>
#include "adafruitms1438.h"

#include "motors.h"

using namespace std;
using namespace upm;

#define M0 AdafruitMS1438::STEPMOTOR_M12 
#define M1 AdafruitMS1438::STEPMOTOR_M34 

//-------------------------------------------------------------------------
static upm::AdafruitMS1438     *ms;


//-------------------------------------------------------------------------


	Motors::Motors()
{
}

//-------------------------------------------------------------------------

	Motors::Motors()
{
  	ms = new upm::AdafruitMS1438(ADAFRUITMS1438_I2C_BUS, ADAFRUITMS1438_DEFAULT_I2C_ADDR);
  	ms->disableStepper(M0);
  	ms->disableStepper(M1);
  // configure for a NEMA-17, 200 steps per revolution
  	ms->stepConfig(M0, 200);
  	ms->stepConfig(M1, 200);

  	ms->setStepperSpeed(M0, 10);
  	ms->setStepperSpeed(M1, 10);

  	ms->setStepperDirection(M0, AdafruitMS1438::DIR_CW);
  	ms->setStepperDirection(m1, AdafruitMS1438::DIR_CW); 
  	ms->enableStepper(M0);
  	ms->enableStepper(M1);

  	delete ms;
}

//-------------------------------------------------------------------------

	Motors::~Motors()
{
	delete ms;
}

//-------------------------------------------------------------------------

void	Motors::Steps(int a, int b)
{
}
