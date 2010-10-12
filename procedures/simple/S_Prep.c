//Code to move towards panel initialization circle...

#include "S_CheckPanel.c"

#define targetX (getPanelSide() * 0.7)

if (fabs(myState[0] - targetX) < .02)
 state = STATE_SEARCHING;

target[0] = targetX;
target[1] = myState[1];
target[2] = myState[2];

SET_POSITION_TARGET(target);
#undef targetX
#include "S_Tangent.c"

