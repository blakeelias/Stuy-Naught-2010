#ifdef _MACRO_THAT_WILL_NEVER_BE_DEFINED_

To test this AI, run:

make

and copy+paste the code in out.c into the ZeroRobotics IDE.



This is a simple satellite that attempts to dock with the panel
and then with the station, without using any defensive or
offensive strategies.

Once better movement functions are completed, change the
defines below to the names of those functions.

#endif

#define SET_POSITION_TARGET ZRSetPositionTarget
#define SET_ATTITUDE_TARGET ZRSetAttitudeTarget

#define STATE_INIT        0
#define STATE_PREP        1
#define STATE_SEARCHING   2
#define STATE_TOPANEL     3
#define STATE_TOSTATION   4

int state = STATE_INIT;

void ZRUser(float* myState, float* otherState, float time)
{
 switch (state)
 {
  case STATE_INIT:
#include "S_Initialize.c"
   break;
  case STATE_PREP:
#include "S_Prep.c"
   break;
  case STATE_SEARCHING:
#include "S_Search.c"
   break;
  case STATE_TOPANEL:
#include "S_Panel.c"
   break;
  case STATE_TOSTATION:
#include "S_Station.c"
   break;
 }
}
