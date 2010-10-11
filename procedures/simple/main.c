
#define SET_POSITION_TARGET ZRSetPositionTarget
#define SET_ATTITUDE_TARGET ZRSetAttitudeTarget

#define STATE_INIT        0
#define STATE_PREP        1
#define STATE_SEARCHING   2
#define STATE_TOPANEL     3
#define STATE_TOSTATION   4

#include "S_Globals.c"

void ZRUser(float* myState, float* otherState, float time)
{
 float target[3];
 float targetX;

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
