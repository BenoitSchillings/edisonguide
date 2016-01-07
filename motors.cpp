#include <unistd.h>
#include <signal.h>
#include <iostream>
#include "motors.h"


#ifdef FAKE
	Motors::Motors() {}
	Motors::~Motors() {}
void	Motors::Steps(int a, int b) {}
#else


#include "adafruitms1438.h"

using namespace std;
using namespace upm;

#define M0 AdafruitMS1438::STEPMOTOR_M12 
#define M1 AdafruitMS1438::STEPMOTOR_M34 

//-------------------------------------------------------------------------

static upm::AdafruitMS1438     *ms;


//-------------------------------------------------------------------------

	Motors::Motors()
{
  	ms = new upm::AdafruitMS1438(ADAFRUITMS1438_I2C_BUS, ADAFRUITMS1438_DEFAULT_I2C_ADDR);
  	ms->disableStepper(M0);
  	ms->disableStepper(M1);
  	ms->stepConfig(M0, 200);
  	ms->stepConfig(M1, 200);

  	ms->setStepperSpeed(M0, 10);
  	ms->setStepperSpeed(M1, 10);

  	ms->setStepperDirection(M0, AdafruitMS1438::DIR_CW);
  	ms->setStepperDirection(M1, AdafruitMS1438::DIR_CW); 
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

#endif
